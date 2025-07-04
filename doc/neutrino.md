# Neutrino Mode

The `-spvmode` option starts the node in Neutrino mode. When enabled,
the node downloads BIP158 compact block filters instead of full blocks
which greatly reduces bandwidth usage. This makes it suitable for
resource constrained or mobile environments.

In this mode the wallet verifies transactions against compact filters.
The feature is experimental and a lightweight alternative to full
synchronization.
