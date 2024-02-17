cmake_minimum_required(VERSION 3.25)
project(string)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(string
        main.cpp
        string_array.cpp
        string_array.h)
