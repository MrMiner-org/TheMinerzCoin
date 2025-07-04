# GraphQL API

The daemon exposes a prototype GraphQL endpoint at `/graphql` served over the existing HTTP server. It is enabled by default and runs on the same port as RPC.

## Running

Start `theminerzcoind` normally and send HTTP `POST` requests containing GraphQL documents to `/graphql`.
For example:

```bash
curl --data '{ block(height: 1) { hash height } }' http://localhost:8332/graphql
```

The available operations mirror existing RPC commands and are defined in [../specs/schema.graphql](../specs/schema.graphql).

