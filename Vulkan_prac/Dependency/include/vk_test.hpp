// vk_test.hpp
#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <vector>
#include <optional>
#include <set>
#include <GLFW/glfw3native.h>

// 定义队列族
struct QueueFamily{
    std::optional<uint32_t> graphicsQueueFamily;

    bool isComplete(){
        return graphicsQueueFamily.has_value();
    }
};

// Vulkan 应用程序类定义
class HelloTriangleApplication {
public:
    void run();  // 运行程序主流程

private:
    // 窗口
    GLFWwindow* window = nullptr;

    // Vulkan 相关对象
    VkInstance instance{};
    VkDebugUtilsMessengerEXT debugMessenger{};
    VkPhysicalDevice device;
    VkDevice logicDevice;
    VkQueue graphicsQueue;

    QueueFamily q_family;

    // 窗口显示
    VkSurfaceKHR surface;

    // 初始化与清理
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    // Vulkan 初始化细节
    void createInstance();
    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();

    // Vulkan 物理设备
    void pickupPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice currentDevice);

    // Vulkan 队列族
    QueueFamily findQueueFamilyIndex(VkPhysicalDevice c_device);

    // Vulkan 逻辑设备
    void createLogicDevice();

    // 调试回调函数
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);



};

// 额外的辅助函数声明（供内部使用）
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);

