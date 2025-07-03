#include "chainparams.h"
#include "pow.h"
#include "main.h"
#include "test/test_bitcoin.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(consensus_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(block_time_reduction)
{
    SelectParams(CBaseChainParams::MAIN);
    const Consensus::Params& params = Params().GetConsensus();

    // prepare a block index before the reduction height
    CBlockIndex pindexPrev;
    pindexPrev.nHeight = params.nBlockTimeReductionHeight - 1;
    pindexPrev.nTime = params.nProtocolV3_1Time + params.nTargetSpacing;
    pindexPrev.nBits = UintToArith256(params.powLimit).GetCompact();

    unsigned int before = CalculateNextTargetRequired(&pindexPrev, pindexPrev.nTime - params.nTargetSpacing, params, false);

    // prepare a block index at the reduction height
    CBlockIndex pindexAfter;
    pindexAfter.nHeight = params.nBlockTimeReductionHeight;
    pindexAfter.nTime = pindexPrev.nTime + params.nTargetSpacing;
    pindexAfter.nBits = pindexPrev.nBits;

    unsigned int after = CalculateNextTargetRequired(&pindexAfter, pindexPrev.nTime, params, false);

    arith_uint256 bnBefore; bnBefore.SetCompact(before);
    arith_uint256 bnAfter; bnAfter.SetCompact(after);

    // expected ratio derived from spacing change
    int64_t baseSpacing = params.nTargetSpacing;
    int64_t newSpacing = params.nTargetSpacing / 2;
    int64_t intervalBefore = params.nTargetTimespan / baseSpacing;
    int64_t intervalAfter = params.nTargetTimespan / newSpacing;

    arith_uint256 expectedAfter = bnBefore;
    expectedAfter *= ((intervalAfter - 1) * newSpacing + baseSpacing + baseSpacing);
    expectedAfter /= ((intervalAfter + 1) * newSpacing);

    BOOST_CHECK(bnAfter == expectedAfter);
}

BOOST_AUTO_TEST_CASE(block_reward_halvings)
{
    SelectParams(CBaseChainParams::MAIN);

    CAmount rewardPre = GetProofOfWorkSubsidy(199999);
    CAmount reward1 = GetProofOfWorkSubsidy(200000);
    CAmount reward2 = GetProofOfWorkSubsidy(300000);
    CAmount reward3 = GetProofOfWorkSubsidy(400000);

    BOOST_CHECK_EQUAL(rewardPre, reward1 * 2);
    BOOST_CHECK_EQUAL(reward1, reward2 * 2);
    BOOST_CHECK_EQUAL(reward2, reward3 * 2);
}

BOOST_AUTO_TEST_SUITE_END()

