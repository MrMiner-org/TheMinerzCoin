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
