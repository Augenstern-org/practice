//
// Created by Neuroil on 2026/3/9.
//

#ifndef SHADER_S_PRINCIPLE_DATA_HPP
#define SHADER_S_PRINCIPLE_DATA_HPP

#include <glm/glm.hpp>
#include <vector>

enum VertexShaderBindingDescription {
    VS_TRIPLE
};

struct Color {
    Color() {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }
    Color(const float _r, const float _g, const float _b) : r(_r), g(_g), b(_b){}
    float r, g, b;
};

struct Vertex {
    Vertex() = default;
    Vertex(const float x, const float y, const float z) : pos(x, y, z){}
    Vertex(const float x, const float y, const float z,
           const float r, const float g, const float b) :
    pos(x, y, z), color(r, g, b){}
    glm::vec3 pos;
    Color color;

    static VertexShaderBindingDescription binding_description();
};

class Texture {
public:
    int width, height;
    std::vector<Color> pixels;

    Texture(int w, int h) : width(w), height(h), pixels(w * h) {}

    // 输入 UV 坐标 (0.0~1.0)，返回颜色
    Color sample(float u, float v);
};

struct UBO {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct VertInSoA {
    std::vector<double> x_pos;
    std::vector<double> y_pos;
    std::vector<float> r;
    std::vector<float> g;
    std::vector<float> b;
};

struct VertOut {
    glm::vec4 pos;
    glm::vec3 color;
};

struct RasterizerIn : public VertOut{};

struct RasterizerOut {
    RasterizerOut(const int w, const int h) {
        r.resize(w * h * 4);
        g.resize(w * h * 4);
        b.resize(w * h * 4);
    }
    RasterizerOut() = default;
    ~RasterizerOut() = default;

    std::vector<float> r;
    std::vector<float> g;
    std::vector<float> b;
};

struct FragBuffer : public RasterizerOut {
    using RasterizerOut::RasterizerOut;
};

struct FrameBuffer : public FragBuffer {
    using FragBuffer::FragBuffer;
};


#endif //SHADER_S_PRINCIPLE_DATA_HPP