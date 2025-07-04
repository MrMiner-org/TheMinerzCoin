#pragma once
#include <primitives/transaction.h>

namespace p2p {

/** Queue a transaction for Dandelion++ stem relay. */
void AddToStemPool(const CTransaction& tx);

/** Check embargo timers and fluff expired transactions. */
void FlushStemPool();

}
