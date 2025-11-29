//
// Created by Neuroil on 2025/11/26.
//
#ifndef BLACKHOLE_PRAC_VK_HPP
#define BLACKHOLE_PRAC_VK_HPP

#include <vulkan/vulkan.h>
#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <vector>
#include <optional>
#include <set>
#include <string>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <fstream>

struct QueueFamily{
    std::optional<uint32_t> graphicQueueFamily;
    std::optional<uint32_t> presentQueueFamily;

    bool isComplete(){
        return graphicQueueFamily.has_value() &&
                presentQueueFamily.has_value();
    }
};

struct SwapChainDetails{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> modes;
};

struct windowInfo {
    uint32_t width = 800;
    uint32_t height = 600;
    const char* title = "Black Hole Ray Tracing Simulation";
};

class vk {
public:
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

private:
    GLFWwindow* window = nullptr;
    windowInfo windowInfo;

private:
    VkInstance instance{};
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    QueueFamily q_family;
    VkDevice device;
    VkQueue graphicQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;
    VkExtent2D swapChainExtent;

private:
    // Debug 相关
    bool framebufferResized = false;
    VkDebugUtilsMessengerEXT debugMessenger;

private:
    // 辅助函数
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);
    SwapChainDetails querySwapChainSupport(VkPhysicalDevice c_device);
    bool checkDeviceExtensionSupported(VkPhysicalDevice c_device);
    QueueFamily findQueueFamily(VkPhysicalDevice c_device);
    bool isPhysicalDeviceSuitable(VkPhysicalDevice c_device);
private:
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickupPhysicalDevice();
    void createLogicDevice();
    void createSwapChain();

private:
    // 销毁函数
    void DestroyDebugUtilsMessengerEXT(VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);
};

#endif //BLACKHOLE_PRAC_VK_HPP