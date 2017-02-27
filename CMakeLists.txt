# main CMakeLists file for building example demos in "genetic_algo"

cmake_minimum_required (VERSION 2.8)

# compiler requirement is C++11
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

project(genetic_algo)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(PROJECT_EXAMPLES_DIR ${PROJECT_SOURCE_DIR}/src/examples)
add_subdirectory(${PROJECT_EXAMPLES_DIR}/n_queen)
add_subdirectory(${PROJECT_EXAMPLES_DIR}/math_functions)