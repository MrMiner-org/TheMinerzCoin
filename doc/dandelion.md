# Dandelion++ Transaction Relay

Dandelion++ obfuscates the origin of transactions by relaying them through a short "stem" phase before broadcasting them widely. This helps preserve user privacy against network observers.

## Usage

TheMinerzCoin enables Dandelion++ by default. To disable it, start the node with `-dandelion=0` or set `dandelion=0` in `theminerzcoin.conf`. Use `-dandelion=1` to explicitly turn it back on.
