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


// #include <filesystem>       // Debug

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
    std::vector<VkImageView> swapChainImageViews;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    uint32_t currentFrame = 0;
    bool framebufferResized = false;


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
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    // 交换链
    SwapChainDetails querySwapChainSupport(VkPhysicalDevice c_device);
    // VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VkPhysicalDevice c_device);
    // std::vector<VkSurfaceFormatKHR> getSurfaceFormat(VkPhysicalDevice c_device);
    // std::vector<VkPresentModeKHR> getSurfacePresentMode(VkPhysicalDevice c_device);
    
    VkSurfaceFormatKHR chooseSurfaceFormat(const SwapChainDetails& details);
    VkPresentModeKHR chooseSurfacePresentMode(const SwapChainDetails& details);
    VkExtent2D chooseExtent2D(const SwapChainDetails& details);
    void createSwapChain();
    void recreateSwapChain();
    void cleanupSwapChain();

    // 调试回调函数
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

    // Images
    void getSwapChainImages(std::vector<VkImage>& images);
    void createImageView();

    // 渲染过程

    // 在完成管线的创建之前，我们需要告诉 Vulkan 将在渲染时使用的帧缓冲附件。我们需要指定将有多少颜色和深度缓冲区，
    // 每个缓冲区使用多少个采样，以及它们的内容在整个渲染操作中应该如何处理
    // 所有这些信息都封装在一个渲染过程对象中，我们将为此创建一个新的 createRenderPass 函数
    void createRenderPass();

    // 渲染管线
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);

    // 着色器
    static std::vector<char> readFile(const std::string& filename);
    void createVertexBuffer();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, 
                      VkMemoryPropertyFlags properties, VkBuffer& buffer, 
                      VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    // 帧缓冲
    void createFrameBuffers();

    // 命令池
    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    // 绘图
    void drawFrame();

    // 创建同步对象
    void createSyncObjects();

    // GPU
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


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

