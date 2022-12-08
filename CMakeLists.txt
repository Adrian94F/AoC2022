cmake_minimum_required(VERSION 3.22)
project(AoC2022)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-g -O0 --coverage")

add_subdirectory(${CMAKE_BINARY_DIR}/../lib/googletest
        EXCLUDE_FROM_ALL)

file(COPY data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SRC_LIST
        src/main.cpp
        src/day1.cpp
        src/day2.cpp
        src/day3.cpp
        src/day4.cpp
        src/day5.cpp
        src/day6.cpp
        src/day7.cpp
        src/day8.cpp
        src/day9.cpp)

include_directories(src)
add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)

set(TEST_SRC_LIST
        test/test_main.cpp
        test/day2.cpp)

link_libraries(gtest)
link_libraries(gmock)
add_executable(${PROJECT_NAME}-ut ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)