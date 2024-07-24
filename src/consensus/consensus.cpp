#include "consensus.h"
#include "chain.h"
#include "primitives/block.h"
#include "uint256.h"

unsigned int DarkGravityWave(const CBlockIndex* pindexLast, const CBlockHeader *pblock) {
    const int64_t pastBlocks = 24;
    const int64_t targetSpacing = 120; // 2 minutes
    const int64_t targetTimespan = pastBlocks * targetSpacing;

    if (pindexLast == nullptr || pindexLast->nHeight < pastBlocks) {
        return UintToArith256(uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff")).GetCompact();
    }

    const CBlockIndex* pindex = pindexLast;
    arith_uint256 sumTarget;
    int64_t actualTimespan = 0;
    for (int i = 0; i < pastBlocks; i++) {
        arith_uint256 target;
        target.SetCompact(pindex->nBits);
        sumTarget += target;

        if (i > 0) {
            actualTimespan += pindex->GetBlockTime() - pindex->pprev->GetBlockTime();
        }

        pindex = pindex->pprev;
    }

    arith_uint256 averageTarget = sumTarget / pastBlocks;
    actualTimespan = std::max(actualTimespan, targetTimespan / 3);
    actualTimespan = std::min(actualTimespan, targetTimespan * 3);

    arith_uint256 newTarget = averageTarget * actualTimespan / targetTimespan;

    return newTarget.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock) {
    return DarkGravityWave(pindexLast, pblock);
}
