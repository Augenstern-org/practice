#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

// 主函数封装
class app {
public:
   void run();


private:
    // 窗口结构体
    struct windowCreateInfo{
        const int width = 800;
        const int height = 600;
        const char* title = "OpenGL first try";
    };

    GLFWwindow* window;
    

private:

    // 成员函数

    void initApp();
    void createWindow();
    void initShader();
    void mainLoop();
    void cleanup();

private:

    // 渲染一个三角形


    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    unsigned int VBO, VAO, EBO;

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

