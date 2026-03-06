cmake_minimum_required(VERSION 4.0)
project(smart_ptr)

set(CMAKE_CXX_STANDARD 23)

add_executable(smart_ptr main.cpp
        sm_ptr.cpp
        sm_ptr.hpp)
