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


- To configure and download needed dependecies and build them

    ```
        cmake -G Ninja .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/stenb/vcpkg/scripts/buildsystems/vcpkg.cmake
    ```
