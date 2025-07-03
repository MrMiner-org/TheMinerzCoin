#include "handshake.h"
#include <openssl/sha.h>

namespace p2p {
std::array<unsigned char, 32> Handshake::Initiate(std::span<const unsigned char> peer_pubkey) {
    std::array<unsigned char, 32> out{};
    SHA256(peer_pubkey.data(), peer_pubkey.size(), out.data());
    return out;
}
}
