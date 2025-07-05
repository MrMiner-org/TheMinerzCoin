#include "dandelion.h"
#include <net.h>
#include <sync.h>
#include <deque>
#include <map>
#include <vector>
#include "random.h"
#include "utiltime.h"
#include <random>

namespace p2p {

/** Draw a random number from an exponential distribution within [min,max]. */
static int64_t ExpDuration(int64_t min, int64_t max)
{
    if (max <= min) return min;
    thread_local std::mt19937_64 gen(FastRandomContext().rand64());
    std::exponential_distribution<double> dist(1.0 / ((max - min) / 2.0));
    double v;
    do {
        v = dist(gen);
    } while (v > (max - min));
    return min + int64_t(v);
}

struct PendingTx {
    CTransaction tx;
    int64_t embargo_expiry;
};

static CCriticalSection cs_stem;
static std::map<uint256, PendingTx> g_stem_pool;
static int64_t g_epoch_expiry = 0;
static CNode* g_stem_peer = nullptr;
enum RelayPhase { STEM, FLUFF };
static RelayPhase g_phase = STEM;

/** Select a random outbound peer for stem relay. */
static CNode* SelectStemPeer()
{
    LOCK(cs_vNodes);
    std::vector<CNode*> candidates;
    for (CNode* pnode : vNodes) {
        if (!pnode->fInbound && !pnode->fDisconnect && pnode->fRelayTxes) {
            candidates.push_back(pnode);
        }
    }
    if (candidates.empty()) {
        return nullptr;
    }
    return candidates[GetRandInt(candidates.size())];
}

static void BroadcastTransactionDirect(const CTransaction& tx)
{
    CInv inv(MSG_TX, tx.GetHash());
    LOCK(cs_vNodes);
    for (CNode* pnode : vNodes) {
        pnode->PushInventory(inv);
    }
}

static void StartEpoch()
{
    g_epoch_expiry = GetTime() + ExpDuration(nDandelionEpochMin, nDandelionEpochMax);
    g_phase = STEM;
    g_stem_peer = SelectStemPeer();
    if (!g_stem_peer) {
        g_phase = FLUFF;
    }
}

void AddToStemPool(const CTransaction& tx)
{
    LOCK(cs_stem);
    int64_t now = GetTime();
    if (now >= g_epoch_expiry)
        StartEpoch();

    if (g_phase == STEM && g_stem_peer) {
        CInv inv(MSG_TX, tx.GetHash());
        g_stem_peer->PushInventory(inv);
        PendingTx entry{tx, now + ExpDuration(nDandelionEmbargoMin, nDandelionEmbargoMax)};
        g_stem_pool[tx.GetHash()] = entry;
    } else {
        BroadcastTransactionDirect(tx);
    }
}

void FlushStemPool()
{
    std::vector<CTransaction> expired;
    {
        LOCK(cs_stem);
        int64_t now = GetTime();
        if (now >= g_epoch_expiry)
            StartEpoch();

        for (auto it = g_stem_pool.begin(); it != g_stem_pool.end();) {
            if (now >= it->second.embargo_expiry || g_phase == FLUFF || !g_stem_peer) {
                expired.push_back(it->second.tx);
                it = g_stem_pool.erase(it);
            } else {
                ++it;
            }
        }
    }

    for (const CTransaction& tx : expired) {
        BroadcastTransactionDirect(tx);
    }
}

} // namespace p2p
