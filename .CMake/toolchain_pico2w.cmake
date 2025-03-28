# SPDX-License-Identifier: MIT

# How to use:
# sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
# cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=../.CMake/toolchain_pico2w.cmake -DOQS_USE_OPENSSL=OFF -DOQS_PERMIT_UNSUPPORTED_ARCHITECTURE=ON -DOQS_EMBEDDED_BUILD=ON -DOQS_BUILD_ONLY_LIB=ON ..
# TODO: SPHINCS+ complains about incompatible pointer types, which may have something to do with the
# fact that Pico is a 32-bit system. I am not sure how to troubleshoot this. For now I will just avoid
# using SPHINCS.

set(CMAKE_SYSTEM_NAME PICO)
set(CMAKE_SYSTEM_PROCESSOR arm32v7)
set(CMAKE_CROSSCOMPILING ON)

set(CMAKE_C_COMPILER arm-none-eabi-gcc --specs=nosys.specs)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Unconditionally set for this platform
add_definitions( -DOQS_USE_RASPBERRY_PI )

