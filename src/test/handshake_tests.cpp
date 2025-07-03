#include <boost/test/unit_test.hpp>
#include <p2p/handshake.h>
#include <vector>
#include "test/test_bitcoin.h"

BOOST_FIXTURE_TEST_SUITE(handshake_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(bip324_handshake)
{
    p2p::Handshake hs;
    std::array<unsigned char,32> peer{};
    auto res = hs.Initiate(peer);
    BOOST_CHECK(res.session_key.size() == 32);
}

BOOST_AUTO_TEST_SUITE_END()
