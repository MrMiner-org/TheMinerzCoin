#!/usr/bin/env python3
"""In-memory storage helpers for blocks and transactions."""

# Copyright (c) 2015-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
# BlockStore: a helper class that keeps a map of blocks and implements
#             helper functions for responding to getheaders and getdata,
#             and for constructing a getheaders message


import dbm.dumb as dbmd
from io import BytesIO

from .mininode import *


class BlockStore(object):
    def __init__(self, datadir):
        self.block_db = dbmd.open(datadir + "/blocks", 'c')
        self.current_block = 0
        self.headers_map = dict()

    def close(self):
        self.block_db.close()

    def erase(self, blockhash):
        del self.block_db[repr(blockhash)]

    # lookup an entry and return the item as raw bytes
    def get(self, blockhash):
        value = None
        try:
            value = self.block_db[repr(blockhash)]
        except KeyError:
            return None
        return value

    # lookup an entry and return it as a CBlock
    def get_block(self, blockhash):
        ret = None
        serialized_block = self.get(blockhash)
        if serialized_block is not None:
            f = BytesIO(serialized_block)
            ret = CBlock()
            ret.deserialize(f)
            ret.calc_sha256()
        return ret

    def get_header(self, blockhash):
        try:
            return self.headers_map[blockhash]
        except KeyError:
            return None

    # Note: this pulls full blocks out of the database just to retrieve
    # the headers -- perhaps we could keep a separate data structure
    # to avoid this overhead.
    def headers_for(self, locator, hash_stop, current_tip=None):
        if current_tip is None:
            current_tip = self.current_block
        current_block_header = self.get_header(current_tip)
        if current_block_header is None:
            return None

        response = msg_headers()
        headers_list = [current_block_header]
        maxheaders = 2000
        while headers_list[0].sha256 not in locator.vHave:
            prev_block_hash = headers_list[0].hashPrevBlock
            prev_block_header = self.get_header(prev_block_hash)
            if prev_block_header is not None:
                headers_list.insert(0, prev_block_header)
            else:
                break
        headers_list = headers_list[:maxheaders]  # truncate if we have too many
        hash_list = [x.sha256 for x in headers_list]
        index = len(headers_list)
        if hash_stop in hash_list:
            index = hash_list.index(hash_stop) + 1
        response.headers = headers_list[:index]
        return response

    def add_block(self, block):
        block.calc_sha256()
        try:
            self.block_db[repr(block.sha256)] = bytes(block.serialize())
        except TypeError as e:
            print("Unexpected error: ", sys.exc_info()[0], e.args)
        self.current_block = block.sha256
        self.headers_map[block.sha256] = CBlockHeader(block)

    def add_header(self, header):
        self.headers_map[header.sha256] = header

    # lookup the hashes in "inv", and return p2p messages for delivering
    # blocks found.
    def get_blocks(self, inv):
        responses = []
        for i in inv:
            if (i.type == 2): # MSG_BLOCK
                data = self.get(i.hash)
                if data is not None:
                    # Use msg_generic to avoid re-serialization
                    responses.append(msg_generic(b"block", data))
        return responses

    def get_locator(self, current_tip=None):
        if current_tip is None:
            current_tip = self.current_block
        r = []
        counter = 0
        step = 1
        last_block = self.get_block(current_tip)
        while last_block is not None:
            r.append(last_block.hashPrevBlock)
            for i in range(step):
                last_block = self.get_block(last_block.hashPrevBlock)
                if last_block is None:
                    break
            counter += 1
            if counter > 10:
                step *= 2
        locator = CBlockLocator()
        locator.vHave = r
        return locator

class TxStore(object):
    def __init__(self, datadir):
        self.tx_db = dbmd.open(datadir + "/transactions", 'c')

    def close(self):
        self.tx_db.close()

    # lookup an entry and return the item as raw bytes
    def get(self, txhash):
        value = None
        try:
            value = self.tx_db[repr(txhash)]
        except KeyError:
            return None
        return value

    def get_transaction(self, txhash):
        ret = None
        serialized_tx = self.get(txhash)
        if serialized_tx is not None:
            f = BytesIO(serialized_tx)
            ret = CTransaction()
            ret.deserialize(f)
            ret.calc_sha256()
        return ret

    def add_transaction(self, tx):
        tx.calc_sha256()
        try:
            self.tx_db[repr(tx.sha256)] = bytes(tx.serialize())
        except TypeError as e:
            print("Unexpected error: ", sys.exc_info()[0], e.args)

    def get_transactions(self, inv):
        responses = []
        for i in inv:
            if (i.type == 1): # MSG_TX
                tx = self.get(i.hash)
                if tx is not None:
                    responses.append(msg_generic(b"tx", tx))
        return responses
