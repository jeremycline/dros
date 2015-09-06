#!/usr/bin/env sh
#
# Installs build dependencies and builds a cross-compiler
# for the operating system. Fedora 22.
set -e

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

echo "Installing some dev tools..."
sudo dnf groupinstall -y "C Development Tools and Libraries"
sudo dnf install -y xorriso grub2-tools qemu-system-x86 bzip2
# Build dependencies for GCC and binutils
sudo dnf install -y texinfo cloog bison flex gmp-devel \
    mpfr-devel isl-devel libmpc-devel
echo "Done."

mkdir -p cross-build
pushd cross-build

# Build binutils
echo "Downloading binutils source..."
curl -O https://ftp.gnu.org/gnu/binutils/binutils-2.25.tar.bz2
tar xjf binutils-2.25.tar.bz2
mkdir build-binutils-2.25
pushd build-binutils-2.25
echo "Building binutils..."
../binutils-2.25/configure --target=$TARGET --prefix="$PREFIX" \
    --with-sysroot --disable-nls --disable-werror
make
make install
popd
echo "Done."

# Build the GCC cross-compiler
echo "Downloading gcc source..."
curl -O https://ftp.gnu.org/gnu/gcc/gcc-5.1.0/gcc-5.1.0.tar.bz2
tar xjf gcc-5.1.0.tar.bz2
mkdir build-gcc-5.1.0
pushd build-gcc-5.1.0
echo "Building gcc..."
../gcc-5.1.0/configure --target=$TARGET --prefix="$PREFIX" \
    --disable-nls --enable-languages=c --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
popd
echo "Done."

popd
rm -rf cross-build

echo "All done, your cross-compiler is in $PREFIX"
