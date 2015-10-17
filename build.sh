#!/usr/bin/env sh
export PATH=/usr/local/bin/i686-dros-toolchain/bin/:$PATH
cmake -DCMAKE_TOOLCHAIN_FILE=~/devel/dros/arch/i386/toolchain-gcc-i386.cmake .
make
