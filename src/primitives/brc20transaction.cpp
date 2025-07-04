#include "primitives/brc20transaction.h"

CBRC20Transaction::CBRC20Transaction() : CTransaction(), tokenType(), amount(0) {}

CBRC20Transaction::CBRC20Transaction(const CMutableBRC20Transaction& tx)
    : CTransaction(tx), tokenType(tx.tokenType), amount(tx.amount) {}

CMutableBRC20Transaction::CMutableBRC20Transaction()
    : CMutableTransaction(), tokenType(), amount(0) {}

CMutableBRC20Transaction::CMutableBRC20Transaction(const CBRC20Transaction& tx)
    : CMutableTransaction(tx), tokenType(tx.tokenType), amount(tx.amount) {}

