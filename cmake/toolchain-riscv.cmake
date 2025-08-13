# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=path/to/toolchain-riscv.cmake ..

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

# Specify the cross compiler
set(CMAKE_C_COMPILER "riscv64-unknown-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "riscv64-unknown-linux-gnu-g++")

set(CMAKE_C_FLAGS "-march=rv64gcv -mabi=lp64d" CACHE INTERNAL "C compiler flags")
set(CMAKE_CXX_FLAGS "-march=rv64gcv -mabi=lp64d -static-libstdc++" CACHE INTERNAL "C++ compiler flags")

include_directories(/usr/lib/gcc-cross/riscv64-linux-gnu/14/include)
