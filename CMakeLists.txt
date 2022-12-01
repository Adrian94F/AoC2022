cmake_minimum_required(VERSION 3.22)
project(AoC2022)

set(CMAKE_CXX_STANDARD 14)

file(COPY data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(AoC2022 src/day1.cpp)
