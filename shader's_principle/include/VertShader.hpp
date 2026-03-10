//
// Created by Neuroil on 2026/3/7.
//

#ifndef SHADER_S_PRINCIPLE_VERTSHADER_HPP
#define SHADER_S_PRINCIPLE_VERTSHADER_HPP

#include <glm/glm.hpp>
#include "Data.hpp"

struct SimpleShader {
    // 顶点着色器：纯计算逻辑
    static VertOut vertex_shader(const VertInSoA& in, const UBO& uni) {
        VertOut out;
        out.pos = uni.model
        out.uv = in.uv;
        return out;
    }

    // 片元着色器
    static glm::vec3 fragment_shader(const VertOut& interpolated, const Texture& tex) {
        return tex.sample(interpolated.uv);
    }
};


#endif //SHADER_S_PRINCIPLE_VERTSHADER_HPP