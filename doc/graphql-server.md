# GraphQL Server

The node exposes a GraphQL endpoint at `/graphql` using the built-in HTTP server. It is enabled automatically when `theminerzcoind` starts and runs on the same port as RPC (default `8332`).

## Querying

Send HTTP `POST` requests containing a GraphQL document to the `/graphql` path. For example:

```bash
curl --data '{ block(height: 1) { hash height } }' http://localhost:8332/graphql
```

The available operations reflect the RPC API and are defined in [../specs/schema.graphql](../specs/schema.graphql). A short overview is also provided in [docs/graphql.md](../docs/graphql.md).
