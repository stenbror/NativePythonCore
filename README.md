# Native Python Core

This is the start of a multi plattform ( Windows, Linux and Mac ) minimum Python 3.15 based runtime system written from ground up in C++.

## Build on Mac ( Apple silicon ).

```
    mkdir -p build
    cd build
    cmake -G Ninja ..
    ctest
```

## Building on Linux ( Ubuntu 24.04 tested )

- Install Compiler with linker, debugger and some tools needed to get started on an empty Linux machine.
  ```
  sudo apt-get install pkg-config autoconf clang lldb git curl zip unzip tar wget
  ```
- Download and install cmake
  ```
  wget https://github.com/Kitware/CMake/releases/download/v4.1.0-rc1/cmake-4.1.0-rc1-linux-x86_64.sh
  chmod 777 cmake-4.1.0-rc1-linux-x86_64.sh
  ```
- Download and install ninja build system
  ```
  git clone https://github.com/ninja-build/ninja.git && cd ninja
  git checkout release
  cat README.md
  ```
- Download, build and install vcpkg package system for C++
  ```
  cd /home/stenbror # Use your own home directory, not mine.
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  .\bootstrap-vcpkg.sh
  ```
- Setup path to cmake, ninja and vcpkg tools.

  Make sure you use your own home directory in path and not mine. :-) You modify the *.bashrc* file if you use bash in terminal.
  ```
  export PATH="/home/stenbror/cmake-4.1.0-rc1-linux-x86_64/bin/:/home/stenbror/ninja/:/home/stenbror/vcpkg/:$PATH"
  ```
- Build project
  ```
  mkdir build
  cd build
  cmake -G Ninja .. -DCMAKE_TOOLCHAIN_FILE=/home/stenbror/vcpkg/scripts/buildsystems/vcpkg.cmake
  ```
- Execute all unit tests.
  ```
  ninja unit_tests
  ctest
  ```
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
