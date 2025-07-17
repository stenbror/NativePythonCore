FROM ubuntu:latest AS base

RUN apt-get -qq update; \
    apt-get install -qqy --no-install-recommends \
        gnupg2 wget ca-certificates apt-transport-https \
        autoconf automake cmake dpkg-dev file make patch libc6-dev pkg-config g++ gdb git wget curl unzip zip tar python3 re2c btop

# Checkout latest clang compiler suite for Ubuntu 24.04 
RUN wget -qO /etc/apt/trusted.gpg.d/apt.llvm.org.asc https://apt.llvm.org/llvm-snapshot.gpg.key
RUN echo "deb http://apt.llvm.org/$(lsb_release -sc)/ llvm-toolchain-$(lsb_release -sc) main" | tee /etc/apt/sources.list.d/apt.llvm.org.list

RUN apt-get -qq update; \
    apt-get install -qqy --no-install-recommends \
        clang-19 llvm-19 lldb-19

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

ENV PATH="/usr/lib/llvm-19/bin:/home/ubuntu/bin/:/home/ubuntu/ninja/:/home/ubuntu/vcpkg/:$PATH"

RUN mkdir sourcecode
WORKDIR "/home/ubuntu/sourcecode"