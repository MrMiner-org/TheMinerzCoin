# Using Taproot and Schnorr Signatures

This release activates BIP340-342 which introduce Schnorr signatures and Taproot outputs. Nodes running TheMinerzCoin 3.0 automatically negotiate the necessary consensus rules and start signalling support as soon as they upgrade.

## Creating Taproot addresses

1. Start a fully synchronised 3.0 wallet.
2. Use `getnewaddress "" "bech32"` from `theminerzcoin-cli` to generate a new Taproot (P2TR) address.
3. Funds sent to the new address will use Schnorr signatures and remain spendable with previous wallet backups.

## Sending to Taproot addresses

Use `sendtoaddress` or any standard wallet functionality. Nodes that have upgraded will relay and mine Taproot spends without additional configuration.

## Soft fork activation

Activation follows the BIP9 style process. You can inspect the status with `getblockchaininfo` under the `softforks` section. No manual steps are required; upgraded nodes participate automatically.
