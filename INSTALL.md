Building TheMinerzCoin
================

See doc/build-*.md for instructions on building the various
elements of the TheMinerzCoin reference implementation of TheMinerzCoin.

Dependencies
------------
Before building from source make sure the basic build tools are available. On
most Linux systems these can be installed from the package manager:

```
sudo apt-get install build-essential cmake libssl-dev libevent-dev pkg-config
```

Build Steps
-----------
Generate the build system using CMake and then build:

```
./generate_build.sh
./build.sh
```
