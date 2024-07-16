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
