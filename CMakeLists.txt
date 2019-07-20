cmake_minimum_required(VERSION 3.0)

project(zlisp LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

find_package(Catch2 REQUIRED)

# Tests
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ext/Catch2/single_include/")
add_executable(zlisp_parsing_test test/parsing_test.cpp)
target_link_libraries(zlisp_parsing_test Catch2::Catch2)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(zlisp_parsing_test)

# Main program
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(zlisp src/main.cpp)

