# Prometheus Metrics

When built with the `prometheus-cpp` library available, the daemon exposes a `/metrics` endpoint for Prometheus scraping.

## Building

Install `prometheus-cpp` and regenerate the build files. Then compile as usual:

```bash
./generate_build.sh
./build.sh
```

## Scraping

Start `theminerzcoind` normally and visit `http://<node-host>:8332/metrics` to collect metrics. See [docs/metrics.md](../docs/metrics.md) for additional details and a Grafana dashboard.
