cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_TOOLCHAIN_FILE "C:/VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_TOOLCHAIN_FILE "/home/evil/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(VULKAN_PRAC)

include_directories(Dependency/include)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(Vulkan_prac_src)