//
// Created by Neuroil on 2026/3/7.
//

#ifndef SHADER_S_PRINCIPLE_VERTSHADER_HPP
#define SHADER_S_PRINCIPLE_VERTSHADER_HPP

#include <glm/glm.hpp>
#include "Data.hpp"

class Shader {

};

class VertShader {
    VertShader(VertexShaderBindingDescription createInfo) {
        // 从 Layout 中读取数据布局
        // shader 需要知晓从哪里读取数据（传入指针）
        // 总共三个指针，最多四个（第四个是 DescriptorSet*）
        // UBO 指针指向所需的 mvp 矩阵
        // VertIn 指针指向需要计算的顶点
        // VertOut 指针指向 VS_Post 缓冲区
    }
    // 计算逻辑
    static VertOut vertex_shader(/* 这里需要重新设计参数 */) {
        // 遍历计算每一个顶点缓冲区的顶点
    }

};


#endif //SHADER_S_PRINCIPLE_VERTSHADER_HPP