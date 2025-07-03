#include <boost/test/unit_test.hpp>
#include <p2p/handshake.h>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <span>
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

BOOST_AUTO_TEST_CASE(encrypted_transport)
{
    int fds[2];
    BOOST_REQUIRE(socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == 0);
    p2p::Handshake a;
    p2p::Handshake b;
    unsigned char buf[32];
    send(fds[0], a.GetPublicKey().data(), 32, 0);
    recv(fds[1], buf, 32, MSG_WAITALL);
    auto b_res = b.Initiate(std::span<const unsigned char>(buf, 32));
    send(fds[1], b.GetPublicKey().data(), 32, 0);
    recv(fds[0], buf, 32, MSG_WAITALL);
    auto a_res = a.Initiate(std::span<const unsigned char>(buf, 32));

    std::vector<unsigned char> msg = {1,2,3,4};
    std::array<unsigned char,12> iv;
    std::array<unsigned char,16> tag;
    auto cipher = p2p::Handshake::Encrypt(msg, a_res.send_key, iv, tag);
    uint32_t len = msg.size();
    send(fds[0], &len, 4, 0);
    send(fds[0], iv.data(), iv.size(), 0);
    send(fds[0], tag.data(), tag.size(), 0);
    send(fds[0], cipher.data(), cipher.size(), 0);

    uint32_t rlen = 0;
    recv(fds[1], &rlen, 4, MSG_WAITALL);
    std::array<unsigned char,12> iv2; recv(fds[1], iv2.data(), iv2.size(), MSG_WAITALL);
    std::array<unsigned char,16> tag2; recv(fds[1], tag2.data(), tag2.size(), MSG_WAITALL);
    std::vector<unsigned char> cipher2(rlen); recv(fds[1], cipher2.data(), rlen, MSG_WAITALL);
    auto dec = p2p::Handshake::Decrypt(cipher2, b_res.recv_key, iv2, tag2);
    BOOST_CHECK_EQUAL_COLLECTIONS(msg.begin(), msg.end(), dec.begin(), dec.end());
    close(fds[0]);
    close(fds[1]);
}

BOOST_AUTO_TEST_SUITE_END()
