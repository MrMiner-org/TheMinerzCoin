# Slashing

TheMinerzCoin introduces a lightweight proof-of-stake slashing system. Validators that sign conflicting blocks or remain offline for an extended period will see a portion of their stake reduced.

## Validator behaviour

- **Equivocation** – signing two different blocks for the same height results in an immediate penalty.
- **Offline staking** – validators that do not produce blocks within the configured threshold are penalised.

Slashed stakes are tracked internally. The wallet RPC command below exposes the current status.

## RPC: `getslashinginfo`

```
getslashinginfo
```

Returns information about validators that have been slashed.

Example output:

```
$ theminerzcoin-cli getslashinginfo
[
  {
    "validator": "<validator id>",
    "stake": 1000,
    "slashed": 50
  }
]
```
