#pragma once

#include "vk_test.hpp"
#include <array>
#include <glm/glm.hpp>


// 顶点着色器通信
struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

extern const std::vector<Vertex> vertices;