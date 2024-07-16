#include "consensus/consensus.h"
#include "chain.h"
#include "uint256.h"

unsigned int GetNextWorkRequiredDGW(const CBlockIndex* pindexLast, const CBlockHeader* pblock, const Consensus::Params& params)
{
    const int64_t nPastBlocks = 24; // Adjust this value as needed

    if (pindexLast == NULL || pindexLast->nHeight < nPastBlocks) {
        return params.powLimit.GetCompact();
    }

    const CBlockIndex* BlockLastSolved = pindexLast;
    const CBlockIndex* BlockReading = pindexLast;
    int64_t nActualTimespan = 0;
    int64_t LastBlockTime = 0;
    int64_t PastBlocksMin = 24;
    int64_t PastBlocksMax = 24;
    uint256 PastDifficultyAverage;
    uint256 PastDifficultyAveragePrev;
    double PastRateAdjustmentRatio = 1.0;
    double EventHorizonDeviation = 1 + (0.7084 * pow((double(nPastBlocks)/2.884), -1.228));
    double EventHorizonDeviationFast = EventHorizonDeviation;
    double EventHorizonDeviationSlow = 1 / EventHorizonDeviation;

    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || BlockLastSolved->nHeight < PastBlocksMin) {
        return params.powLimit.GetCompact();
    }

    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
        PastDifficultyAverage.SetCompact(BlockReading->nBits);
        if (i > 1) {
            if (PastDifficultyAverage > PastDifficultyAveragePrev) {
                PastDifficultyAverage = ((PastDifficultyAverage - PastDifficultyAveragePrev) / i) + PastDifficultyAveragePrev;
            } else {
                PastDifficultyAverage = PastDifficultyAveragePrev - ((PastDifficultyAveragePrev - PastDifficultyAverage) / i);
            }
        }
        PastDifficultyAveragePrev = PastDifficultyAverage;

        if (LastBlockTime > 0) {
            int64_t Diff = (LastBlockTime - BlockReading->GetBlockTime());
            nActualTimespan += Diff;
        }
        LastBlockTime = BlockReading->GetBlockTime();
        if (BlockReading->pprev == NULL) { assert(BlockReading); break; }
        BlockReading = BlockReading->pprev;
    }

    uint256 bnNew(PastDifficultyAverage);

    int64_t nTargetTimespan = nPastBlocks * params.nPowTargetSpacing;

    if (nActualTimespan < nTargetTimespan / 3)
        nActualTimespan = nTargetTimespan / 3;
    if (nActualTimespan > nTargetTimespan * 3)
        nActualTimespan = nTargetTimespan * 3;

    bnNew *= nActualTimespan;
    bnNew /= nTargetTimespan;

    if (bnNew > params.powLimit) {
        bnNew = params.powLimit;
    }

    return bnNew.GetCompact();
}
