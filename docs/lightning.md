# Lightning/State-Channels Bridge

This pilot module allows `theminerzcoind` to interact with an external
[LND](https://github.com/lightningnetwork/lnd) instance via gRPC. The
feature is experimental and must be explicitly enabled at build time.

## Building

Enable the module by passing `-DWITH_LIGHTNING=ON` to CMake. The build
expects gRPC and the LND protobuf definitions to be available on your
system. Example:

```bash
cmake -DWITH_LIGHTNING=ON ..
make
```

## Configuration

Use the `-lndconnect` option to specify the gRPC address of your LND
node. By default the client connects to `localhost:10009`.
TLS credentials can be supplied via three additional options:

* `-lndcacert=<file>` – path to the server CA certificate
* `-lndcert=<file>` – path to your client certificate
* `-lndkey=<file>` – path to the corresponding private key

Example:

```
theminerzcoind -lndconnect=127.0.0.1:10009 \
               -lndcacert=/path/to/ca.crt \
               -lndcert=/path/to/client.crt \
               -lndkey=/path/to/client.key
```

```
theminerzcoind -lndconnect=127.0.0.1:10009
```

## Wallet RPC commands

When built with lightning support three new wallet RPC commands become
available:

- `openchannel "node_pubkey" amount` – open a channel with `amount`
  satoshis.
- `closechannel "txid:index"` – close the specified channel.
- `fundchannel "node_pubkey" amount` – create the funding transaction
  but do not broadcast it.

These commands delegate to the connected LND instance and return an
error if the request fails.
