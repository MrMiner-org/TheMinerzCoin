#include "proof_verifier.h"
#include "hash.h"

bool ProofVerifier::verify(const uint256& commitment, std::span<const unsigned char> proof)
{
    uint256 proof_hash = Hash(proof.begin(), proof.end());
    return proof_hash == commitment;
}
