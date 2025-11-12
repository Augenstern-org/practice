// vk_test.cpp
#include "vk_test.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>

// 定义窗口大小
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// 验证层设置
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

// 设备拓展
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


// ---- HelloTriangleApplication 实现 ----

void HelloTriangleApplication::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void HelloTriangleApplication::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void HelloTriangleApplication::initVulkan() {
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickupPhysicalDevice();
    createLogicDevice();
}

void HelloTriangleApplication::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void HelloTriangleApplication::cleanup() {
    vkDestroyDevice(logicDevice, nullptr);

    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }


    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void HelloTriangleApplication::createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}



void HelloTriangleApplication::pickupPhysicalDevice(){
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0){
        throw std::runtime_error("No device available!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    for(const auto& PhysicalDevice: devices){
        if (isDeviceSuitable(PhysicalDevice)){
            device = PhysicalDevice;
            break;
        }
    }
    if (device == nullptr){
        throw std::runtime_error("No Physical Device Available!");
    }
}

bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice currentDevice){
    VkPhysicalDeviceProperties deviceProperties;    // 储存设备
    VkPhysicalDeviceFeatures deviceFeatures;         // 储存设备支持的特性
    vkGetPhysicalDeviceProperties(currentDevice, &deviceProperties);
    vkGetPhysicalDeviceFeatures(currentDevice, &deviceFeatures);
    q_family = findQueueFamilyIndex(currentDevice);
    bool deviceExtensionSupported = checkDeviceExtensionSupported(currentDevice);
    bool swapChainAdequate = false;
    if (deviceExtensionSupported) {
        SwapChainDetails details = querySwapChainSupport(currentDevice);
        swapChainAdequate = !details.formats.empty() && !details.modes.empty();
    }

    std::cout << deviceProperties.deviceName << std::endl;

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && 
                                            deviceFeatures.geometryShader &&
                                            q_family.isComplete() &&
                                            deviceExtensionSupported &&
                                            swapChainAdequate;
    // 这里是挑选 “独立显卡” 并且还支持 “几何着色器” 的显卡
}

QueueFamily HelloTriangleApplication::findQueueFamilyIndex(VkPhysicalDevice c_device){
    uint32_t queueFamilyPropertyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(c_device, &queueFamilyPropertyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyPropertyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(c_device, &queueFamilyPropertyCount, queueFamilies.data());

    int index = 0;
    QueueFamily foundQueueFamily;
    for (const auto& qf : queueFamilies) {
        if (qf.queueFlags && VK_QUEUE_GRAPHICS_BIT) {
            foundQueueFamily.graphicsQueueFamily = index;
        }

        VkBool32 presentSupported = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(c_device, index, surface, &presentSupported);
        if (presentSupported == true) {
            foundQueueFamily.presentQueueFamily = index;
        }
        if (foundQueueFamily.isComplete()) {
            break;
        }
        ++index;
    }
    return foundQueueFamily;
}

bool HelloTriangleApplication::checkDeviceExtensionSupported(VkPhysicalDevice c_device) {
    uint32_t deviceExtensionCount;
    vkEnumerateDeviceExtensionProperties(c_device, nullptr, &deviceExtensionCount, nullptr);
    std::vector<VkExtensionProperties> deviceExtensionProperties(deviceExtensionCount);
    vkEnumerateDeviceExtensionProperties(c_device, nullptr, &deviceExtensionCount, deviceExtensionProperties.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
    for (const auto& Extension : deviceExtensionProperties) {
        requiredExtensions.erase(Extension.extensionName);
    }
    return requiredExtensions.empty();
}


void HelloTriangleApplication::createLogicDevice() {
    std::set<uint32_t> indices = {q_family.graphicsQueueFamily.value(), q_family.presentQueueFamily.value()};

    float queueProperties = 1.f;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (uint32_t index : indices) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = index;
        queueCreateInfo.queueCount = 1;     // 支持同时处理的队列数
        queueCreateInfo.pQueuePriorities = &queueProperties;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    // Vulkan 逻辑设备开启的功能
    VkPhysicalDeviceFeatures features{};
    // 要开启的话就在下面添加对应功能
    // 功能的值为bool值
    // 示例如下：
    // features.geometryShader = 1;
    // features.xxx
    // ...

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &features;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (vkCreateDevice(device, &createInfo, nullptr, &logicDevice) != VK_SUCCESS) {
        throw std::runtime_error("Failed to Create Logic Device!");
    }
    vkGetDeviceQueue(logicDevice, q_family.graphicsQueueFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(logicDevice, q_family.presentQueueFamily.value(), 0, &presentQueue);
}

// Surface 功能：
// 1. 抽象抽象窗口系统之间的差异
// 2. 绑定物理窗口
// 3. 作为交换链的基础
//
// 与窗口系统的交互流程：
// 1. 绑定原生窗口
// 2. 协商显示参数
// 3. 缓冲区交换

void HelloTriangleApplication::createSurface() {
    // VkWin32SurfaceCreateInfoKHR surface_create_info{};
    // surface_create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    // surface_create_info.hwnd = glfwGetWin32Window(window);
    // surface_create_info.hinstance = GetModuleHandle(nullptr);

    // if (vkCreateWin32SurfaceKHR(instance, &surface_create_info, nullptr, &surface) != VK_SUCCESS) {
    //     throw std::runtime_error("failed to create window surface!");
    // }

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to Create Window Surface!");
    }
}

// 交换链创建流程
// 查询支持细节 -> 选择参数 -> 创建交换链 -> 获取图像

SwapChainDetails HelloTriangleApplication::querySwapChainSupport(VkPhysicalDevice c_device) {
    SwapChainDetails details{};
    details.capabilities = getSurfaceCapabilities(c_device);
    details.formats = getSurfaceFormat(c_device);
    details.modes = getSurfacePresentMode(c_device);
}

VkSurfaceCapabilitiesKHR HelloTriangleApplication::getSurfaceCapabilities(VkPhysicalDevice c_device) {
    VkSurfaceCapabilitiesKHR surface_capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(c_device, surface, &surface_capabilities);
    return surface_capabilities;
}

std::vector<VkSurfaceFormatKHR> HelloTriangleApplication::getSurfaceFormat(VkPhysicalDevice c_device) {
    std::vector<VkSurfaceFormatKHR> surface_formats;
    uint32_t surface_formats_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(c_device, surface, &surface_formats_count, nullptr);

    if (surface_formats_count != 0) {
        vkGetPhysicalDeviceSurfaceFormatsKHR(c_device, surface, &surface_formats_count, surface_formats.data());
    }
    return surface_formats;
}

std::vector<VkPresentModeKHR> HelloTriangleApplication::getSurfacePresentMode(VkPhysicalDevice c_device) {
    std::vector<VkPresentModeKHR> modes;
    uint32_t surface_present_modes_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(c_device, surface, &surface_present_modes_count, nullptr);

    if (surface_present_modes_count != 0) {
        vkGetPhysicalDeviceSurfacePresentModesKHR(c_device, surface, &surface_present_modes_count, modes.data());
    }
    return modes;
}




// ---- Debug 相关 ----
void HelloTriangleApplication::setupDebugMessenger() {
    if (!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

std::vector<const char*> HelloTriangleApplication::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (enableValidationLayers)
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return extensions;
}

bool HelloTriangleApplication::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) return false;
    }
    return true;
}

void HelloTriangleApplication::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

VKAPI_ATTR VkBool32 VKAPI_CALL HelloTriangleApplication::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

// ---- Vulkan 调试扩展函数 ----

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger) {

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != nullptr)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator) {

    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func != nullptr)
        func(instance, debugMessenger, pAllocator);
}