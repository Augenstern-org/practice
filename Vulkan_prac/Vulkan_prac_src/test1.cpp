// main.cpp
#include "vk_test.hpp"
#include "shader.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
