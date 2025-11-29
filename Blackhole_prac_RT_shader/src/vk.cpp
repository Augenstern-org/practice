//
// Created by Neuroil on 2025/11/26.
//
#include "vk.hpp"

#include <queue>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// 飞行帧
constexpr int MAX_FRAMES_IN_FLIGHT = 2;

// 验证层设置
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

// 设备拓展
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
    VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
    VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME
};

void vk::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void vk::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(windowInfo.width, windowInfo.height, windowInfo.title, nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    // glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void vk::initVulkan() {
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickupPhysicalDevice();
    createLogicDevice();
    createSwapChain();
}

void vk::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void vk::cleanup() {

    vkDestroyDevice(device, nullptr);
    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void vk::createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("failed to load validation layers!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Black Hole Application";
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

bool vk::checkValidationLayerSupport() {
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

std::vector<const char *> vk::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;
}

VkResult vk::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT*pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != nullptr)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void vk::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<vk*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

void vk::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
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
VKAPI_ATTR VkBool32 VKAPI_CALL vk::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

SwapChainDetails vk::querySwapChainSupport(VkPhysicalDevice c_device) {
    SwapChainDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(c_device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(c_device, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(c_device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(c_device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.modes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(c_device, surface, &presentModeCount, details.modes.data());
    }

    return details;
}

void vk::setupDebugMessenger() {
    if (!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to create debug messenger!");
    }
}

void vk::createSurface() {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to Create Window Surface!");
    }
}

void vk::pickupPhysicalDevice() {
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to enumerate physical device!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& c_device : devices) {
        if (isPhysicalDeviceSuitable(c_device)) {
            std::cout << isPhysicalDeviceSuitable(c_device) << std::endl;
            physicalDevice = c_device;
            break;
        }
    }
    if (physicalDevice == VK_NULL_HANDLE){
        throw std::runtime_error("No Physical Device Available!");
    }
}

void vk::createLogicDevice() {
    // 开启 VK_Ray_Tracing 拓展
    VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeaturesKHR{};
    accelerationStructureFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    accelerationStructureFeaturesKHR.pNext = nullptr;

    VkPhysicalDeviceRayTracingPipelineFeaturesKHR rayTracingPipelineFeaturesKHR{};
    rayTracingPipelineFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
    rayTracingPipelineFeaturesKHR.pNext = &accelerationStructureFeaturesKHR;

    // features 容器
    VkPhysicalDeviceFeatures2 deviceFeatures2{};
    deviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    deviceFeatures2.pNext = &rayTracingPipelineFeaturesKHR;

    // 查询特性
    vkGetPhysicalDeviceFeatures2(physicalDevice, &deviceFeatures2);

    // 检验是否支持特性
    if (!accelerationStructureFeaturesKHR.accelerationStructure || !rayTracingPipelineFeaturesKHR.rayTracingPipeline) {
        throw std::runtime_error("failed to switch on the required features!");
    }

    QueueFamily indices = findQueueFamily(physicalDevice);
    std::set<uint32_t> set_indices = {q_family.graphicQueueFamily.value(), q_family.presentQueueFamily.value()};

    float queueProperties = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueInfos;
    for (uint32_t index : set_indices) {
        VkDeviceQueueCreateInfo queueInfo{};
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.queueFamilyIndex = index;
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities = &queueProperties;
        queueInfos.push_back(queueInfo);
    }

    VkPhysicalDeviceFeatures features{};

    VkDeviceCreateInfo deviceInfo{};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.pEnabledFeatures = &features;
    deviceInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    deviceInfo.ppEnabledExtensionNames = deviceExtensions.data();
    deviceInfo.pQueueCreateInfos = queueInfos.data();
    deviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
    deviceInfo.pNext = &deviceFeatures2;

    if (vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vk device!");
    }

    vkGetDeviceQueue(device, q_family.graphicQueueFamily.value(), 0, &graphicQueue);
    vkGetDeviceQueue(device, q_family.presentQueueFamily.value(), 0, &presentQueue);
}

void vk::createSwapChain() {
}

bool vk::isPhysicalDeviceSuitable(VkPhysicalDevice c_device) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(c_device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(c_device, &deviceFeatures);
    q_family = findQueueFamily(c_device);
    bool deviceExtensionSupported = checkDeviceExtensionSupported(c_device);
    // bool swapChainAdequate = false;

    // if (deviceExtensionSupported) {
    //     SwapChainDetails details = querySwapChainSupport(c_device);
    //
    //     swapChainAdequate = !details.formats.empty() && !details.modes.empty();
    // }

    const bool condition = (q_family.isComplete() &&
                            (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) &&
                            deviceFeatures.geometryShader &&
                            deviceExtensionSupported
                            // swapChainAdequate
    );
    return condition;
}

QueueFamily vk::findQueueFamily(VkPhysicalDevice c_device) {
    QueueFamily rQueueFamily;
    uint32_t queueFamilyPropertiesCount;
    vkGetPhysicalDeviceQueueFamilyProperties(c_device, &queueFamilyPropertiesCount, nullptr);
    if (queueFamilyPropertiesCount == 0) {
        throw std::runtime_error("there's no queue family!");
    }

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyPropertiesCount);
    vkGetPhysicalDeviceQueueFamilyProperties(c_device, &queueFamilyPropertiesCount, queueFamilies.data());

    int index = 0;

    for (const auto& qf : queueFamilies) {
        if (qf.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            rQueueFamily.graphicQueueFamily = index;
        }

        VkBool32 isPresentModeSupported = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(c_device, index, surface, &isPresentModeSupported);
        if (isPresentModeSupported) {
            rQueueFamily.presentQueueFamily = index;
        }
        if (rQueueFamily.isComplete()) {
            break;
        }
        ++index;
    }

    if (!rQueueFamily.isComplete()) {
        throw std::runtime_error("failed to find suitable queue families!");
    }
    return rQueueFamily;
}

bool vk::checkDeviceExtensionSupported(VkPhysicalDevice c_device) {
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

void vk::DestroyDebugUtilsMessengerEXT(VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator) {

    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func != nullptr)
        func(instance, debugMessenger, pAllocator);
}

