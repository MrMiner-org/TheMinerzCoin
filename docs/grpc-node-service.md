# Node gRPC Service

The node exposes a minimal gRPC server for accessing blockchain data and
broadcasting transactions. It starts automatically when the daemon
invokes `StartNodeGrpcServer`.

## Running

`StartNodeGrpcServer("0.0.0.0:50051")` is called during initialization
from [`src/init.cpp`](../src/init.cpp). Launch `theminerzcoind` normally
and the service will listen on port `50051`.

## RPCs

The service currently implements two RPC methods:

- **GetBlock** – returns the hash and height of the block at a given
  height.
- **BroadcastTransaction** – broadcasts a raw transaction provided in
  hex.

The full protocol definition is available in
[../specs/node.proto](../specs/node.proto).
