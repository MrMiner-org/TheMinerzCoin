#include "validation.h"
#include "consensus/consensus.h"

bool CheckProofOfWork(const CBlockHeader& block, const Consensus::Params& params)
{
    uint256 hash;
    if (chainActive.Height() >= 72000) {
        switch (params.nAlgo) {
            case ALGO_KAWPOW:
                kawpow_hash(&block, sizeof(block), &hash, sizeof(hash));
                break;
            case ALGO_YESCRYPT_R8:
                yescrypt_hash(&block, sizeof(block), &hash, sizeof(hash));
                break;
            case ALGO_SCRYPT:
            default:
                hash = block.GetPoWHash(); // Assuming Scrypt is the default method for GetPoWHash
                break;
        }
    } else {
        hash = block.GetPoWHash(); // Default to Scrypt before block 72000
    }
    return hash <= block.nBits;
}
bool IsLongRangeAttack(const CBlockIndex* pindexNew, const CBlockIndex* pindexFork)
{
    if (pindexNew->nHeight - pindexFork->nHeight > 100) {
        return true;
    }
    return false;
}

bool ProcessNewBlockHeaders(const std::vector<CBlockHeader>& headers, const CChainParams& chainparams, CValidationState& state, const CBlockIndex** ppindex)
{
    for (const CBlockHeader& header : headers) {
        const CBlockIndex* pindexFork = nullptr;
        if (IsLongRangeAttack(pindexBestHeader, pindexFork)) {
            return state.Invalid(error("Long-range attack detected"));
        }
    }
    // Existing header processing logic
}
CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& consensusParams)
{
    // No PoW rewards after MAX_POW_BLOCKS
    if (nHeight > MAX_POW_BLOCKS) {
        return 0;
    }

    // Existing subsidy logic
    CAmount nSubsidy = 50 * COIN;
    ...

    return nSubsidy;
}

CAmount GetPoSBlockSubsidy(int nHeight, const Consensus::Params& consensusParams)
{
    // No PoS rewards after MAX_POS_BLOCKS
    if (nHeight > MAX_POS_BLOCKS) {
        return 0;
    }

    // Existing subsidy logic
    CAmount nSubsidy = 50 * COIN;
    ...

    return nSubsidy;
}
bool ContextualCheckBlockHeader(const CBlockHeader& block, CValidationState& state, const CChainParams& params, const CBlockIndex* pindexPrev, int64_t nAdjustedTime)
{


    // Enforce maximum block heights
    if (block.IsProofOfWork() && pindexPrev->nHeight >= MAX_POW_BLOCKS) {
        return state.Invalid(error("ContextualCheckBlockHeader: PoW block height exceeds maximum limit"));
    }

    if (block.IsProofOfStake() && pindexPrev->nHeight >= MAX_POS_BLOCKS) {
        return state.Invalid(error("ContextualCheckBlockHeader: PoS block height exceeds maximum limit"));
    }


}

bool ContextualCheckBlock(const CBlock& block, CValidationState& state, const CChainParams& params, const CBlockIndex* pindexPrev)
{


    // Enforce maximum block heights
    if (block.IsProofOfWork() && pindexPrev->nHeight >= MAX_POW_BLOCKS) {
        return state.Invalid(error("ContextualCheckBlock: PoW block height exceeds maximum limit"));
    }

    if (block.IsProofOfStake() && pindexPrev->nHeight >= MAX_POS_BLOCKS) {
        return state.Invalid(error("ContextualCheckBlock: PoS block height exceeds maximum limit"));
    }

}