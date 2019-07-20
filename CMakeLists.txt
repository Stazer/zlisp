cmake_minimum_required(VERSION 2.6)

project(zlisp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(zlisp main.cpp)

