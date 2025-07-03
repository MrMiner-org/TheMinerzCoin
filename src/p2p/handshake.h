#pragma once
#include <array>
#include <span>

namespace p2p {
class Handshake {
public:
    std::array<unsigned char, 32> Initiate(std::span<const unsigned char> peer_pubkey);
};
}
