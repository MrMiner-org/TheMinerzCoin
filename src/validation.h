#ifndef BITCOIN_VALIDATION_H
#define BITCOIN_VALIDATION_H

#include <consensus/validation.h>
#include <string>
#include <vector>
#include <optional>

enum class TxValidationResult {
    TX_CONFLICT,
    TX_CONSENSUS,
    TX_INPUTS_NOT_STANDARD,
    TX_MEMPOOL_POLICY,
    TX_MISSING_INPUTS,
    TX_NOT_STANDARD,
    TX_NO_MEMPOOL,
    TX_PREMATURE_SPEND,
    TX_RECONSIDERABLE,
    TX_WITNESS_MUTATED,
    TX_WITNESS_STRIPPED
};

enum class BlockValidationResult {
    BLOCK_CONSENSUS,
    BLOCK_INVALID_HEADER,
    BLOCK_MUTATED,
    BLOCK_MISSING_PREV,
    BLOCK_INVALID_PREV,
    BLOCK_HEADER_LOW_WORK,
    BLOCK_TIME_FUTURE,
    BLOCK_CHECKPOINT,
    BLOCK_CACHED_INVALID
};

class TxValidationState : public CValidationState {
    TxValidationResult m_result{TxValidationResult::TX_CONSENSUS};
public:
    bool Invalid(TxValidationResult result, const std::string& reject_reason = "", const std::string& debug_message = "") {
        m_result = result;
        return CValidationState::Invalid(false, 0, reject_reason, debug_message);
    }
    TxValidationResult GetResult() const { return m_result; }
    std::string ToString() const { return GetRejectReason(); }
};

class BlockValidationState : public CValidationState {
    BlockValidationResult m_result{BlockValidationResult::BLOCK_CONSENSUS};
public:
    bool Invalid(BlockValidationResult result, const std::string& reject_reason = "", const std::string& debug_message = "") {
        m_result = result;
        return CValidationState::Invalid(false, 0, reject_reason, debug_message);
    }
    BlockValidationResult GetResult() const { return m_result; }
    std::string ToString() const { return GetRejectReason(); }
};

// Minimal stubs for other classes used in validation.cpp
class BlockManager {};
class Chainstate {};
class ChainstateManager {
public:
    struct Options { bool signals{false}; };
    Options m_options{};
    bool IsInitialBlockDownload() const { return false; }
};

#endif // BITCOIN_VALIDATION_H
