cmake_minimum_required(VERSION 2.6)
set(CMAKE_GENERATOR "Unix Makefiles")
project(Neuron)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR})

add_executable(main main.cpp neuron.cpp)
add_executable(unitest neuron.cpp unitest.cpp)

target_link_libraries(unitest gtest gtest_main)
add_test(unitest unitest)
