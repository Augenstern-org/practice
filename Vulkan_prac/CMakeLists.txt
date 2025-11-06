cmake_minimum_required(VERSION 3.10)
project(VULKAN_PRAC VERSION 1.0)

# 设置cpp版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加 Vulkan 库
find_package(Vulkan REQUIRED)

# 添加源文件
add_executable(vk_prac src/test1.cpp)

# 链接库
target_link_libraries(vk_prac Vulkan::Vulkan)

