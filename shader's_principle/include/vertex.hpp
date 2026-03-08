//
// Created by Neuroil on 2026/3/7.
//

#ifndef SHADER_S_PRINCIPLE_VERTEX_HPP
#define SHADER_S_PRINCIPLE_VERTEX_HPP

/*
 * Vertex 对象存储了该顶点的坐标
 */

#include <vector>

class Vertex {
public:
    // 用向量初始化顶点
    explicit Vertex(const std::vector<int>& init_pos) : pos(init_pos){}
    // 用数组初始化顶点
    template<size_t len>
    explicit Vertex(const int (&init_array)[len]) : pos(init_array, init_array + len){}
    ~Vertex() =default;

    // 获取顶点坐标
    const std::vector<int>* get_pos() const;

private:
    const std::vector<int> pos;
};

#endif //SHADER_S_PRINCIPLE_VERTEX_HPP