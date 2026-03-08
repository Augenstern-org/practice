#include <iostream>
#include <GLFW/glfw3.h>

#include "../include/Screen.hpp"

#define MAX_IN_FLIGHT = 2;
const int WIDTH = 800;
const int HEIGHT = 600;

void draw(FrameBuffers frame_buffers);





int main() {

    auto screen = Screen(WIDTH, HEIGHT);
    screen.frame_buffers = FrameBuffers(WIDTH, HEIGHT);
    if (!screen.get_windows_status()) {
        std::cout << "failed to creat window!" << std::endl;
        return -1;
    }


    // 主循环
    while (!glfwWindowShouldClose(screen.get_window_handle())) {
        draw(screen.frame_buffers);

        screen.present();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void draw(FrameBuffers frame_buffers) {
    // 每一帧渲染逻辑的最开始执行
    std::fill(frame_buffers.data.begin(), frame_buffers.data.end(), Color{0.0f, 0.0f, 0.0f});
}
