#include "taproot.h"
#include <crypto/sha256.h>
#include <hash.h>
#include <schnorr.h>
#include "script/script.h"

namespace Consensus {
bool VerifyTaprootSpend(const CTransaction& tx)
{
    if (tx.vin.empty() || tx.vout.empty()) return false;

    const CTxIn& in = tx.vin[0];
    if (in.scriptSig.size() > MAX_TAPROOT_SCRIPT_ELEMENT_SIZE || in.scriptSig.size() != 64) return false;
    std::array<unsigned char,64> sig;
    std::copy(in.scriptSig.begin(), in.scriptSig.end(), sig.begin());

    const CScript& spk = tx.vout[0].scriptPubKey;
    if (spk.size() > MAX_TAPROOT_SCRIPT_ELEMENT_SIZE || spk.size() != 34 || spk[0] != OP_1) return false;
    unsigned char pk[32];
    memcpy(pk, &spk[1], 32);

    uint256 h = tx.GetHash();
    return crypto::SchnorrVerify(
        std::span<const unsigned char,32>(h.begin(), 32),
        std::span<const unsigned char,32>(pk, 32),
        std::span<const unsigned char,64>(sig.data(), 64));
}
}
