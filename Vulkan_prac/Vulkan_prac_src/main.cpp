// 告诉 GLFW 我们会用 Vulkan，而不是默认的 OpenGL
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

// 定义窗口宽度和高度
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// 封装整个程序的类
class HelloTriangleApplication {
public:
    // 程序入口函数
    void run() {
        initWindow();   // 初始化窗口
        initVulkan();   // 初始化 Vulkan
        mainLoop();     // 主循环（持续响应事件）
        cleanup();      // 清理资源
    }

private:
    GLFWwindow* window;  // 指向窗口对象的指针
    VkInstance instance; // Vulkan 实例句柄，用来与 Vulkan 交互

    // 创建 Vulkan 实例的函数
    void createInstance() {
        // 填充一个 VkApplicationInfo 结构体，提供关于应用程序的基本信息
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; // 必须显式指定结构体类型
        appInfo.pApplicationName = "Hello Triangle";         // 应用程序名称
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // 应用程序版本号
        appInfo.pEngineName = "No Engine";                   // 图形引擎名称（可选）
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);    // 引擎版本号
        appInfo.apiVersion = VK_API_VERSION_1_0;             // 目标 Vulkan API 版本

        // 填充一个 VkInstanceCreateInfo 结构体，用来指定实例的创建信息
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo; // 指向应用程序信息

        // GLFW 用于 Vulkan 的平台扩展（例如 Win32、X11 等）
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        // 通过 GLFW 获取 Vulkan 所需的扩展列表
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // 将这些扩展传递给 Vulkan
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // 暂时不启用任何验证层（调试工具）
        createInfo.enabledLayerCount = 0;

        // 真正创建 Vulkan 实例
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            // 如果创建失败，抛出异常
            throw std::runtime_error("failed to create instance!");
        }
    }

    // 初始化 GLFW 窗口
    void initWindow() {
        glfwInit(); // 初始化 GLFW 库

        // 禁用默认的 OpenGL 上下文，因为我们使用的是 Vulkan
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // 禁止窗口大小调整（为了简单）
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // 创建一个 800x600 的窗口
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    // 初始化 Vulkan（当前只创建实例）
    void initVulkan() {
        createInstance(); // 创建 Vulkan 实例
    }

    // 主循环：窗口每帧处理输入事件
    void mainLoop() {
        // 持续运行直到用户关闭窗口
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents(); // 处理系统事件（如鼠标、键盘输入）
        }
    }

    // 清理程序资源
    void cleanup() {
        // 在销毁窗口前，应该先销毁 Vulkan 实例
        vkDestroyInstance(instance, nullptr);

        // 销毁窗口
        glfwDestroyWindow(window);

        // 终止 GLFW，释放所有分配的资源
        glfwTerminate();
    }
};

// 程序入口
int main() {
    HelloTriangleApplication app; // 创建应用程序对象

    try {
        app.run(); // 运行程序
    } catch (const std::exception& e) {
        // 如果出现异常，输出错误信息
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE; // 返回失败状态码
    }

    return EXIT_SUCCESS; // 正常结束程序
}
