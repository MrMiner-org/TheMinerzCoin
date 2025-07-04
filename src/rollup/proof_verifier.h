#ifndef THEMZ_ROLLUP_PROOF_VERIFIER_H
#define THEMZ_ROLLUP_PROOF_VERIFIER_H

#include <span>
#include "uint256.h"

class ProofVerifier {
public:
    ProofVerifier() = default;

    /**
     * Verify a zero-knowledge proof against a stored commitment.
     * In this toy implementation the proof is hashed and compared
     * against the commitment value.
     */
    bool verify(const uint256& commitment, std::span<const unsigned char> proof);
};

#endif // THEMZ_ROLLUP_PROOF_VERIFIER_H
