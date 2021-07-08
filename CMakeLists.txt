# cmake_minimum_required(VERSION <specify CMake version here>)
project(myccompiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(myccompiler main.cpp lexer.cpp catch.hpp)