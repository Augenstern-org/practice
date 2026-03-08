//
// Created by Neuroil on 2026/3/7.
//

#ifndef SHADER_S_PRINCIPLE_VERTEX_HPP
#define SHADER_S_PRINCIPLE_VERTEX_HPP

/*
 * Vertex 对象存储了该顶点的坐标、颜色
 */

#include <vector>
#include <glm/glm.hpp>

struct Color {
    float r, g, b;
};

struct Vertex {
    glm::vec3 pos;
    Color color;
};

#endif //SHADER_S_PRINCIPLE_VERTEX_HPP