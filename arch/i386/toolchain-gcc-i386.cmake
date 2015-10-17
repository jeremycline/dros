INCLUDE(CMakeForceCompiler)

# This is the name of the operating system on which CMake is targeting.
SET(CMAKE_SYSTEM_NAME DrOS)

# Point CMake at the cross-compiler
CMAKE_FORCE_C_COMPILER(i686-elf-gcc GNU)

SET(CMAKE_FIND_ROOT_PATH  "/usr/local/bin/i686-dros-toolchain/")

# List of root paths to search on the filesystem.
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Only the roots in CMAKE_FIND_ROOT_PATH will be searched for libraries.
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# Only the roots in CMAKE_FIND_ROOT_PATH will be searched for includes.
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# Only the roots in CMAKE_FIND_ROOT_PATH will be searched for packages.
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Let CMake know we're cross-compiling.
set(CMAKE_CROSSCOMPILING TRUE)
