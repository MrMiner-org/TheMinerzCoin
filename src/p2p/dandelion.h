#pragma once
#include <primitives/transaction.h>

namespace p2p {

/** Queue a transaction for Dandelion++ stem relay. */
void AddToStemPool(const CTransaction& tx);

/**
 * Periodic maintenance tick. Handles epoch transitions,
 * embargo expiration and flushing of transactions that
 * leave the stem phase.
 */
void FlushStemPool();

}
