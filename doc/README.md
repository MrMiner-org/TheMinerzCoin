TheMinerzCoin
=============

Setup
---------------------
TheMinerzCoin is a TheMinerzCoin client and it builds the backbone of the network. However, it downloads and stores the entire history of TheMinerzCoin transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download TheMinerzCoin, visit [theminerzcoin.eu](https://theminerzcoin.eu/).

Running
---------------------
The following are some helpful notes on how to run TheMinerzCoin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/theminerzcoin-qt` (GUI) or
- `bin/theminerzcoind` (headless)

### Windows

Unpack the files into a directory, and then run theminerzcoin-qt.exe.

### OS X

Drag TheMinerzCoin-More.app to your applications folder, and then run TheMinerzCoin-More.

### Need Help?

* See the documentation at the [Bitcoin Wiki](https://en.bitcoin.it/wiki/Main_Page)
for help and more information.
* Ask for help in [TheMinerzCoin Discord server](https://discord.gg/hjNUgWD).
* Ask for help in [TheMinerzCoin room](https://gitter.im/TheMinerzCoin_Hub) on Gitter.
* Ask for help in [/r/theminerzcoin/](https://nm.reddit.com/r/theminerzcoin/) on Reddit.
* Ask for help on the [BitcoinTalk](https://bitcointalk.org/) forums, in the [TheMinerzCoin topic](https://bitcointalk.org/index.php?topic=3017838.new#new).

Building
---------------------
The following are developer notes on how to build TheMinerzCoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The TheMinerzCoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [RPC/REST OpenAPI Specification](../specs/openapi.yaml)
- [GraphQL Schema](../specs/schema.graphql)
- [GraphQL API](../docs/graphql.md)
- [GraphQL Server](graphql-server.md)
- [WebSocket Event Server](websockets.md)
- [Prometheus Metrics](prometheus-metrics.md)
- [Node gRPC Service](grpc-node-service.md)
- [Fuzzing](fuzzing.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Taproot and Schnorr](taproot_schnorr.md)
- [Encrypted P2P Transport](encrypted_p2p_handshake.md)
- [BLS12-381 Staking](bls12-381-staking.md)
- [Dandelion++ Transaction Relay](dandelion.md)
- [Descriptor Wallets and PSBTv2](descriptor-wallets.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [BitcoinTalk](https://bitcointalk.org/) forums, in the [TheMinerzCoin topic](https://bitcointalk.org/index.php?topic=3017838.new#new).
* Discuss TheMinerzCoin development in [TheMinerzCoin room](https://gitter.im/TheMinerzCoin_Hub) on Gitter.
* Discuss TheMinerzCoin development in [TheMinerzCoin team](https://keybase.io/team/theminerzcoin) on Keybase.

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
