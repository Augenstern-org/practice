include_directories(../include)

add_executable(main main.cpp vk.cpp
        vertex_data.cpp
        vertex_data.hpp)

target_link_libraries(main PRIVATE glfw glm::glm Vulkan::Vulkan)