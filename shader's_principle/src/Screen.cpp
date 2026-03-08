//
// Created by Neuroil on 2026/3/7.
//

#include "../include/Screen.hpp"

    FrameBuffers Screen::frame_buffers;

void Screen::present(FrameBuffers fb) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 2. vector 数据传给显卡
    // 这里的 GL_RGB 和 GL_FLOAT 必须对应的 Color 结构体
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
        0, GL_RGB, GL_FLOAT, frame_buffers.data.data());

    // 3. 把画贴在窗口上
    // 画一个正方形铺满整个窗口，把你的渲染结果当成贴图贴上去
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f); // 左下
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f, -1.0f); // 右下
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f,  1.0f); // 右上
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f,  1.0f); // 左上
    glEnd();

    // 4. 双缓冲交换：把画好的缓冲区推向显示器
    glfwSwapBuffers(this->window_handle);

    // 5. 响应窗口事件（如关闭、点击）
    glfwPollEvents();
}

const bool Screen::get_windows_status() const {
    return windows_status;
}

GLFWwindow * Screen::get_window_handle() const {
    return window_handle;
}
