#ifndef BITCOIN_PRIMITIVES_BRC20TRANSACTION_H
#define BITCOIN_PRIMITIVES_BRC20TRANSACTION_H

#include "primitives/transaction.h"
#include "serialize.h"
#include <string>
struct CMutableBRC20Transaction;

/**
 * Simple transaction representation for BRC20 token transfers.
 * Extends CTransaction with token metadata.
 */
class CBRC20Transaction : public CTransaction
{
public:
    std::string tokenType; //! Token ticker or identifier
    CAmount amount{0};     //! Amount of token transferred

    CBRC20Transaction();
    CBRC20Transaction(const CMutableBRC20Transaction& tx);

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
        CTransaction::SerializationOp(s, ser_action, nType, nVersion);
        READWRITE(tokenType);
        READWRITE(amount);
        if (ser_action.ForRead()) {
            UpdateHash();
        }
    }
};

/** Mutable version of CBRC20Transaction. */
struct CMutableBRC20Transaction : public CMutableTransaction
{
    std::string tokenType;
    CAmount amount{0};

    CMutableBRC20Transaction();
    CMutableBRC20Transaction(const CBRC20Transaction& tx);

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
        CMutableTransaction::SerializationOp(s, ser_action, nType, nVersion);
        READWRITE(tokenType);
        READWRITE(amount);
    }
};

#endif // BITCOIN_PRIMITIVES_BRC20TRANSACTION_H
