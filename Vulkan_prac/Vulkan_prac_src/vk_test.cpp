// vk_test.cpp
#include "vk_test.hpp"


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
    createSwapChain();
    getSwapChainImages(swapChainImages);
    createImageView();
    createGraphicsPipeline();
}

void HelloTriangleApplication::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void HelloTriangleApplication::cleanup() {
    vkDestroyPipelineLayout(logicDevice, pipelineLayout, nullptr);
    for (const auto& imageView : imageViews){
        vkDestroyImageView(logicDevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(logicDevice, swapChain, nullptr);
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
        throw std::runtime_error("Failed to find suitable queue families!");
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
    std::set<uint32_t> set_indices = {q_family.graphicsQueueFamily.value(), q_family.presentQueueFamily.value()};

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
    imageViews.resize(swapChainImages.size());
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
        if (vkCreateImageView(logicDevice, &imageViewCreateInfo, nullptr, &imageViews[index]) != VK_SUCCESS){
            throw std::runtime_error("Failed to create image view!");
        }
    }
}

// 图形管线

void HelloTriangleApplication::createGraphicsPipeline(){
    auto vertShaderCode = readFile("../shader/vert.spv");
    auto fragShaderCode = readFile("../shader/frag.spv");

    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pNext = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pNext = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr;       // 可选
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr;     // 可选

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

    // 当选择动态视口和剪裁矩形时，需要为管线启用相应的动态状态
    std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    // 然后只需在管线创建时指定它们的计数
    VkPipelineViewportStateCreateInfo viewPortCreateInfo{};
    viewPortCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewPortCreateInfo.viewportCount = 1;
    viewPortCreateInfo.scissorCount = 1;

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
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f;      // 可选
    rasterizer.depthBiasClamp = 0.0f;               // 可选
    rasterizer.depthBiasSlopeFactor = 0.0f;         // 可选

    // 颜色混合
    // 有两种结构体用于配置颜色混合。第一个结构体 VkPipelineColorBlendAttachmentState 包含每个附加帧缓冲区的配置，
    // 第二个结构体 VkPipelineColorBlendStateCreateInfo 包含全局颜色混合设置。
    // 在我们的例子中只有一个帧缓冲区
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    // 该选项负责不透明的效果，性能更好
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;         // 可选
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;        // 可选
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;                    // 可选
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;         // 可选
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;        // 可选
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;                    // 可选

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

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;              // 可选
    pipelineLayoutInfo.pSetLayouts = nullptr;           // 可选
    pipelineLayoutInfo.pushConstantRangeCount = 0;      // 可选
    pipelineLayoutInfo.pPushConstantRanges = nullptr;   // 可选

    if (vkCreatePipelineLayout(logicDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
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
        throw std::runtime_error("Failed to create shader module!");
    }
    return shaderModule;
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