CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

# Loads a specific architecture profile.
FUNCTION(LOAD_PROFILE ARCH)
    # Obtain sources for the arch
    FILE(GLOB ARCH_SRCS "arch/${ARCH}/*.c" "arch/${ARCH}/*.S")
     
    # Load flags associated with arch
    INCLUDE("arch/${ARCH}/flags.cmake")
     
    # Now export our output variables
    SET(ARCH_SRCS ${ARCH_SRCS} PARENT_SCOPE)
    SET(ARCH_LINKER "arch/${ARCH}/linker.ld" PARENT_SCOPE)

    # And specific flags
    SET(ARCH_C_FLAGS ${ARCH_C_FLAGS} PARENT_SCOPE)
    SET(ARCH_ASM_FLAGS ${ARCH_ASM_FLAGS} PARENT_SCOPE)
ENDFUNCTION(LOAD_PROFILE)

LOAD_PROFILE("i386")


INCLUDE_DIRECTORIES("freestanding/include" "include")

# Configure the following C flags:
#
#   -g:         Include debugging information.
#   -std=gnu11: Explicitly set the C standard to GNU 2011.
#   -ffreestanding: Assert compilation targets a freestanding environment; implies -fno-builtin.
#   -Wall:          Enable all warnings about constructions that some users consider questionable.
#   -Wextra:        Enable extra warnings not turned on by '-Wall'.
#   -Werror:        Force all warnings to be compilation errors.
SET(CMAKE_C_FLAGS "${ARCH_C_FLAGS} -g -std=gnu11 -ffreestanding -nostdlib -Wall -Wextra -Werror")

# Configure the linker to include the necessary C runtime objects
EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -print-file-name=crtbegin.o OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE CRTBEGIN_PATH)
MESSAGE(STATUS "Using the following crtbegin.o: " ${CRTBEGIN_PATH})
EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -print-file-name=crtend.o OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE CRTEND_PATH)
MESSAGE(STATUS "Using the following crtend.o: " ${CRTEND_PATH})
SET(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_COMPILER} ${CMAKE_C_LINK_FLAGS} ${LINK_FLAGS} ${CRTBEGIN_PATH} <OBJECTS> ${CRTEND_PATH} -o <TARGET> -nostdlib -T ${ARCH_LINKER}")

# Collect all freestanding libc functions. This is necessary since GCC may generate calls
# to several functions defined within, so even if some of these functions are not used
# directly in the kernel code, they are still required. See the README in freestanding for
# more information.
FILE(GLOB_RECURSE FREESTANDING_SRCS "freestanding/*.c")
FILE(GLOB_RECURSE GENERIC_SRCS "kernel/*.c")

# Define the kernel image and its build requirements.
ADD_EXECUTABLE(kernel.elf ${ARCH_SRCS} ${GENERIC_SRCS} ${FREESTANDING_SRCS})

