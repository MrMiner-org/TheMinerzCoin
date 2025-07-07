# Fuzzing

This repository includes a few libFuzzer based targets used to stress-test
parsers and the script interpreter.

## Targets

- `tx_deser_fuzz` – deserializes random data as a transaction.
- `block_deser_fuzz` – deserializes random data as a block.
- `script_interpreter_fuzz` – invokes the script interpreter on random scripts.

## Building

Compile the fuzzers with libFuzzer and the AddressSanitizer enabled:

```bash
cmake -S . -B fuzz_build \
  -DCMAKE_CXX_FLAGS="-fsanitize=fuzzer,address" \
  -DCMAKE_C_FLAGS="-fsanitize=fuzzer,address"
cmake --build fuzz_build -j$(nproc) \
  --target tx_deser_fuzz block_deser_fuzz script_interpreter_fuzz
```

Replace `address` with `undefined` to build with the Undefined Behavior
Sanitizer instead.

## Running

Execute any of the fuzzers directly and optionally provide a corpus directory or
`-runs=<n>` to limit executions:

```bash
./fuzz_build/src/test/fuzz/tx_deser_fuzz corpus/ -runs=1
```

The same applies to `block_deser_fuzz` and `script_interpreter_fuzz`.
