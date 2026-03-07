cmake_minimum_required(VERSION 4.0)
project(shader_s_principle)

set(CMAKE_CXX_STANDARD 20)

add_executable(shader_s_principle src/main.cpp
        src/vertex.cpp
        include/vertex.hpp
        src/Screen.cpp
        include/Screen.hpp
        src/Image.cpp
        include/Image.hpp
        src/VertShader.cpp
        include/VertShader.hpp)
