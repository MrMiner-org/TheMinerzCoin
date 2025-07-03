#pragma once
#include <array>
#include <span>
#include <vector>

namespace p2p {
struct HandshakeResult {
    std::array<unsigned char,32> send_key;
    std::array<unsigned char,32> recv_key;
    bool encryption_enabled{false};
};

class Handshake {
public:
    Handshake();
    const std::array<unsigned char,32>& GetPublicKey() const { return m_pubkey; }
    HandshakeResult Initiate(std::span<const unsigned char> peer_pubkey, bool peer_supports_encryption = true);

    static std::vector<unsigned char> Encrypt(std::span<const unsigned char> plaintext,
                                              std::span<const unsigned char,32> key,
                                              std::array<unsigned char,12>& iv_out,
                                              std::array<unsigned char,16>& tag_out);
    static std::vector<unsigned char> Decrypt(std::span<const unsigned char> ciphertext,
                                              std::span<const unsigned char,32> key,
                                              std::span<const unsigned char,12> iv,
                                              std::span<const unsigned char,16> tag);

private:
    std::array<unsigned char,32> m_privkey{};
    std::array<unsigned char,32> m_pubkey{};
};
}
