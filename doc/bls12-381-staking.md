# BLS12-381 Staking

Staking pools in TheMinerzCoin 3.0 use BLS12-381 aggregate signatures. The core library now exposes utilities in `crypto/bls_aggregate` for combining signatures. This allows pool members to combine their staking weight while producing a single signature on the block.

## Enabling staking

Staking remains controlled by the existing `-staking` option. Ensure your wallet is unlocked and run the daemon with staking enabled (the default).

## Pool operation

Pool operators share an aggregate public key with participants. Individual wallets sign their stake with a partial BLS signature which the pool combines before broadcasting.

## Compatibility

Existing standalone staking continues to function. BLS aggregation only applies when wallets join a pool.
