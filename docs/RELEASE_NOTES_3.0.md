# TheMinerzCoin 3.0 Release Notes

Major Features
--------------
- Activation of Taproot and Schnorr signatures (BIP340-BIP342)
- Encrypted P2P transport via BIP324
- BLS12-381 aggregate signatures for staking pools
- Dandelion++ transaction relay for improved privacy
- Compact Block v2 and assume-utxo snapshots for faster initial sync
- Optional Lightning channels through an LND bridge
- zk-rollup sidechain prototype
- Modularised CMake build system with C++20 (`std::span`, `std::simd`)
- Fuzzing targets and sanitizer enabled CI
- Rust bindings for secp256k1 based cryptography
- Descriptor wallets, PSBTv2 and native hardware wallet support
- GraphQL/gRPC APIs and WebSocket events
- Neutrino SPV light client mode
- Docker release images and Prometheus metrics
- OpenAPI 3.1 specification for RPC/REST

This release bumps the network protocol and database versions. Upgrading nodes
will perform a one-time reindex.
## Enabling new functionality

* Taproot and Schnorr support activate automatically once the network reaches the defined signalling threshold. No configuration is necessary. Wallets may generate Taproot receiving addresses using `getnewaddress "" "bech32"`.
* The encrypted P2P handshake (BIP324) is on by default. Use `-p2pnoencrypt` if you must disable it for testing.
* BLS12-381 staking uses the existing `-staking` option. Join a pool by registering its aggregate public key with your wallet software.
* Dandelion++ transaction relay is enabled by default. Use `-dandelion=0` to disable it if desired.

### Upgrade considerations

Running 3.0 for the first time will trigger a database reindex due to new consensus rules. Back up `wallet.dat` before upgrading. Nodes that have not upgraded will continue to run but cannot enforce Taproot or encrypted transport.
