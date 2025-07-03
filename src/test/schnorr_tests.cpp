#include <boost/test/unit_test.hpp>
#include "test/test_bitcoin.h"
#include <schnorr.h>

BOOST_FIXTURE_TEST_SUITE(schnorr_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(sign_verify)
{
    unsigned char msg[32]{};
    CKey key;
    key.MakeNewKey(true);
    auto sig = crypto::SchnorrSign(std::span<const unsigned char,32>(msg,32),
                                   std::span<const unsigned char,32>(key.begin(),32));
    bool ok = crypto::SchnorrVerify(std::span<const unsigned char,32>(msg,32),
                                   std::span<const unsigned char,32>(key.GetPubKey().begin()+1,32), sig);
    BOOST_CHECK(ok);
}

BOOST_AUTO_TEST_SUITE_END()
