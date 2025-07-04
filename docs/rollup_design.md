# Rollup Architecture Overview

This document outlines the proposed design for integrating a high-TPS sidechain using a rollup mechanism.

## Components

- **BlockCommitment**: Records commitments of aggregated transactions that will later be proven on the main chain.
- **ProofVerifier**: Handles zero-knowledge proof verification for state transitions.

## Flow

1. Transactions are collected off-chain and batched into a rollup block.
2. `BlockCommitment` stores a lightweight commitment to this batch on-chain.
3. A zero-knowledge proof is generated off-chain and submitted with the commitment.
4. `ProofVerifier` validates the proof, finalizing the rollup block.

This architecture allows many off-chain transactions while retaining security through succinct proofs.
