#ifndef BITCOIN_WALLET_PSBT_H
#define BITCOIN_WALLET_PSBT_H

#include "primitives/transaction.h"
#include <string>

/** Encode a transaction as a minimal PSBTv2 string */
std::string EncodePsbtV2(const CMutableTransaction& tx);

/** Decode a minimal PSBTv2 string into a transaction. Returns false on error. */
bool DecodePsbtV2(const std::string& psbt, CMutableTransaction& tx);

#endif // BITCOIN_WALLET_PSBT_H
