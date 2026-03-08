cmake_minimum_required(VERSION 3.20)
project(shader_s_principle)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


add_executable(shader_s_principle src/main.cpp
        include/vertex.hpp
        src/Screen.cpp
        include/Screen.hpp
        src/Texture.cpp
        include/Texture.hpp
        src/VertShader.cpp
        include/VertShader.hpp
        src/Buffers.cpp
        include/Buffers.hpp)

target_link_libraries(shader_s_principle PRIVATE
        glfw
        glm::glm
        opengl32
)
