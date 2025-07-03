#include "dandelion.h"
#include <net.h>
#include <sync.h>
#include <deque>

namespace p2p {

static CCriticalSection cs_stem;
static std::deque<CTransaction> g_stem_pool;

void AddToStemPool(const CTransaction& tx)
{
    LOCK(cs_stem);
    g_stem_pool.push_back(tx);
}

void FlushStemPool()
{
    LOCK(cs_stem);
    while (!g_stem_pool.empty()) {
        RelayTransaction(g_stem_pool.front());
        g_stem_pool.pop_front();
    }
}

} // namespace p2p
