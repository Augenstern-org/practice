//
// Created by Neuroil on 2026/3/7.
//

#ifndef SHADER_S_PRINCIPLE_IMAGE_HPP
#define SHADER_S_PRINCIPLE_IMAGE_HPP

#include "vertex.hpp"

class Texture {
public:
    int width, height;
    std::vector<Color> pixels;

    Texture(int w, int h) : width(w), height(h), pixels(w * h) {}

    // 输入 UV 坐标 (0.0~1.0)，返回颜色
    Color sample(float u, float v);
};


#endif //SHADER_S_PRINCIPLE_IMAGE_HPP