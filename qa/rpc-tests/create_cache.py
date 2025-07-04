#!/usr/bin/env python3
# Copyright (c) 2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
# Helper script to create the cache
# (see BitcoinTestFramework.setup_chain)
#

import os
import shutil

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import (
    MAX_NODES,
    connect_nodes,
    disable_mocktime,
    enable_mocktime,
    get_mocktime,
    initialize_datadir,
    log_filename,
    set_node_times,
    start_nodes,
    stop_nodes,
    sync_blocks,
)


class CreateCache(BitcoinTestFramework):

    def __init__(self):
        super().__init__()

        # Test network and test nodes are not required:
        self.num_nodes = 0
        self.nodes = []

    def setup_network(self):
        # Create clean data directories for the cache and start the nodes
        self.num_nodes = MAX_NODES

        # Ensure no stale cache directories remain
        for i in range(self.num_nodes):
            cachedir = os.path.join("cache", "node" + str(i))
            if os.path.isdir(cachedir):
                shutil.rmtree(cachedir)
            initialize_datadir("cache", i)

        # Start nodes using the cache datadirs
        self.nodes = start_nodes(self.num_nodes, "cache")
        for i in range(1, self.num_nodes):
            connect_nodes(self.nodes[i], 0)
        self.is_network_split = False

    def run_test(self):
        """Generate a cached blockchain used by the RPC tests."""

        enable_mocktime()
        block_time = get_mocktime() - (201 * 10 * 60)

        # Create a 200 block chain. Only the first four nodes generate coins
        for _ in range(2):
            for peer in range(4):
                for _ in range(25):
                    set_node_times(self.nodes, block_time)
                    self.nodes[peer].generate(1)
                    block_time += 10 * 60
                sync_blocks(self.nodes)

        disable_mocktime()
        stop_nodes(self.nodes)
        self.nodes = []

        # Remove logs to keep the cache small and consistent
        for i in range(self.num_nodes):
            for log in ["debug.log", "db.log", "peers.dat", "fee_estimates.dat"]:
                try:
                    os.remove(log_filename("cache", i, log))
                except OSError:
                    pass


if __name__ == "__main__":
    CreateCache().main()
