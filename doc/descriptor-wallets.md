# Descriptor Wallets and PSBTv2

TheMinerzCoin 3.0 ships descriptor based key management along with a
minimal implementation of PSBT version 2.

## Enabling descriptor wallets

Descriptor wallets require SQLite support. Install the `sqlite3`
development package, regenerate the build files and compile:

```bash
./generate_build.sh
./build.sh
```

Start `theminerzcoind` normally. Legacy Berkeley DB wallets remain
usable, but new wallets created with `createwallet` use descriptors when
SQLite is present.

### Importing descriptors

Descriptors are imported with the `importdescriptors` RPC. Pass an array
of descriptor objects:

```bash
theminerzcoin-cli importdescriptors '[{"desc":"wpkh([d34db33f/84h/0h/0h]xpub6CUGRU.../0/*)#zr0q9zl7","timestamp":"now","active":true}]'
```

The command reports whether each descriptor was processed successfully.

## Creating PSBTv2 transactions

Use `walletcreatefundedpsbt` to construct and fund a version 2 PSBT in a
single step:

```bash
theminerzcoin-cli walletcreatefundedpsbt '[{"txid":"<id>","vout":0}]' '{"<address>":0.01}'
```

The result includes the serialized PSBT, change output position and
estimated fee:

```
{
  "psbt": "cHNidP8BAHECAAAAA...",
  "changepos": 1,
  "fee": 0.00000123
}
```

Finalize the PSBT with `walletprocesspsbt` and broadcast it using
`sendrawtransaction`.
