# WebSocket Event Server

The node exposes a lightweight WebSocket endpoint broadcasting block and transaction events.
It starts automatically when `theminerzd` runs and binds to port `12345` by default.

## Running

Start the daemon normally. If compiled with `libwebsockets`, the event server
listens on `ws://<node-host>:12345` with no further configuration.

## Configuration

The port is currently fixed in `src/init.cpp`. Adjust it before building if a
different value is required.

## Example

Connect using a WebSocket client such as `websocat`:

```bash
websocat ws://localhost:12345
```

Notifications use the following formats:

```
block:<hash>
tx:<hash>
```
