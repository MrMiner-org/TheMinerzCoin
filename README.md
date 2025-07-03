TheMinerzCoin
=====================================
[![build](https://github.com/MrMiner-org/TheMinerzCoin/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/MrMiner-org/TheMinerzCoin/actions/workflows/build.yml)

What is TheMinerzCoin?
----------------

TheMinerzCoin is a decentralised digital currency with near-instant transaction speeds and negligible transaction fees built upon Proof of Stake 3.0 (PoSV3, BPoS) as
introduced by the TheMinerzCoin development team.
TheMinerzCoin is the name of open source software which enables the use of this currency. It takes TheMinerzCoin to the next level by building upon
Bitcoin Core 0.13.2 with some patches from newer Bitcoin Core versions to offer performance enhancements, wider compatibility with third party services and a more advanced base.

For more information and downloadable binaries, see https://theminerzcoin.eu/

World-first Features
--------------------

TheMinerzCoin project thrives on new ideas. Highlights include Proof of Stake 3.0, near‑instant transactions and automatic block-time and reward adjustments. See [doc/innovation.md](doc/innovation.md) for details.

Version 3.0 introduces:

- Schnorr/Taproot support (BIP340-342)
- Encrypted P2P transport (BIP324)
- BLS aggregate signatures for staking pools
Architecture
------------
A high-level architecture diagram is provided in [docs/architecture.puml](docs/architecture.puml) illustrating the wallet, RPC, consensus and P2P layers as well as the new BLS staking module.

License
-------

TheMinerzCoin is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/MrMiner-org/TheMinerzCoin/tags) are created
regularly to indicate new official, stable release versions of TheMinerzCoin.

Change log can be found in [CHANGELOG.md](CHANGELOG.md).

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).


Testing
-------

Testing and code review might be the bottleneck for development. Please help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](/doc/unit-tests.md) for new code, and to
submit new unit tests for old code. Unit tests can be built after running `./generate_build.sh`
and executed with: `cmake --build build --target check`

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

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
