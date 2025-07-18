FROM debian:latest

RUN apt-get update && apt-get install -y locales && rm -rf /var/lib/apt/lists/* \
	&& localedef -i nb_NO -c -f UTF-8 -A /usr/share/locale/locale.alias nb_NO.UTF-8

ENV LANG nb_NO.utf8

RUN apt-get update && apt-get install -y lsb-release wget software-properties-common curl gnupg \
        autoconf automake dpkg-dev file make patch libc6-dev pkg-config git unzip zip tar python3 re2c btop

RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 21

RUN ln -s /usr/bin/clang++-21 /usr/bin/clang++
RUN ln -s /usr/bin/clang-21 /usr/bin/clang

WORKDIR "/home/"
ENV CXX="/usr/bin/clang++"
ENV CC="/usr/bin/clang"

# Download and install cmake 4.1.0
RUN wget https://github.com/Kitware/CMake/releases/download/v4.1.0-rc2/cmake-4.1.0-rc2-linux-x86_64.sh
RUN chmod 777 cmake-4.1.0-rc2-linux-x86_64.sh
RUN ./cmake-4.1.0-rc2-linux-x86_64.sh --skip-license

# Download and build Ninja
RUN git clone https://github.com/ninja-build/ninja.git
WORKDIR "/home/ninja"
RUN ./configure.py --bootstrap
WORKDIR "/home/"

# Download, build and install vcpkg system for C++
RUN git clone https://github.com/microsoft/vcpkg.git
WORKDIR "/home/vcpkg"
RUN ./bootstrap-vcpkg.sh
WORKDIR "/home/"

ENV PATH="/home/bin/:/home/ninja/:/home/vcpkg/:$PATH"

RUN mkdir sourcecode
WORKDIR "/home/sourcecode"
