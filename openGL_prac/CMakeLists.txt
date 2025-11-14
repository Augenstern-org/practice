cmake_minimum_required(VERSION 3.10)

project(MyProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OPENGL_PRAC)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)



set(GLFW3_DIR "/usr/local/lib/cmake/glfw3")
# find_package(GLFW3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(./include/)


# add_executable(test ./test/test.cpp src/glad.c)
add_executable(test src/main.cpp src/openGL_test.cpp src/glad.c)

target_link_options(test PUBLIC "SHELL:-Wl,-no-as-needed -lglfw" )
target_link_libraries(test ${OPENGL_gl_LIBRARY} glfw ${GLUT_LIBRARIES})