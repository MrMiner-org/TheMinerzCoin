#include "dandelion.h"
#include <net.h>
#include <sync.h>
#include <deque>
#include <map>
#include <vector>
#include "random.h"
#include "utiltime.h"

namespace p2p {

/** Time in seconds a transaction stays embargoed in the stem phase. */
static const int64_t EMBARGO_MIN = 10;
static const int64_t EMBARGO_MAX = 30;
/** Duration of a Dandelion++ epoch. */
static const int64_t EPOCH_MIN = 60;
static const int64_t EPOCH_MAX = 120;

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
    g_epoch_expiry = GetTime() + EPOCH_MIN + GetRandInt(EPOCH_MAX - EPOCH_MIN);
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
        PendingTx entry{tx, now + EMBARGO_MIN + GetRandInt(EMBARGO_MAX - EMBARGO_MIN)};
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
