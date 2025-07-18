Mac OS X Build Instructions and Notes
====================================
The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

Preparation
-----------
Install the OS X command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](http://brew.sh).

Dependencies
----------------------

    brew install automake berkeley-db4 libtool boost --c++11 miniupnpc openssl pkg-config homebrew/versions/protobuf260 --c++11 qt5 libevent

In case you want to build the disk image with `make deploy` (.dmg / optional), you need RSVG

    brew install librsvg

NOTE: Building with Qt4 is still supported, however, could result in a broken UI. Building with Qt5 is recommended.

Build TheMinerzCoin
------------------------

1. Clone the theminerzcoin source code and cd into `theminerzcoin`

        git clone https://github.com/MrMiner-org/TheMinerzCoin/
        cd theminerzcoin

2.  Build theminerzcoin:

    Configure and build the headless theminerzcoin binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `-DWITH_GUI=OFF` to CMake.

        ./generate_build.sh
        ./build.sh

3.  It is recommended to build and run the unit tests:

        cmake --build build --target check

4.  You can also create a .dmg that contains the .app bundle (optional):

        cmake --build build --target deploy

Running
-------

TheMinerzCoin is now available at `./src/theminerzcoind`

Before running, it's recommended you create an RPC configuration file.

    echo -e "rpcuser=theminerzcoinrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/TheMinerzCoin/theminerzcoin.conf"

    chmod 600 "/Users/${USER}/Library/Application Support/TheMinerzCoin/theminerzcoin.conf"

The first time you run theminerzcoind, it will start downloading the blockchain. This process could take several hours.

You can monitor the download process by looking at the debug.log file:

    tail -f $HOME/Library/Application\ Support/TheMinerzCoin/debug.log

Other commands:
-------

    ./src/theminerzcoind -daemon # Starts the theminerzcoin daemon.
    ./src/theminerzcoin-cli --help # Outputs a list of command-line options.
    ./src/theminerzcoin-cli help # Outputs a list of RPC commands when the daemon is running.

Using Qt Creator as IDE
------------------------
You can use Qt Creator as an IDE, for theminerzcoin development.
Download and install the community edition of [Qt Creator](https://www.qt.io/download/).
Uncheck everything except Qt Creator during the installation process.

1. Make sure you installed everything through Homebrew mentioned above
2. Generate build files with `./generate_build.sh -DCMAKE_BUILD_TYPE=Debug`
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "theminerzcoin-qt" as project name, enter src/qt as location
5. Leave the file selection as it is
6. Confirm the "summary page"
7. In the "Projects" tab select "Manage Kits..."
8. Select the default "Desktop" kit and select "Clang (x86 64bit in /usr/bin)" as compiler
9. Select LLDB as debugger (you might need to set the path to your installation)
10. Start debugging with Qt Creator

Notes
-----

* Tested on OS X 10.8 through 10.12 on 64-bit Intel processors only.

* Building with downloaded Qt binaries is not officially supported. See the notes in [#7714](https://github.com/bitcoin/bitcoin/issues/7714)
