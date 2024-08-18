TheMinerzCoin 
=====================================
[![build](https://github.com/CoinBlack/blackcoin-more/actions/workflows/build.yml/badge.svg?branch=26.x)](https://github.com/CoinBlack/blackcoin-more/actions/workflows/build.yml)

https://theminerzcoin.eu/

What is TheMinerzCoin?
----------------

TheMinerzCoin is a decentralised digital currency with near-instant transaction speeds and negligible transaction fees built upon Proof of Stake 3.1 (PoSV3, BPoS) as introduced by the TheMinerzCoin development team.

What is TheMinerzCoin ?
----------------

TheMinerzCoin  is the name of open source software which enables use of the TheMinerzCoin protocol.
It connects to the TheMinerzCoin peer-to-peer network to download and fully
validate blocks and transactions. It also includes a wallet and graphical user
interface, which can be optionally built.

For more information, as well as an immediately usable, binary version of
the TheMinerzCoin  software, see https://theminerzcoin.eu/.

License
-------

TheMinerzCoin  is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built (see `doc/build-*.md` for instructions) and tested. [Tags](https://github.com/MrMiner-org/TheMinerzCoin/tags) are created
regularly to indicate new official, stable release versions of TheMinerzCoin .

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md)
and useful hints for developers can be found in [doc/developer-notes.md](doc/developer-notes.md).

The best place to get started is to join TheMinerzCoin Discord: https://discord.gg/s7pM5ChykY

Testing
-------

Testing and code review might be the bottleneck for development. Please help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The CI (Continuous Integration) systems make sure that every pull request is built for Windows, Linux, and macOS,
and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

Changes to translations as well as new translations can be submitted to
[Bitcoin Core's Transifex page](https://www.transifex.com/bitcoin/bitcoin/).

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

Branches
-------

### master
The master branch gets latest updates from the stable branch.
However, it may contain experimental features and should be used with caution.

### 2.x
The release branch for TheMinerzCoin  26.x. Contains functional but highly experimental code.
