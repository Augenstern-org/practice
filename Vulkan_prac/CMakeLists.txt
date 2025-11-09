cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # set(CMAKE_TOOLCHAIN_FILE "C:/VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_TOOLCHAIN_FILE "/home/evil/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(VULKAN_PRAC)

# include_directories(../Dependency/include)
set(glfw3_ROOT C:/glfw-3.4.bin.WIN64)
include_directories(${glfw3_ROOT}/include)

set(glm_DIR C:/glm)
include_directories(${glm_DIR}/glm)

link_directories(${glfw3_ROOT}/lib-vc2022)

find_package(Vulkan REQUIRED)

add_subdirectory(Vulkan_prac_src)