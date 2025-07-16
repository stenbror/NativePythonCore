FROM ubuntu:latest AS base

RUN apt-get -qq update; \
    apt-get install -qqy --no-install-recommends \
        gnupg2 wget ca-certificates apt-transport-https \
        autoconf automake cmake dpkg-dev file make patch libc6-dev pkg-config clang llvm lldb g++ gdb git wget curl unzip zip tar python3 re2c btop

WORKDIR "/home/ubuntu/"

# Download and install cmake 4.1.0
RUN wget https://github.com/Kitware/CMake/releases/download/v4.1.0-rc2/cmake-4.1.0-rc2-linux-x86_64.sh
RUN chmod 777 cmake-4.1.0-rc2-linux-x86_64.sh
RUN ./cmake-4.1.0-rc2-linux-x86_64.sh --skip-license

# Download and build Ninja
RUN git clone https://github.com/ninja-build/ninja.git
WORKDIR "/home/ubuntu/ninja"
RUN ./configure.py --bootstrap
WORKDIR "/home/ubuntu"

# Download, build and install vcpkg system for C++
RUN git clone https://github.com/microsoft/vcpkg.git
WORKDIR "/home/ubuntu/vcpkg"
RUN ./bootstrap-vcpkg.sh
WORKDIR "/home/ubuntu"

ENV PATH="/home/ubuntu/bin/:/home/ubuntu/ninja/:/home/ubuntu/vcpkg/:$PATH"

RUN mkdir sourcecode
WORKDIR "/home/ubuntu/sourcecode"