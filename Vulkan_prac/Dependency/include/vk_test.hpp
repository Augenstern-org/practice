// vk_test.hpp
#pragma once

#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vector>
#include <optional>
#include <set>
#include <string>
#include <cstdint>              // Necessary for uint32_t
#include <limits>               // Necessary for std::numeric_limits
#include <algorithm>            // Necessary for std::clamp

// 定义队列族
struct QueueFamily{
    std::optional<uint32_t> graphicsQueueFamily;
    std::optional<uint32_t> presentQueueFamily;

    bool isComplete(){
        return graphicsQueueFamily.has_value() &&
                presentQueueFamily.has_value();
    }
};

// 交换链细节
struct SwapChainDetails{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> modes;
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
    VkQueue presentQueue;

    QueueFamily q_family;

    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;

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
    QueueFamily findQueueFamilyIndex(VkPhysicalDevice& c_device);

    // Vulkan 逻辑设备
    void createLogicDevice();
    bool checkDeviceExtensionSupported(VkPhysicalDevice c_device);

    // Vulkan 窗口显示
    void createSurface();

    // 交换链
    SwapChainDetails querySwapChainSupport(VkPhysicalDevice c_device);
    VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VkPhysicalDevice c_device);
    std::vector<VkSurfaceFormatKHR> getSurfaceFormat(VkPhysicalDevice c_device);
    std::vector<VkPresentModeKHR> getSurfacePresentMode(VkPhysicalDevice c_device);
    VkSurfaceFormatKHR chooseSurfaceFormat(const SwapChainDetails& details);
    VkPresentModeKHR chooseSurfacePresentMode(const SwapChainDetails& details);
    VkExtent2D chooseExtent2D(const SwapChainDetails& details);
    void createSwapChain();
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

