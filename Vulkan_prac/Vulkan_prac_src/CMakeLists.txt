include_directories(../Dependency/include)

add_executable(test1 test1.cpp vk_test.cpp)

target_link_libraries(test1 PRIVATE glfw Vulkan::Vulkan glm::glm)