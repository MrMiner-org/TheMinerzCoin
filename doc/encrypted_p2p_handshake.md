# Encrypted P2P Transport

TheMinerzCoin 3.0 implements the BIP324 encrypted transport protocol. All connections use an encrypted handshake when both peers support it.

## Usage

No manual configuration is necessary. The feature is negotiated automatically during the version handshake.

If you need to disable encrypted transport for debugging or compatibility testing, start the node with `-p2pnoencrypt`.

If the encrypted handshake fails, the connection now falls back to plaintext
instead of being dropped.

## Verification

The connection type can be inspected with `getpeerinfo`; encrypted peers show `"bip324": true` in their capabilities list.
