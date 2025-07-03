Building TheMinerzCoin
================

See doc/build-*.md for instructions on building the various
elements of the TheMinerzCoin reference implementation of TheMinerzCoin.

Dependencies
------------
Before building from source make sure the basic build tools are available. On
most Linux systems these can be installed from the package manager:

```
sudo apt-get install build-essential autoconf automake libtool pkg-config \
    libssl-dev libevent-dev
```

Build Steps
-----------
Run the autotools scripts to generate the build system before invoking `make`:

```
./autogen.sh && ./configure
make
```
