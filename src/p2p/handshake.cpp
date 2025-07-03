#include "handshake.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <cstring>

namespace p2p {

Handshake::Handshake()
{
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_X25519, nullptr);
    EVP_PKEY* pkey = nullptr;
    if (ctx && EVP_PKEY_keygen_init(ctx) > 0 && EVP_PKEY_keygen(ctx, &pkey) > 0) {
        size_t len = m_privkey.size();
        EVP_PKEY_get_raw_private_key(pkey, m_privkey.data(), &len);
        len = m_pubkey.size();
        EVP_PKEY_get_raw_public_key(pkey, m_pubkey.data(), &len);
    }
    if (pkey) EVP_PKEY_free(pkey);
    if (ctx) EVP_PKEY_CTX_free(ctx);
}

static void DeriveKeys(const unsigned char* secret, size_t secret_len,
                       std::array<unsigned char,32>& send_key,
                       std::array<unsigned char,32>& recv_key)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(secret, secret_len, hash);
    std::memcpy(send_key.data(), hash, 32);
    SHA256(hash, 32, hash);
    std::memcpy(recv_key.data(), hash, 32);
}

HandshakeResult Handshake::Initiate(std::span<const unsigned char> peer_pubkey, bool peer_supports_encryption)
{
    HandshakeResult res{};
    if (!peer_supports_encryption || peer_pubkey.size() != 32) {
        res.encryption_enabled = false;
        return res;
    }
    EVP_PKEY* priv = EVP_PKEY_new_raw_private_key(EVP_PKEY_X25519, nullptr, m_privkey.data(), m_privkey.size());
    EVP_PKEY* peer = EVP_PKEY_new_raw_public_key(EVP_PKEY_X25519, nullptr, peer_pubkey.data(), peer_pubkey.size());
    if (!priv || !peer) {
        if (priv) EVP_PKEY_free(priv);
        if (peer) EVP_PKEY_free(peer);
        return res;
    }
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(priv, nullptr);
    size_t secret_len = 32;
    unsigned char secret[32];
    if (ctx && EVP_PKEY_derive_init(ctx) > 0 && EVP_PKEY_derive_set_peer(ctx, peer) > 0 &&
        EVP_PKEY_derive(ctx, secret, &secret_len) > 0) {
        DeriveKeys(secret, secret_len, res.send_key, res.recv_key);
        res.encryption_enabled = true;
    }
    if (ctx) EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(priv);
    EVP_PKEY_free(peer);
    return res;
}

std::vector<unsigned char> Handshake::Encrypt(std::span<const unsigned char> plaintext,
                                              std::span<const unsigned char,32> key,
                                              std::array<unsigned char,12>& iv_out,
                                              std::array<unsigned char,16>& tag_out)
{
    RAND_bytes(iv_out.data(), iv_out.size());
    std::vector<unsigned char> ciphertext(plaintext.size());
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int len = 0;
    EVP_EncryptInit_ex(ctx, EVP_chacha20_poly1305(), nullptr, nullptr, nullptr);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, iv_out.size(), nullptr);
    EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(), iv_out.data());
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    int total = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + total, &len);
    total += len;
    ciphertext.resize(total);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, tag_out.size(), tag_out.data());
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext;
}

std::vector<unsigned char> Handshake::Decrypt(std::span<const unsigned char> ciphertext,
                                              std::span<const unsigned char,32> key,
                                              std::span<const unsigned char,12> iv,
                                              std::span<const unsigned char,16> tag)
{
    std::vector<unsigned char> plaintext(ciphertext.size());
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int len = 0;
    EVP_DecryptInit_ex(ctx, EVP_chacha20_poly1305(), nullptr, nullptr, nullptr);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, iv.size(), nullptr);
    EVP_DecryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data());
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size());
    int total = len;
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, tag.size(), const_cast<unsigned char*>(tag.data()));
    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + total, &len) <= 0) {
        plaintext.clear();
    } else {
        total += len;
        plaintext.resize(total);
    }
    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

} // namespace p2p
