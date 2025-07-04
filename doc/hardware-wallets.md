# Using Hardware Wallets

TheMinerzCoin supports signing transactions with USB hardware wallets.

## Enumerating devices

Run `enumeratehw` via the RPC interface to list attached devices. Each entry
shows the device path and identifying information.

```
$ theminerzcoin-cli enumeratehw
```

## Sending data

Raw APDU messages can be sent to a device with `sendtohw` by passing the device
path and hex encoded data:

```
$ theminerzcoin-cli sendtohw "<device-path>" "<hex-data>"
```

The command returns `{ "sent": true }` on success. Responses are currently not
returned.
