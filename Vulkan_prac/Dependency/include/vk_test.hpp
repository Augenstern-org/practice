// vk_test.hpp
#pragma once

#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
// #include <GLfW/glfw3native.h>
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

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainImageExtent;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> imageViews;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;



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
    bool checkDeviceExtensionSupported(VkPhysicalDevice c_device);

    // Vulkan 窗口显示
    void createSurface();

    // 交换链
    SwapChainDetails querySwapChainSupport(VkPhysicalDevice c_device);
    // VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VkPhysicalDevice c_device);
    // std::vector<VkSurfaceFormatKHR> getSurfaceFormat(VkPhysicalDevice c_device);
    // std::vector<VkPresentModeKHR> getSurfacePresentMode(VkPhysicalDevice c_device);
    
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

    // Images
    void getSwapChainImages(std::vector<VkImage>& images);
    void createImageView();

    // 着色器
    static std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        // 从文件末尾开始读取的优点是，可以使用读取位置来确定文件的大小并分配缓冲区

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open the file!");
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        // 寻址返回开头正式开始读取
        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        
        return buffer;
    }

    // 渲染过程

    // 在完成管线的创建之前，我们需要告诉 Vulkan 将在渲染时使用的帧缓冲附件。我们需要指定将有多少颜色和深度缓冲区，
    // 每个缓冲区使用多少个采样，以及它们的内容在整个渲染操作中应该如何处理
    // 所有这些信息都封装在一个渲染过程对象中，我们将为此创建一个新的 createRenderPass 函数
    void createRenderPass();

    // 渲染管线
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);



    // 着色器

    static std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        // 从文件末尾开始读取的优点是，可以使用读取位置来确定文件的大小并分配缓冲区

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open the file!");
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        // 寻址返回开头正式开始读取
        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        
        return buffer;
    }

    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);

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

