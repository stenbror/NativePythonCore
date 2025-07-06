# Native Python Core

This is the start of a multi plattform ( Windows, Linux and Mac ) minimum Python 3.15 based runtime system written from ground up in C++.

## Build on Linux and Mac.

```
    mkdir -p build
    cd build
    cmake -G Ninja ..
    ctest
```

## Building on Windows machines

- We need to install cmake, vcpkg and Windows C/C++ compiler
  - Download Visual Studio and make sure you install C/C++ development. [Community Edition etc](https://visualstudio.microsoft.com/downloads/)
  - Download and install [CMake](https://cmake.org/download/) for your platform and processor.


- To configure and download needed dependecies and build them

    ```
    cmake -G Ninja .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/stenb/vcpkg/scripts/buildsystems/vcpkg.cmake
    ```
    Replace username with yours. C:\Users\xxxxxx etc.
