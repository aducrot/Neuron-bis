cmake_minimum_required(VERSION 2.6)
set(CMAKE_GENERATOR "Unix Makefiles")
project(Neuron)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")
add_executable(main main.cpp neuron.cpp)
