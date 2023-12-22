cmake_minimum_required(VERSION 3.12)
project(mini_gdb VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 11)


set(SAC_LIB_SRCS
    include/helper.hpp
    src/helper.cpp
)

include_directories(
    /usr/local/include
    /usr/include
    include/
)

link_directories(
    /usr/local/lib/
    /usr/lib64/
)



add_executable(mini_gdb main.cpp ${SAC_LIB_SRCS})

target_link_libraries(mini_gdb -lpthread)
