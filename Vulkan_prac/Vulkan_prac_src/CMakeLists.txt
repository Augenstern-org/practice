add_executable(test1 main.cpp)


target_link_libraries(test1 PRIVATE glfw)
target_link_libraries(test1 PRIVATE glm::glm)
target_link_libraries(test1 PRIVATE Vulkan::Vulkan)