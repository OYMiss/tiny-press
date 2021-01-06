cmake_minimum_required(VERSION 3.17)
project(tiny_press)

set(CMAKE_CXX_STANDARD 17)

add_executable(tiny_press main.cpp html.h html.cpp lib/prase.hpp lib/convert.hpp)