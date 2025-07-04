#include <boost/test/unit_test.hpp>
#include "rollup/block_commitment.h"
#include "rollup/proof_verifier.h"

BOOST_AUTO_TEST_SUITE(rollup_tests)

BOOST_AUTO_TEST_CASE(commit_and_verify)
{
    BlockCommitment bc;
    std::vector<unsigned char> data{'h','e','l','l','o'};
    bc.record(data);
    BOOST_REQUIRE_EQUAL(bc.GetCommitments().size(), 1u);

    ProofVerifier verifier;
    BOOST_CHECK(verifier.verify(bc.GetCommitments()[0], data));

    std::vector<unsigned char> wrong{'b','a','d'};
    BOOST_CHECK(!verifier.verify(bc.GetCommitments()[0], wrong));
}

BOOST_AUTO_TEST_SUITE_END()
