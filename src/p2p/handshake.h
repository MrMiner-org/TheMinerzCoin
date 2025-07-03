#pragma once
#include <array>
#include <span>

namespace p2p {
struct HandshakeResult {
    std::array<unsigned char,32> session_key;
};

class Handshake {
public:
    HandshakeResult Initiate(std::span<const unsigned char> peer_pubkey);
};
}
