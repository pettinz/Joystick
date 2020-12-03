# Joystick

The aim is to provide a corss-platform library to access Joystick peripheral on macOs, Linux and Windows systems.

## Usage

You can include this library in your CMake projects using FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
    joystick
    GIT_REPOSITORY https://github.com/pettinz/joystick.git
    GIT_TAG "master")

FetchContent_MakeAvailable(joystick)
```

Otherwise you can build from the source code

```bash
$ ~ git clone https://github.com/pettinz/joystick.git
$ ~ cd joystick
$ ~ cmake -Bbuild
$ ~ cmake --build build
```