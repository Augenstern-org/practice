//
// Created by Neuroil on 2026/3/8.
//

#ifndef SHADER_S_PRINCIPLE_BUFFERS_HPP
#define SHADER_S_PRINCIPLE_BUFFERS_HPP

#include <vector>
#include "Texture.hpp"

class FrameBuffers {
public:
    int width, height;
    std::vector<Color> data;

    FrameBuffers(int w = 800, int h = 600) : width(w), height(h) {
        data.resize(w * h * sizeof(Color));
    }

    // 操作接口：把 (x, y) 映射到一维向量索引
    void setPixel(int x, int y, const Color& color) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            data[y * width + x] = color;
        }
    }
};

// class commandBuffers {
// public:
//     std::vector<command> cmdBuffer;
// };


#endif //SHADER_S_PRINCIPLE_BUFFERS_HPP