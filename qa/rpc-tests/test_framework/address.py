#!/usr/bin/env python3
# Copyright (c) 2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
# address.py
#
# This file encodes and decodes BASE58 P2PKH and P2SH addresses
#

from .script import CScript, hash160, hash256
from .util import bytes_to_hex_str, hex_str_to_bytes

chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"


def byte_to_base58(b, version):
    result = ""
    str = bytes_to_hex_str(b)
    str = bytes_to_hex_str(chr(version).encode("latin-1")) + str
    checksum = bytes_to_hex_str(hash256(hex_str_to_bytes(str)))
    str += checksum[:8]
    value = int("0x" + str, 0)
    while value > 0:
        result = chars[value % 58] + result
        value //= 58
    while str[:2] == "00":
        result = chars[0] + result
        str = str[2:]
    return result


def base58_decode(s):
    """Decode a base58 encoded string ``s`` back into bytes.

    The return value is a tuple of ``(payload, version)`` with the checksum
    verified.  ``payload`` is the original byte string passed to
    :func:`byte_to_base58` and ``version`` is the version byte.
    """

    value = 0
    for c in s:
        value *= 58
        idx = chars.find(c)
        assert idx != -1
        value += idx

    hex_str = format(value, "x")
    if len(hex_str) % 2:
        hex_str = "0" + hex_str

    for c in s:
        if c == chars[0]:
            hex_str = "00" + hex_str
        else:
            break

    data = hex_str_to_bytes(hex_str)
    payload, checksum = data[:-4], data[-4:]
    assert checksum == hash256(payload)[:4]
    version = payload[0]
    return payload[1:], version


def keyhash_to_p2pkh(hash, main=False):
    assert len(hash) == 20
    version = 0 if main else 111
    return byte_to_base58(hash, version)


def scripthash_to_p2sh(hash, main=False):
    assert len(hash) == 20
    version = 5 if main else 196
    return byte_to_base58(hash, version)


def key_to_p2pkh(key, main=False):
    key = check_key(key)
    return keyhash_to_p2pkh(hash160(key), main)


def script_to_p2sh(script, main=False):
    script = check_script(script)
    return scripthash_to_p2sh(hash160(script), main)


def check_key(key):
    if type(key) is str:
        key = hex_str_to_bytes(key)  # Assuming this is hex string
    if type(key) is bytes and (len(key) == 33 or len(key) == 65):
        return key
    assert False


def check_script(script):
    if type(script) is str:
        script = hex_str_to_bytes(script)  # Assuming this is hex string
    if type(script) is bytes or type(script) is CScript:
        return script
    assert False
