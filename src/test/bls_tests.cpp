#include <boost/test/unit_test.hpp>
#include "test/test_bitcoin.h"
#include <crypto/bls_aggregate.h>

BOOST_FIXTURE_TEST_SUITE(bls_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(aggregate)
{
    bls::Signature s1{};
    bls::Signature s2{};
    s1.data[0] = 1;
    s2.data[0] = 2;
    auto out = bls::Aggregate({s1,s2});
    BOOST_CHECK(out.data[0] == 3);
}

BOOST_AUTO_TEST_SUITE_END()
