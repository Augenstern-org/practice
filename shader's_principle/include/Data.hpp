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



enum class DescriptorType {
    UNIFORM_BUFFER,    // 常量缓冲区 (MVP 矩阵等)
    STORAGE_BUFFER,    // 结构化缓冲区 (大量顶点/实例数据)
    COMBINED_IMAGE_SAMPLER, // 纹理 + 采样器
    INPUT_ATTACHMENT   // 帧缓存输入
};

struct DescriptorSetLayoutBinding {
    uint32_t binding;           // 对应 Shader 中的 layout(binding = N)
    DescriptorType descriptorType;
    uint32_t descriptorCount;   // 支持数组（例如：Texture2D textures[4]）
    uint32_t stageFlags;        // 哪些阶段可见（顶点/像素）
};

struct DescriptorSetLayout {
    // 使用动态数组或固定大小数组存放绑定规则
    std::vector<DescriptorSetLayoutBinding> bindings;

    // 预计算总大小，方便管线直接分配内存
    uint32_t totalSizeInBytes;
};

struct DescriptorPoolSize {
    DescriptorType type;
    uint32_t descriptorCount;
};

struct DescriptorSet {
    void** basePtr; // 指向池中分配给它的起始地址
    const DescriptorSetLayout* layout;

    // 把真正的 Buffer 指针塞进池子里
    void UpdateBinding(uint32_t binding, void* resourcePtr) {
        // 通过 Layout 查到对应的偏移量，然后写入
        // 假设 Layout 里 binding 是连续的
        basePtr[binding] = resourcePtr;
    }
};

class DescriptorPool {
private:
    // 模拟描述符，存一堆指针或句柄
    std::vector<void*> poolData;
    uint32_t nextFreeSlot = 0;

public:
    // 初始化时直接分配一大块，避免管线运行中途申请内存
    DescriptorPool(uint32_t maxSets, const std::vector<DescriptorPoolSize>& sizes) {
        uint32_t totalCount = 0;
        for (auto& s : sizes) totalCount += s.descriptorCount;
        poolData.resize(totalCount, nullptr);
    }

    bool AllocateDescriptorSet(const DescriptorSetLayout& layout, DescriptorSet& outSet) {
        // 内存分配器
        // 根据 Layout 的需求，从 poolData 中切出一块给 DescriptorSet
        uint32_t required = layout.bindings.size();
        if (nextFreeSlot + required > poolData.size()) return false;

        outSet.basePtr = &poolData[nextFreeSlot];
        nextFreeSlot += required;
        return true;
    }

    void Reset() {
        nextFreeSlot = 0; // 每一帧结束直接重置指针
    }
};

struct VertShaderLayout {

};

struct VertShaderCreateInfo {
    // 从 Layout 中读取数据布局
    // shader 需要知晓从哪里读取数据（传入指针）
    // 总共三个指针，最多四个（第四个是 DescriptorSet*）
    // UBO 指针指向所需的 mvp 矩阵
    // VertIn 指针指向需要计算的顶点
    // VertOut 指针指向 VS_Post 缓冲区
};

#endif //SHADER_S_PRINCIPLE_DATA_HPP