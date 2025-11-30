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
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

extern const std::vector<Vertex> vertices;
extern const std::vector<uint16_t> indices;

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

// ----------------------------------------------------------------------------------------------

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
    const char* title = "Black Hole Ray Tracing Simulation COMPUTE_SHADER";
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
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainImageExtent;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

private:
    uint32_t currentFrame = 0;

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
    VkSurfaceFormatKHR chooseSurfaceFormat(const SwapChainDetails& details);
    VkPresentModeKHR choosePresentMode(const SwapChainDetails& details);
    VkExtent2D chooseExtent2D(const SwapChainDetails& details);
    static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                  VkMemoryPropertyFlags properties, VkBuffer& buffer,
                  VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
private:
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickupPhysicalDevice();
    void createLogicDevice();
    void createSwapChain();
    void createImageView();
    void createRenderPass();
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    void createFrameBuffers();
    void createCommandPool();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSyncObjects();

private:
    // 销毁函数
    void DestroyDebugUtilsMessengerEXT(VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);
    void cleanupSwapChain();
};

#endif //BLACKHOLE_PRAC_VK_HPP