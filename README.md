# Native Python Core

This is the start of a multi plattform ( Windows, Linux and Mac ) minimum Python 3.15 based runtime system written from ground up in C++.

## Build on Linux and Mac.

```
    mkdir -p build
    cd build
    cmake -G Ninja ..
    ctest
```

## Building on Linux ( Ubuntu 24.04 tested )

- Install Compiler with linker, debugger and some tools needed to get started on an empty Linux machine.
  ```
  sudo apt-get install pkg-config autoconf clang lldb git 
  ```
- Download and install cmake
- Download and install ninja build system
- Download, build and install vcpkg package system for C++
  ```
  cd /home/stenbror # Use your own home directory, not mine.
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  .\bootstrap-vcpkg.sh
  ```
- Setup path to cmake, ninja and vcpkg tools.

## Building on Windows machines

- We need to install cmake, vcpkg and Windows C/C++ compiler
  - Download Visual Studio and make sure you install C/C++ development. [Community Edition etc](https://visualstudio.microsoft.com/downloads/)
  - Download and install [CMake](https://cmake.org/download/) for your platform and processor.
  - Clone and execute vcpkg
    ```
        cd c:\Users\stenb
        git clone https://github.com/microsoft/vcpkg.git
        cd vcpkg
        .\bootstrap-vcpkg.bat
    ```
    Replace my username with yours and make sure path for cmake.exe and vcpkg.exe is set based on where you installed them.

- Create and move to a build directory
  ```
  mkdir build
  cd build
  ```
- To configure and download needed dependecies and build them

    ```
    cmake -G Ninja .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/stenb/vcpkg/scripts/buildsystems/vcpkg.cmake
    ```
    Replace username with yours. C:\Users\xxxxxx etc.
- Build project for test
  ```
  ninja unit_tests
  ctest
  ```
