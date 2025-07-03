#include <boost/test/unit_test.hpp>
#include <p2p/handshake.h>
#include <vector>
#include "test/test_bitcoin.h"

BOOST_FIXTURE_TEST_SUITE(handshake_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(bip324_handshake)
{
    p2p::Handshake initiator;
    p2p::Handshake responder;
    auto i_pub = initiator.GetPublicKey();
    auto r_pub = responder.GetPublicKey();

    auto i_res = initiator.Initiate(r_pub);
    auto r_res = responder.Initiate(i_pub);

    BOOST_CHECK(i_res.encryption_enabled);
    BOOST_CHECK(r_res.encryption_enabled);
    BOOST_CHECK_EQUAL_COLLECTIONS(i_res.send_key.begin(), i_res.send_key.end(), r_res.recv_key.begin(), r_res.recv_key.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(i_res.recv_key.begin(), i_res.recv_key.end(), r_res.send_key.begin(), r_res.send_key.end());

    std::array<unsigned char,12> iv;
    std::array<unsigned char,16> tag;
    std::vector<unsigned char> msg = {0,1,2,3,4,5};
    auto enc = p2p::Handshake::Encrypt(msg, i_res.send_key, iv, tag);
    auto dec = p2p::Handshake::Decrypt(enc, r_res.recv_key, iv, tag);
    BOOST_CHECK_EQUAL_COLLECTIONS(msg.begin(), msg.end(), dec.begin(), dec.end());
}

BOOST_AUTO_TEST_SUITE_END()
