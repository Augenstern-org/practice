// 编码约定

// 所有的 Vulkan 函数、枚举和结构体都在 vulkan.h 头文件中定义，
// 该文件包含在 LunarG 开发的 Vulkan SDK 中。
// 我们将在下一章介绍安装此 SDK 的方法。

// 函数具有小写的 vk 前缀，类型（如枚举和结构体）具有 Vk 前缀，
// 枚举值具有 VK_ 前缀。API 大量使用结构体来为函数提供参数。
// 例如，对象创建通常遵循以下模式：

// VkXXXCreateInfo createInfo{};
// createInfo.sType = VK_STRUCTURE_TYPE_XXX_CREATE_INFO;
// createInfo.pNext = nullptr;
// createInfo.foo = ...;
// createInfo.bar = ...;

// VkXXX object;
// if (vkCreateXXX(&createInfo, nullptr, &object) != VK_SUCCESS) {
//     std::cerr << "failed to create object" << std::endl;
//     return false;
// }

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}