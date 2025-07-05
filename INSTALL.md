Building TheMinerzCoin
================

See doc/build-*.md for instructions on building the various
elements of the TheMinerzCoin reference implementation of TheMinerzCoin.

Dependencies
------------
Before building from source make sure the basic build tools and Qt5 development
packages are available. On recent Debian or Ubuntu systems run:

```
sudo apt-get update
sudo apt-get install build-essential cmake libssl-dev libevent-dev pkg-config \
    qtbase5-dev qt5-qmake qttools5-dev qttools5-dev-tools libqt5widgets5 \
    libqt5network5 libqt5gui5 libqt5core5a libqt5dbus5 libprotobuf-dev \
    protobuf-compiler libdb++-dev libdb5.3++-dev libgrpc++-dev \
    protobuf-compiler-grpc
```

These packages provide OpenSSL, libevent, the Qt5 toolkit and Protocol Buffers
so that `./generate_build.sh` can configure the build system without errors.

Build Steps
-----------
Generate the build system using CMake and then build:

```
./generate_build.sh
./build.sh
```
