cmake_minimum_required(VERSION 3.17)
project(tiny_press)

set(CMAKE_CXX_STANDARD 17)

add_executable(tiny_press main.cpp html.h html.cpp marktool/parse.hpp marktool/convert.cpp marktool/convert.h)

install(TARGETS tiny_press)
