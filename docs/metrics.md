# Metrics and Monitoring

The node exposes a Prometheus compatible endpoint at `/metrics` once built with the `prometheus-cpp` library available.

## Building

Ensure `prometheus-cpp` is installed and discoverable by CMake. Regenerate the build files and compile normally:

```bash
./generate_build.sh
./build.sh
```

## Running

Start the daemon as usual. Metrics are served over the existing HTTP server on the same port as RPC.

Visit `http://<node-host>:8332/metrics` to scrape metrics.

## Grafana

Import the dashboard JSON in the `grafana/` directory to visualize common node statistics.
