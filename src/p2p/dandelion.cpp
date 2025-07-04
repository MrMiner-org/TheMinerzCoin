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

struct PendingTx {
    CTransaction tx;
    int64_t embargo_expiry;
};

static CCriticalSection cs_stem;
static std::map<uint256, PendingTx> g_stem_pool;

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

void AddToStemPool(const CTransaction& tx)
{
    CNode* stem_peer = SelectStemPeer();
    if (!stem_peer) {
        // No suitable outbound peer, fluff immediately
        BroadcastTransactionDirect(tx);
        return;
    }

    CInv inv(MSG_TX, tx.GetHash());
    stem_peer->PushInventory(inv);

    PendingTx entry{tx, GetTime() + EMBARGO_MIN + GetRandInt(EMBARGO_MAX - EMBARGO_MIN)};

    LOCK(cs_stem);
    g_stem_pool[tx.GetHash()] = entry;
}

void FlushStemPool()
{
    std::vector<CTransaction> expired;
    {
        LOCK(cs_stem);
        int64_t now = GetTime();
        for (auto it = g_stem_pool.begin(); it != g_stem_pool.end();) {
            if (now >= it->second.embargo_expiry) {
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
