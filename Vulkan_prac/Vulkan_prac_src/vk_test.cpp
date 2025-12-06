// vk_test.cpp
#include "vk_test.hpp"
#include "shader.hpp"
#include <cmath>

const int MAX_FRAMES_IN_FLIGHT = 2;


// 定义窗口大小
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 700;

// 验证层设置
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

// 设备拓展
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
    // VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME,
    // VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME

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
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void HelloTriangleApplication::initVulkan() {
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickupPhysicalDevice();
    createLogicDevice();
    createSwapChain();
    createImageView();
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicsPipeline();
    createFrameBuffers();
    createCommandPool();
    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createDescriptorSets();
    createCommandBuffers();
    createSyncObjects();
}

void HelloTriangleApplication::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame();
    }
    vkDeviceWaitIdle(logicDevice);
}

void HelloTriangleApplication::cleanup() {
    cleanupSwapChain();

    vkDestroyPipeline(logicDevice, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(logicDevice, pipelineLayout, nullptr);

    vkDestroyRenderPass(logicDevice, renderPass, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(logicDevice, uniformBuffers[i], nullptr);
        vkFreeMemory(logicDevice, uniformBuffersMemory[i], nullptr);
    }

    vkDestroyDescriptorPool(logicDevice, descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(logicDevice, descriptorSetLayout, nullptr);

    vkDestroyBuffer(logicDevice, indexBuffer, nullptr);
    vkFreeMemory(logicDevice, indexBufferMemory, nullptr);

    vkDestroyBuffer(logicDevice, vertexBuffer, nullptr);
    vkFreeMemory(logicDevice, vertexBufferMemory, nullptr);

    for (size_t index = 0; index != MAX_FRAMES_IN_FLIGHT; ++index){
        vkDestroySemaphore(logicDevice, renderFinishedSemaphores[index], nullptr);
        vkDestroySemaphore(logicDevice, imageAvailableSemaphores[index], nullptr);
        vkDestroyFence(logicDevice, inFlightFences[index], nullptr);
    }
    vkDestroyCommandPool(logicDevice, commandPool, nullptr);

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

    // 打印获取到的扩展列表
    // std::cout << "Required extensions:" << std::endl;
    // for (const auto& ext : extensions) {
    //     std::cout << "\t" << ext << std::endl;
    // }
    
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
    if (device == VK_NULL_HANDLE){
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
        
        // debug
        // std::cout << details.formats.empty() << details.modes.empty() << std::endl;
        
        swapChainAdequate = !details.formats.empty() && !details.modes.empty();
    }

    const bool condition = (q_family.isComplete() &&
                            (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) &&
                            deviceFeatures.geometryShader &&
                            deviceExtensionSupported &&
                            swapChainAdequate
    );


    // std::cout << deviceProperties.deviceName << " is OK: " << condition << std::endl;
    // std::cout << deviceProperties.deviceName 
    //     << " is OK: " 
    //     << "isComplete = " << q_family.isComplete() << ", "
    //     << "deviceExtensionSupported = " << deviceExtensionSupported << ", "
    //     << "swapChainAdequate = " << swapChainAdequate
    //     << std::endl;


    return condition;
    // 这里是挑选 “独立显卡” 并且还支持 “几何着色器” 的显卡
}



QueueFamily HelloTriangleApplication::findQueueFamilyIndex(VkPhysicalDevice c_device){
    QueueFamily foundQueueFamily;
    uint32_t queueFamilyPropertyCount = 0;

    // if (c_device == VK_NULL_HANDLE) {
    //     throw std::runtime_error("Invalid physical device!");
    // }

    // if (surface == nullptr) {
    //     throw std::runtime_error("Invalid physical device!");
    // }

    vkGetPhysicalDeviceQueueFamilyProperties(c_device, &queueFamilyPropertyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyPropertyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(c_device, &queueFamilyPropertyCount, queueFamilies.data());

    int index = 0;

    for (const auto& qf : queueFamilies) {
        if (qf.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            foundQueueFamily.graphicsQueueFamily = index;
        }

        VkBool32 presentSupported = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(c_device, index, surface, &presentSupported);
        if (presentSupported) {
            foundQueueFamily.presentQueueFamily = index;
        }
        if (foundQueueFamily.isComplete()) {
            break;
        }
        ++index;
    }
    if (!foundQueueFamily.isComplete()) {
        throw std::runtime_error("failed to find suitable queue families!");
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
    QueueFamily indices = findQueueFamilyIndex(device);
    std::set<uint32_t> set_indices = {indices.graphicsQueueFamily.value(), indices.presentQueueFamily.value()};

    float queueProperties = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (uint32_t index : set_indices) {
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
        throw std::runtime_error("failed to Create Logic Device!");
    }
    vkGetDeviceQueue(logicDevice, indices.graphicsQueueFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(logicDevice, indices.presentQueueFamily.value(), 0, &presentQueue);
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
        throw std::runtime_error("failed to Create Window Surface!");
    }
}

// 交换链创建流程
// 查询支持细节 -> 选择参数 -> 创建交换链 -> 获取图像

// SwapChainDetails HelloTriangleApplication::querySwapChainSupport(VkPhysicalDevice c_device) {
//     SwapChainDetails details{};
//     details.capabilities = getSurfaceCapabilities(c_device);
//     details.formats = getSurfaceFormat(c_device);
//     details.modes = getSurfacePresentMode(c_device);
//     return details;
// }

// VkSurfaceCapabilitiesKHR HelloTriangleApplication::getSurfaceCapabilities(VkPhysicalDevice c_device) {
//     VkSurfaceCapabilitiesKHR surface_capabilities;
//     vkGetPhysicalDeviceSurfaceCapabilitiesKHR(c_device, surface, &surface_capabilities);
//     return surface_capabilities;
// }

// std::vector<VkSurfaceFormatKHR> HelloTriangleApplication::getSurfaceFormat(VkPhysicalDevice c_device) {
//     std::vector<VkSurfaceFormatKHR> surface_formats;
//     uint32_t surface_formats_count;
//     vkGetPhysicalDeviceSurfaceFormatsKHR(c_device, surface, &surface_formats_count, nullptr);

//     // std::cout << "surface_formats_count: " << surface_formats_count << std::endl;

//     if (surface_formats_count != 0) {
        
//         vkGetPhysicalDeviceSurfaceFormatsKHR(c_device, surface, &surface_formats_count, surface_formats.data());
//     }
//     return surface_formats;
// }

// std::vector<VkPresentModeKHR> HelloTriangleApplication::getSurfacePresentMode(VkPhysicalDevice c_device) {
//     std::vector<VkPresentModeKHR> modes;
//     uint32_t surface_present_modes_count;
//     vkGetPhysicalDeviceSurfacePresentModesKHR(c_device, surface, &surface_present_modes_count, nullptr);

//     // std::cout << "surface_present_modes_count: " << surface_present_modes_count << std::endl;

//     if (surface_present_modes_count != 0) {
//         vkGetPhysicalDeviceSurfacePresentModesKHR(c_device, surface, &surface_present_modes_count, modes.data());
//     }
//     return modes;
// }

SwapChainDetails HelloTriangleApplication::querySwapChainSupport(VkPhysicalDevice device) {
    SwapChainDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
        details.modes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.modes.data());
    }

    return details;
}

VkSurfaceFormatKHR HelloTriangleApplication::chooseSurfaceFormat(const SwapChainDetails& details) {
    const std::vector<VkSurfaceFormatKHR>& available_formats = details.formats;
    for (const auto& available_format : available_formats) {
        if (available_format.format == VK_FORMAT_B8G8R8_SRGB &&
            available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {

            return available_format;
        }
    }
    return available_formats[0];
}

VkPresentModeKHR HelloTriangleApplication::chooseSurfacePresentMode(const SwapChainDetails& details) {
    const std::vector<VkPresentModeKHR>& available_present_modes = details.modes;
    for (const auto& available_present_mode : available_present_modes) {
        if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return available_present_mode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D HelloTriangleApplication::chooseExtent2D(const SwapChainDetails &details) {
    const VkSurfaceCapabilitiesKHR& capabilities = details.capabilities;
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

void HelloTriangleApplication::createSwapChain() {
    SwapChainDetails swapChainSupport = querySwapChainSupport(device);

    VkSurfaceFormatKHR surfaceFormat = chooseSurfaceFormat(swapChainSupport);
    VkPresentModeKHR presentMode = chooseSurfacePresentMode(swapChainSupport);
    VkExtent2D extent = chooseExtent2D(swapChainSupport);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamily indices = findQueueFamilyIndex(device);
    uint32_t queueFamilyIndices[] = {indices.graphicsQueueFamily.value(), indices.presentQueueFamily.value()};

    if (indices.graphicsQueueFamily != indices.presentQueueFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(logicDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(logicDevice, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(logicDevice, swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainImageExtent = extent;
}

void HelloTriangleApplication::getSwapChainImages(std::vector<VkImage>& images){
    uint32_t imageCount;
    vkGetSwapchainImagesKHR(logicDevice, swapChain, &imageCount, nullptr);
    if (imageCount != 0){
        images.resize(imageCount);
        vkGetSwapchainImagesKHR(logicDevice, swapChain, &imageCount, images.data());
    }
}

void HelloTriangleApplication::createImageView(){
    swapChainImageViews.resize(swapChainImages.size());
    for (int index = 0; index != swapChainImages.size(); ++index){
        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image = swapChainImages[index];
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = swapChainImageFormat;
        imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;    // 图像用途
        imageViewCreateInfo.subresourceRange.baseMipLevel = 0;                          // 初始mipmap层数
        imageViewCreateInfo.subresourceRange.levelCount = 1;                            // mipmap层数
        imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
        imageViewCreateInfo.subresourceRange.layerCount = 1;
        if (vkCreateImageView(logicDevice, &imageViewCreateInfo, nullptr, &swapChainImageViews[index]) != VK_SUCCESS){
            throw std::runtime_error("failed to create image view!");
        }
    }
}

// 着色器
std::vector<char> HelloTriangleApplication::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    // 从文件末尾开始读取的优点是，可以使用读取位置来确定文件的大小并分配缓冲区

    if (!file.is_open()) {
        // auto c_dir = std::filesystem::current_path();
        // std::cout << "Current Path: " << c_dir << std::endl;
        throw std::runtime_error("failed to open the file!");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    // 寻址返回开头正式开始读取
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    
    return buffer;
}

// 图形管线

void HelloTriangleApplication::createGraphicsPipeline(){
    auto vertShaderCode = readFile("../../../Vulkan_prac_src/shader/vert.spv");
    auto fragShaderCode = readFile("../../../Vulkan_prac_src/shader/frag.spv");

    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    
    // 管理着色器
    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    // 输入汇编
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    // 视区
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) swapChainImageExtent.width;
    viewport.height = (float) swapChainImageExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    // 裁剪矩形
    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapChainImageExtent;

    // 然后只需在管线创建时指定它们的计数
    VkPipelineViewportStateCreateInfo viewportStateCreateInfo{};
    viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCreateInfo.viewportCount = 1;
    viewportStateCreateInfo.scissorCount = 1;

    // 光栅化器
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;

    // polygonMode 确定如何为几何图形生成片段。以下模式可用
    // · VK_POLYGON_MODE_FILL：用片段填充多边形的区域
    // · VK_POLYGON_MODE_LINE：多边形边缘绘制为线条
    // · VK_POLYGON_MODE_POINT：多边形顶点绘制为点
    // 使用填充以外的任何模式都需要启用 GPU 功能。
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_NONE;
    // rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f;          // 可选
    rasterizer.depthBiasClamp = 0.0f;                   // 可选
    rasterizer.depthBiasSlopeFactor = 0.0f;             // 可选

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;              // 可选
    multisampling.pSampleMask = nullptr;                // 可选
    multisampling.alphaToCoverageEnable = VK_FALSE;     // 可选
    multisampling.alphaToOneEnable = VK_FALSE;          // 可选

    // 深度与模板测试
    VkPipelineDepthStencilStateCreateInfo depthStencilStateInfo{};

    // 颜色混合
    // 有两种结构体用于配置颜色混合。第一个结构体 VkPipelineColorBlendAttachmentState 包含每个附加帧缓冲区的配置，
    // 第二个结构体 VkPipelineColorBlendStateCreateInfo 包含全局颜色混合设置。
    // 在我们的例子中只有一个帧缓冲区
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    // 该选项负责不透明的效果，性能更好
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;                                    // 可选
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;                                    // 可选
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;                         // 可选
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;                        // 可选
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;                   // 可选
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;         // 可选

    // 针对烟雾、粒子、UI等效果采用该选项可实现透明效果
    // colorBlendAttachment.blendEnable = VK_TRUE;
    // colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    // colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    // colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    // colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    // colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    // colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;   // 可选
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;     // 可选
    colorBlending.blendConstants[1] = 0.0f;     // 可选
    colorBlending.blendConstants[2] = 0.0f;     // 可选
    colorBlending.blendConstants[3] = 0.0f;     // 可选

    // 当选择动态视口和剪裁矩形时，需要为管线启用相应的动态状态
    std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 0;      // 可选
    pipelineLayoutInfo.pPushConstantRanges = nullptr;   // 可选

    if (vkCreatePipelineLayout(logicDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportStateCreateInfo;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.pNext = nullptr;

    // 引用描述固定功能阶段的所有结构
    pipelineInfo.layout = pipelineLayout;

    // 之后是管线布局，它是一个 Vulkan 句柄，而不是一个结构指针
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;

    // 实际上还有两个参数：basePipelineHandle 和 basePipelineIndex。Vulkan 允许您通过派生自现有管线来创建新的图形管线。
    // 管线派生的思想是，当它们与现有管线具有许多共同功能时，设置管线的成本较低，并且在同一父级管线之间切换也可以更快地完成。
    // 您可以使用 basePipelineHandle 指定现有管线的句柄，也可以使用 basePipelineIndex 引用即将创建的另一个管线的索引。
    // 目前只有一个管线，所以我们只需指定一个空句柄和一个无效索引。
    // 只有在 VkGraphicsPipelineCreateInfo 的 flags 字段中也指定了 VK_PIPELINE_CREATE_DERIVATIVE_BIT 标志时，
    // 才会使用这些值。
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    // pipelineInfo.basePipelineIndex = -1;

    // 创建图形管线
    if (vkCreateGraphicsPipelines(logicDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    // 清理工作
    vkDestroyShaderModule(logicDevice, fragShaderModule, nullptr);
    vkDestroyShaderModule(logicDevice, vertShaderModule, nullptr);

}

VkShaderModule HelloTriangleApplication::createShaderModule(const std::vector<char>& code){
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*> (code.data());
    VkShaderModule shaderModule;

    if (vkCreateShaderModule(logicDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS){
        throw std::runtime_error("failed to create shader module!");
    }
    return shaderModule;
}

void HelloTriangleApplication::createRenderPass(){
    VkAttachmentDescription colorAttachment{};
    colorAttachment.flags = 0;
    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency dependency{};
    // 指定依赖项与被依赖项的索引
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    // 指定等待的操作以及该操作发生的阶段 -> 等待交换链完成从图像的读取
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    // 等待颜色附件阶段
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT; 

    VkRenderPassCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    // 指定附件与子通道
    createInfo.attachmentCount = 1;
    createInfo.pAttachments = &colorAttachment;
    createInfo.subpassCount = 1;
    createInfo.pSubpasses = &subpass;
    // 指定依赖项的数组
    createInfo.dependencyCount = 1;
    createInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(logicDevice, &createInfo, nullptr, &renderPass) != VK_SUCCESS){
        throw std::runtime_error("failed to create render pass!");
    }
}

void HelloTriangleApplication::createFrameBuffers() {
    swapChainFramebuffers.resize(swapChainImageViews.size());
    for (size_t index = 0; index != swapChainFramebuffers.size(); ++index) {
        // 首先需要指定帧缓冲需要与哪个 renderPass 兼容
        // 只能将帧缓冲与它兼容的渲染通道一起使用
        // 这大致意味着它们使用相同数量和类型的附件
        VkImageView attachments[] = {
            swapChainImageViews[index]
        };

        VkFramebufferCreateInfo framebufferCreateInfo{};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.pNext = nullptr;
        framebufferCreateInfo.renderPass = renderPass;
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = attachments;
        framebufferCreateInfo.width = swapChainImageExtent.width;
        framebufferCreateInfo.height = swapChainImageExtent.height;
        framebufferCreateInfo.layers = 1;

        if (vkCreateFramebuffer(logicDevice, &framebufferCreateInfo, nullptr, &swapChainFramebuffers[index])
                != VK_SUCCESS) {
            throw std::runtime_error("failed to create frame buffer!");
        }
    }
}

void HelloTriangleApplication::createCommandPool() {
    // 命令池有两个可能的标志
    //
    // ·VK_COMMAND_POOL_CREATE_TRANSIENT_BIT：
    //     提示命令缓冲区经常被新的命令重新记录（可能会改变内存分配行为）
    //
    // ·VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT：
    //     允许单独重新记录命令缓冲区，如果没有此标志，则必须一起重置所有命令缓冲区
    //
    // 我们将在每一帧都记录一个命令缓冲区，因此我们希望能够重置并重新记录它。
    // 因此，我们需要为我们的命令池设置 VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT 标志位。
    //
    // 命令缓冲区通过在设备队列（例如我们检索到的图形和呈现队列）之一上提交来执行。
    // 每个命令池只能分配在单一类型的队列上提交的命令缓冲区。
    // 我们将要记录用于绘图的命令，这就是我们选择图形队列族的原因。
    QueueFamily queueFamilyIndices = findQueueFamilyIndex(device);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsQueueFamily.value();

    if (vkCreateCommandPool(logicDevice, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void HelloTriangleApplication::createCommandBuffers() {
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.commandPool = commandPool;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.commandBufferCount = (uint32_t) commandBuffers.size();

    if (vkAllocateCommandBuffers(logicDevice, &allocateInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void HelloTriangleApplication::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    // 启动渲染通道
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
    // 绑定通道与附件
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainImageExtent;
    // 定义渲染区域的大小
    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    // 定义了 VK_ATTACHMENT_LOAD_OP_CLEAR 的清除值
    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // 绑定图形管线
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    // 初始化之前设置的动态管线部分
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapChainImageExtent.width);
    viewport.height = static_cast<float>(swapChainImageExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapChainImageExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    // 实际的 vkCmdDraw 函数有点虎头蛇尾，但它如此简单是因为我们预先指定的所有信息。除了命令缓冲区之外，它还有以下参数:
    // ·vertexCount：
    //     即使我们没有顶点缓冲区，我们技术上仍然有 3 个顶点要绘制。
    // ·instanceCount：
    //     用于实例化渲染，如果不这样做，则使用 1。
    // ·firstVertex：
    //     用作顶点缓冲区的偏移量，定义了 gl_VertexIndex 的最小值。
    // ·firstInstance：
    //     用作实例化渲染的偏移量，定义了 gl_InstanceIndex 的最小值。

    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[currentFrame], 0, nullptr);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

    // 完成渲染
    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void HelloTriangleApplication::drawFrame(){
    // 在高层次上，在 Vulkan 中渲染帧包含一组常见的步骤：
    //      ·等待前一帧完成
    //      ·从交换链获取图像
    //      ·记录一个命令缓冲区，该缓冲区将场景绘制到该图像上
    //      ·提交已记录的命令缓冲区
    //      ·呈现交换链图像

    // 我们有两种同步原语可供使用，并且方便地有两个地方可以应用同步：
    //     ·交换链操作和等待前一帧完成。
    //
    // 我们希望使用信号量来进行交换链操作，因为它们发生在 GPU 上，因此如果可以避免，我们不希望让主机等待。
    // 对于等待前一帧完成，我们希望使用栅栏，原因恰恰相反，因为我们需要主机等待。这样我们就不会一次绘制多个帧。
    // 因为我们每帧都重新记录命令缓冲区，所以在当前帧执行完成之前，
    // 我们不能将下一帧的工作记录到命令缓冲区中，因为我们不希望在 GPU 使用命令缓冲区时覆盖其当前内容。

    vkWaitForFences(logicDevice, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);   // 等待前一帧

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(logicDevice, swapChain, UINT64_MAX, 
                                            imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

    vkResetFences(logicDevice, 1, &inFlightFences[currentFrame]);                           // 手动重置fence

    // 获取图像

    vkResetCommandBuffer(commandBuffers[currentFrame], 0);
    recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

    // 更新 uniform 缓冲区数据
    updateUniformBuffer(currentFrame);

    // 提交命令缓冲区
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};                // 等待什么信号量
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};    // 在什么阶段等待
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    // 重新提交到交换链
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr;

    result = vkQueuePresentKHR(presentQueue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false;
        recreateSwapChain();
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void HelloTriangleApplication::createSyncObjects(){
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreCreateInfo{};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceCreateInfo{};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t index = 0; index != MAX_FRAMES_IN_FLIGHT; ++index){
        if (vkCreateSemaphore(logicDevice, &semaphoreCreateInfo, nullptr, &imageAvailableSemaphores[index]) != VK_SUCCESS ||
            vkCreateSemaphore(logicDevice, &semaphoreCreateInfo, nullptr, &renderFinishedSemaphores[index]) != VK_SUCCESS ||
            vkCreateFence(logicDevice, &fenceCreateInfo, nullptr, &inFlightFences[index]) != VK_SUCCESS){
                throw std::runtime_error("failed to create semaphores!");
        }
    }
}

void HelloTriangleApplication::recreateSwapChain() {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(logicDevice);

    createSwapChain();
    createImageView();
    createFrameBuffers();
}

void HelloTriangleApplication::cleanupSwapChain() {
    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(logicDevice, framebuffer, nullptr);
    }

    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(logicDevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(logicDevice, swapChain, nullptr);
}

void HelloTriangleApplication::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;

}



void HelloTriangleApplication::createVertexBuffer() {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                                               VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
                stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(logicDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(logicDevice, stagingBufferMemory);

    // VK_BUFFER_USAGE_TRANSFER_SRC_BIT：
    //     缓冲区可以用作内存传输操作的源。
    // VK_BUFFER_USAGE_TRANSFER_DST_BIT：
    //     缓冲区可以用作内存传输操作的目的地。
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
    copyBuffer(stagingBuffer, vertexBuffer, bufferSize);
    // 清理暂存缓冲区
    vkDestroyBuffer(logicDevice, stagingBuffer, nullptr);
    vkFreeMemory(logicDevice, stagingBufferMemory, nullptr);
}

void HelloTriangleApplication::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, 
                                            VkMemoryPropertyFlags properties, VkBuffer& buffer,
                                             VkDeviceMemory& bufferMemory){
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(logicDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS){
        throw std::runtime_error("failed to create Vertex Buffer!");
    }

    // 获取内存需求
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(logicDevice, buffer, &memRequirements);

    // VkMemoryRequirements 结构具有三个字段
    // size：
    //     所需内存量的字节大小，可能与 bufferInfo.size 不同。
    // alignment：
    //     缓冲区在内存分配区域中开始的字节偏移量，取决于 bufferInfo.usage 和 bufferInfo.flags。
    // memoryTypeBits：
    //     适用于该缓冲区的内存类型的位域。

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(logicDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vertex buffer memory!");
    }

    vkBindBufferMemory(logicDevice, buffer, bufferMemory, 0);
}

uint32_t HelloTriangleApplication::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(device, &memProperties);

    // 查找合适的内存类型
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; ++i) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void HelloTriangleApplication::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(logicDevice, &allocInfo, &commandBuffer);

    // 记录缓冲区
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    // 传输命令
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    // 清理缓冲区
    vkFreeCommandBuffers(logicDevice, commandPool, 1, &commandBuffer);

}

void HelloTriangleApplication::createIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                                               VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingBufferMemory);
    void* data;
    vkMapMemory(logicDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(logicDevice, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    copyBuffer(stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer(logicDevice, stagingBuffer, nullptr);
    vkFreeMemory(logicDevice, stagingBufferMemory, nullptr);
}

void HelloTriangleApplication::createDescriptorSetLayout() {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    if (vkCreateDescriptorSetLayout(logicDevice, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void HelloTriangleApplication::createDescriptorPool() {
    // 使用 VkDescriptorPoolSize 结构描述描述符集将包含哪些描述符类型以及它们的数量
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t> (MAX_FRAMES_IN_FLIGHT);

    // 每一帧分配一个这些描述符。此池大小结构由主要的 VkDescriptorPoolCreateInfo 引用
    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;

    // 除了可用的单个描述符的最大数量外，还需要指定可以分配的最大描述符集数量
    poolInfo.maxSets = static_cast<uint32_t> (MAX_FRAMES_IN_FLIGHT);

    if (vkCreateDescriptorPool(logicDevice, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void HelloTriangleApplication::createDescriptorSets() {
    std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();

    descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(logicDevice, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        // 引用缓冲区的描述符（例如我们的统一缓冲区描述符）使用 VkDescriptorBufferInfo 结构进行配置
        // 此结构指定缓冲区以及其中包含描述符数据的区域
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        // 如果覆盖整个缓冲区，那么也可以将 VK_WHOLE_SIZE 值用于范围。
        // 描述符的配置使用 vkUpdateDescriptorSets 函数更新，该函数接受 VkWriteDescriptorSet 结构的数组作为参数。

        // 前两个字段指定要更新的描述符集和绑定。我们给统一缓冲区绑定索引 0。
        // 请记住，描述符可以是数组，因此我们还需要指定要更新的数组中的第一个索引。我们没有使用数组，因此索引只是 0。
        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = descriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;

        // 我们需要再次指定描述符的类型。
        // 可以在一个数组中一次更新多个描述符，从索引 dstArrayElement 开始。
        // descriptorCount 字段指定要更新的数组元素的数量。
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;

        // 最后一个字段引用一个包含 descriptorCount 结构的数组，该结构实际上配置了描述符。
        // 根据描述符的类型，您实际上需要使用这三个中的哪一个。
        // pBufferInfo 字段用于引用缓冲区数据的描述符，
        // pImageInfo 用于引用图像数据的描述符，
        // pTexelBufferView 用于引用缓冲区视图的描述符。
        // 我们的描述符基于缓冲区，因此我们使用 pBufferInfo。
        descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = nullptr;
        descriptorWrite.pTexelBufferView = nullptr;

        // 使用 vkUpdateDescriptorSets 应用更新。
        // 它接受两种类型的数组作为参数：VkWriteDescriptorSet 数组和 VkCopyDescriptorSet 数组。
        // 后者可用于将描述符相互复制，正如其名称所示
        vkUpdateDescriptorSets(logicDevice, 1, &descriptorWrite, 0, nullptr);
    }
}

void HelloTriangleApplication::createUniformBuffers() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(logicDevice, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }
}

void HelloTriangleApplication::updateUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
    // ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    ubo.model = glm::mat4(1.0f);
    const float radius = glm::length(glm::vec3(2.0f, 2.0f, 0.0f));
    glm::vec3 cameraPos = glm::vec3(
        radius * sin(time), // X 坐标
        radius * cos(time),               // Y 坐标
        2.0f                // Z 坐标
    );

    // 3. 更新 View 矩阵
    ubo.view = glm::lookAt(
        cameraPos,                      // 摄像机位置（动态变化）
        glm::vec3(0.0f, 0.0f, 0.0f),    // 观察目标点（保持在原点）
        glm::vec3(0.0f, 0.0f, 1.0f)     // 上方向
    );

    ubo.proj = glm::perspective(glm::radians(45.0f), swapChainImageExtent.width / (float) swapChainImageExtent.height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
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
    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
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