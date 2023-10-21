# Tests


## Running tests

This project leverages [AUnit](https://github.com/bxparks/AUnit) to facilitate building automated tests, and [EpoxyDuino](https://github.com/bxparks/EpoxyDuino) to mock an Arduino on a PC and run continuous integration.

I ran tests using Windows Subsystem for Linux (WSL). Follow these steps to get started - you may be able to skip several steps on a standard Linux distro or macOS.

1. Install the AUnit library within the Arduino IDE.
1. [Setup and configure WSL](https://learn.microsoft.com/en-us/windows/wsl/install).
    1. At the time of this running, the provided Ubuntu distro requires an `apt update` before proceeding.
    1. EpoxyDuino requires a C++ compiler and make. Add them to your install with `apt install g++` and `apt install make`.
1. Clone the [EpoxyDuino](https://github.com/bxparks/EpoxyDuino) repo and place it within the `user/Documents/Arduino/libraries` folder (this is not a required location, but this project is setup assuming EpoxyDuino is located here).
1. Add a `.env` file to the root of this project with the following format:

```bash
arduino_ide_dir=LOCATION_OF_ARDUINO_IDE
```

You are now ready to build and compile and run the tests. Follow these instructions to run all tests from the root of this project. I prefer to use the WSL terminal within VS Code for this purpose.

```bash
$ make -C tests clean

$ make -C tests tests
$ make -C tests runtests | grep failed
```

Alternatively, you can browse to the subfolder containing a specific subset of tests and run those directly.

```bash
$ make clean

$ make
$ make run
```