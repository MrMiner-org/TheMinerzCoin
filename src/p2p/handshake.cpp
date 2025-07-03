#include "handshake.h"
#include <openssl/sha.h>

namespace p2p {
HandshakeResult Handshake::Initiate(std::span<const unsigned char> peer_pubkey)
{
    HandshakeResult res{};
    // Placeholder for BIP324 handshake: derive shared session key
    SHA256(peer_pubkey.data(), peer_pubkey.size(), res.session_key.data());
    return res;
}
}
