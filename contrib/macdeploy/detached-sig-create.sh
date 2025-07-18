#!/bin/sh
set -euo pipefail
# Create a detached signature for a macOS application bundle.
# Copyright (c) 2014-2021 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C

ROOTDIR=dist
BUNDLE="${ROOTDIR}/TheMinerzCoin-Qt.app"
BINARY="${BUNDLE}/Contents/MacOS/TheMinerzCoin-Qt"
SIGNAPPLE=signapple
TEMPDIR=sign.temp
ARCH=$(${SIGNAPPLE} info ${BINARY} | head -n 1 | cut -d " " -f 1)
OUT="signature-osx-${ARCH}.tar.gz"
OUTROOT=osx/dist

if [ -z "$1" ]; then
  echo "usage: $0 <signapple args>"
  echo "example: $0 <path to key>"
  exit 1
fi

rm -rf ${TEMPDIR}
mkdir -p ${TEMPDIR}

${SIGNAPPLE} sign -f --detach "${TEMPDIR}/${OUTROOT}"  "$@" "${BUNDLE}"

tar -C "${TEMPDIR}" -czf "${OUT}" .
rm -rf "${TEMPDIR}"
echo "Created ${OUT}"
