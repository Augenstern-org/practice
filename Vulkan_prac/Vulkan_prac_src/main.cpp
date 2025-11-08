// 告诉 GLFW 我们要使用 Vulkan，而不是默认的 OpenGL
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

// 定义窗口的宽度和高度
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// 定义验证层的名称，验证层用于调试 Vulkan 程序，帮助开发者检查潜在错误
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation" // Vulkan 默认的验证层
};

// 在调试模式下启用验证层，发布模式下禁用
#ifdef NDEBUG
const bool enableValidationLayers = false; // 发布模式，关闭验证层
#else
const bool enableValidationLayers = true;  // 调试模式，启用验证层
#endif

// 创建调试回调函数的扩展
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT; // 如果没有找到扩展函数，返回错误
    }
}

// 销毁调试回调函数的扩展
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

// 主应用程序类
class HelloTriangleApplication {
public:
    // 程序主函数
    void run() {
        initWindow();   // 初始化 GLFW 窗口
        initVulkan();   // 初始化 Vulkan
        mainLoop();     // 进入主循环，等待并处理事件
        cleanup();      // 程序结束时清理资源
    }

private:
    GLFWwindow* window;  // 窗口指针

    VkInstance instance;                // Vulkan 实例
    VkDebugUtilsMessengerEXT debugMessenger; // 调试回调

    VkPhysicalDevice physicalDevice; // Vulkan 物理设备句柄

    // 初始化 GLFW 窗口
    void initWindow() {
        glfwInit();  // 初始化 GLFW 库

        // 禁用默认的 OpenGL 上下文，因为我们使用的是 Vulkan
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);  // 禁用窗口大小调整

        // 创建一个 800x600 的窗口
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void pickPhisicalDevice(){
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr); // 列出可用的 Vulkan 设备
        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount); // 分配一个数组来保存所有 VkPhysicalDevice 句柄
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        bool isDeviceSuitable(VkPhysicalDevice device) {   // 判断该设备是否可用
            return true;
        }
        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
}
    }

    // 初始化 Vulkan，首先创建实例，并设置调试回调
    void initVulkan() {
        createInstance();       // 创建 Vulkan 实例
        setupDebugMessenger();  // 设置调试回调
        pickPhisicalDevice();   // 选择 Vulkan 设备
    }

    // 主循环，处理窗口事件
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();  // 检查并处理事件（如按键、鼠标等）
        }
    }

    // 清理所有资源
    void cleanup() {
        // 如果启用了验证层，则销毁调试回调
        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

        // 销毁 Vulkan 实例
        vkDestroyInstance(instance, nullptr);

        // 销毁 GLFW 窗口
        glfwDestroyWindow(window);

        // 终止 GLFW 库
        glfwTerminate();
    }

    // 创建 Vulkan 实例
    void createInstance() {
        // 检查验证层是否支持
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        // 填充应用程序信息
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; // 类型标识
        appInfo.pApplicationName = "Hello Triangle";         // 应用程序名称
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // 应用程序版本
        appInfo.pEngineName = "No Engine";                   // 引擎名称
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);    // 引擎版本
        appInfo.apiVersion = VK_API_VERSION_1_0;             // Vulkan API 版本

        // 填充 Vulkan 实例创建信息
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; // 类型标识
        createInfo.pApplicationInfo = &appInfo; // 应用程序信息

        // 获取 GLFW 所需的扩展
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size()); // 启用扩展数量
        createInfo.ppEnabledExtensionNames = extensions.data();  // 扩展名称

        // 设置调试回调信息
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size()); // 启用验证层数量
            createInfo.ppEnabledLayerNames = validationLayers.data(); // 验证层名称

            populateDebugMessengerCreateInfo(debugCreateInfo);  // 填充调试信息
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo; // 链接调试回调信息
        } else {
            createInfo.enabledLayerCount = 0; // 不启用验证层
            createInfo.pNext = nullptr;       // 不使用调试回调
        }

        // 创建 Vulkan 实例
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    // 填充调试回调信息
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {}; // 重置结构体
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT; // 启用详细、警告和错误信息
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT; // 启用各种消息类型
        createInfo.pfnUserCallback = debugCallback; // 调试回调函数
    }

    // 设置调试回调
    void setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        // 创建调试回调
        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    // 获取 Vulkan 所需的扩展
    std::vector<const char*> getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // 把扩展存储到 vector 中
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        // 如果启用验证层，加入调试扩展
        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    // 检查验证层是否支持
    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);  // 获取所有支持的层

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // 检查每个验证层是否可用
        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    // 调试回调函数
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl; // 输出调试信息
        return VK_FALSE;
    }
};

int main() {
    HelloTriangleApplication app; // 创建应用程序对象

    try {
        app.run(); // 运行应用程序
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;  // 如果发生异常，输出错误信息
        return EXIT_FAILURE; // 返回失败状态码
    }

    return EXIT_SUCCESS; // 程序正常结束
}
