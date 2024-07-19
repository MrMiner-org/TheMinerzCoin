# Changelog

## v1.1.3 (2024-07-13)

- Create V2 transactions by default
- Disconnect from peers older than version 70015
- Increased DEFAULT_MIN_RELAY_TX_FEE to 100000

## v1.1.2 (2024-03-01)
- Set mainnet hard fork date to April 24, 2024
- Adjusted minimum fee calculations
- Added working Nodes

## v1.1.1 (2023-12-16)
- Added new Logo
- Updated DBD repo Link
- Fixed Do not split rewards if vDevFundAddress is empty

## v1.1.0 (2023-10-06)
- Added Reward change on Block 11500 [PoW 10 TMC - PoS 25 TMC]

## v1.0.4 (2023-10-04)
- Added working Nodes

## v1.0.3 (2023-09-14)
- Remove Bitcoin init files
- Update doc/init.md
- Use chainActive.Tip() instead of pindexBestHeader
- [build] [macos] missing background.tiff file
- Reduced the minimum fee after a fork
- Fixed a bug in the derivation of TxTime that could potentially lead to unplanned hard forks
- Fixed a segfault issue occurring during the initial sync
 
## v1.0.2 (2023-09-11)
- Fixed Windows Wallet not close in Systemtray
- Fixed Windows Wallet only runs as Background service when close
- Added Pictures for Qt Wallets

## v1.0.1 (2023-09-06)
- Changed Algorithm from x11 to Scrypt
- Removed Masternodes function
- Added Proof of Stake 3.0 (PoSV3, BPoS)

## v1.0.0 (2023-08-28)
- Changed versioning (backport of Core's PR20223)
- Testnet hard fork: Removed transaction timestamp
- Testnet hard fork: Increased transaction fees and set minimum transaction fee of 0.001 BLK
- Testnet hard fork: Enabled relative timelocks (OP_CHECKSEQUENCEVERIFY, BIP62, 112 and 113)
- Enabled compact block relay protocol (BIP152)
- Added an option to donate the specified percentage of staking rewards to the dev fund (20% by default)
- Set default MAX_OP_RETURN_RELAY to 223
- Removed `sendfreetransactions` argument
- Get rid of `AA_EnableHighDpiScaling` warning (backport of Core's PR16254)
- Updated multiple dependencies
- Updated leveldb, which should resolve the "missing UTXO" staking issue
- Updated dependencies and ported build system from Bitcoin Core 0.20+
- Updated crypto and added CRC32 for ARM64
- Updated univalue to v1.0.3
- Updated to Qt v5.12.11
- Updated to OpenSSL v1.1.1m
- Added "getstakereport" RPC call
- Added --use-sse2 to enable SSE2
- Code cleanup (headers, names, etc)
- Immediately ban clients operating on forked chains older than nMaxReorganizationDepth
- Fixed IsDust() policy to allow atomic swaps
- Updated fixed seeds for mainnet and testnet
- Updated dependencies for MacOS
- Dust mitigation in mempool (by JJ12880 from Radium Core) 
- Compile on MacOS Catalina
- Cross-compile MacOS with Xcode 11.3.1
- Updated dependencies for Windows x64, Linux x64, MacOS, ARM64, ARMv7
- Sign/verify compatibility with legacy clients 
- Increased dbcache to 450MB
- Disabled stake cache for now
- Updated fixed seeds for mainnet and testnet
- Fix staking memory leak (by JJ12880 from Radium Core)
- Updated fixed seeds
- Added secondary TheMinerzCoin DNS seeder
- Updated Berkeley DB to 6.2.38
- Updated OpenSSL to 1.0.2u
- Updated fixed seeds
- Changed default port
- Updated fixed seeds
- Added burn RPC call
- Set default MAX_OP_RETURN_RELAY to 15000
- Removed unit selector from status bar
- Updated fixed seeds
- Some small fixes and refactorings
- Fixed wrongly displayed balances in GUI and RPC
- Added header spam filter (fake stake vulnerability fix)
- Added total balance in RPC call getwalletinfo
- Updated dependencies
- Updated fixed seeds
- Some small fixes and updates
- Fixed walletpassphrase RPC call (wallet now can be unlocked for staking only)
- Allowed connections from peers with protocol version 60016
- Disabled BIP 152
- Updated to Bitcoin Core 0.13.2
- Some small fixes and updates from Bitcoin Core 0.14.x branch
- Fixed testnet and regtest
- Added Qt 5.9 support for cross-compile
- Added Qt support for ARMv7
- Added out-of-sync modal window (backport of Core's PR8371, PR8802, PR8805, PR8906, PR8985, PR9088, PR9461, PR9462)
- Added support for nested commands and simple value queries in RPC console (backport of Core's PR7783)
- Added abortrescan RPC call (backport of Core's PR10208)
- Added reservebalance RPC call
- Removed SegWit
- Removed replace-by-fee
- Removed address indexes
- Removed relaying of double-spends
- Removed drivechain support using OP_COUNT_ACKS
- Proof-of-stake related code optimized and refactored
- Some small fixes and updates from Bitcoin Core 0.13.x branch
- Added use available balance button in send coins dialog (backport of Core's PR11316)
- Added a button to open the config file in a text editor (backport of Core's PR9890)
- Added uptime RPC call (backport of Core's PR10400)
- Removed P2P alert system (backport of Core's PR7692)