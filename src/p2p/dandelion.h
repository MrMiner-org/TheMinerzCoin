#pragma once
#include <primitives/transaction.h>

namespace p2p {

/** Queue a transaction for Dandelion++ stem relay. */
void AddToStemPool(const CTransaction& tx);

/** Flush all queued transactions by relaying them. */
void FlushStemPool();

}
