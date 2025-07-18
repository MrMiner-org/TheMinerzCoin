TheMinerzCoin
=====================================
[![build](https://github.com/MrMiner-org/TheMinerzCoin/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/MrMiner-org/TheMinerzCoin/actions/workflows/build.yml)

What is TheMinerzCoin?
----------------

TheMinerzCoin is a decentralised digital currency with near-instant transaction speeds and negligible transaction fees built upon Proof of Stake 3.0 (PoSV3, BPoS) as
introduced by the TheMinerzCoin development team.
TheMinerzCoin is the name of open source software which enables the use of this currency. It takes TheMinerzCoin to the next level by building upon
Bitcoin Core 25.x with some patches from newer Bitcoin Core versions to offer performance enhancements, wider compatibility with third party services and a more advanced base.

For more information and downloadable binaries, see https://theminerzcoin.eu/

World-first Features
--------------------

TheMinerzCoin project thrives on new ideas. Highlights include Proof of Stake 3.0, near‑instant transactions and automatic block-time and reward adjustments. See [docs/innovation.md](docs/innovation.md) for details.

Version 3.0 introduces:

- Schnorr/Taproot support (BIP340-342)
- Encrypted P2P transport (BIP324)
- BLS aggregate signatures for staking pools
- Dandelion++ transaction relay for improved privacy
- Lightweight slashing to penalise equivocation and offline validators ([docs/slashing.md](docs/slashing.md))
- Compact Block **v2** and assume-utxo snapshots for faster syncing
- Optional Lightning channels via an LND bridge ([docs/lightning.md](docs/lightning.md))
- Experimental zk-rollup sidechain ([docs/rollup_design.md](docs/rollup_design.md))
- Modularised CMake build using C++20 features (`std::span`, `std::simd`)
- Fuzz targets and sanitizer-based CI ([docs/fuzzing.md](docs/fuzzing.md))
- Rust bindings for critical crypto routines under `rust/`
- Descriptor wallets and PSBTv2 support ([docs/descriptor-wallets.md](docs/descriptor-wallets.md))
- Native hardware wallet interface ([docs/hardware-wallets.md](docs/hardware-wallets.md))
- GraphQL/gRPC APIs and WebSocket event streams
- Neutrino SPV light client mode ([docs/neutrino.md](docs/neutrino.md))
- Docker release images and Prometheus metrics ([docs/metrics.md](docs/metrics.md))
- OpenAPI 3.1 specification for RPC/REST ([specs/openapi.yaml](specs/openapi.yaml))

Usage
-----
Bootstrap a node from a UTXO snapshot by supplying the `-assumeutxodat` flag on
startup:

```
theminerzcoind -assumeutxodat=/path/to/utxo-snapshot.dat
```

When peers communicate over the default BIP324 encrypted transport, block relay
uses compact block **v2** automatically. Disable encryption with `-p2pnoencrypt`
to fall back to version 1 if needed.
The RPC interface can control USB hardware wallets; see [docs/hardware-wallets.md](docs/hardware-wallets.md).
Architecture
------------
A high-level architecture diagram is provided in [docs/architecture.puml](docs/architecture.puml) illustrating the wallet, RPC, consensus and P2P layers as well as the new BLS staking module.

Deterministic dependencies
--------------------------
Build pinned versions of all required libraries with the depends system:

```bash
make -C depends HOST=x86_64-linux-gnu
```

Then point CMake at the generated prefix when configuring:

```bash
./generate_build.sh -DCMAKE_PREFIX_PATH=$(pwd)/depends/x86_64-linux-gnu
```

Note: These helper scripts rely on Bash. If `/bin/sh` is not Bash on your
system, invoke them explicitly with `bash ./generate_build.sh`.

See [depends/README.md](depends/README.md) for more advanced options and cross-compilation details.

To build everything in one go using Conan and CMake:

```bash
mkdir build && cd build && conan install .. --output-folder=. --build=missing
cmake .. -DWITH_GUI=OFF -DWITH_RUST=OFF
cmake --build . --target package -j$(nproc)
```

License
-------

TheMinerzCoin is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/MrMiner-org/TheMinerzCoin/tags) are created
regularly to indicate new official, stable release versions of TheMinerzCoin.

Change log can be found in [CHANGELOG.md](docs/CHANGELOG.md).

The contribution workflow is described in [CONTRIBUTING.md](docs/CONTRIBUTING.md).


Testing
-------

Testing and code review might be the bottleneck for development. Please help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](/docs/unit-tests.md) for new code, and to
submit new unit tests for old code. Unit tests can be built after running `./generate_build.sh`
and executed with: `cmake --build build --target check`

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The ZMQ-based tests additionally require the `pyzmq` Python package.

GitHub Actions build every pull request on Linux, macOS and Windows and run the unit and sanity tests automatically. The workflow can be executed locally using [act](https://github.com/nektos/act) with `act -j build`.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

### API specifications

The RPC/REST API—covering wallet management, staking operations and network
statistics—is documented in [specs/openapi.yaml](specs/openapi.yaml). A prototype
GraphQL schema describing the same functionality lives in
[specs/schema.graphql](specs/schema.graphql).
A lightweight WebSocket event server is also available; see
[docs/websockets.md](docs/websockets.md).
A simple gRPC node service can also be started; see
[docs/grpc-node-service.md](docs/grpc-node-service.md).
More information on descriptor wallets and PSBTv2 is provided in
[docs/descriptor-wallets.md](docs/descriptor-wallets.md).
