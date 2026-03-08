//
// Created by Neuroil on 2026/3/7.
//

#ifndef SHADER_S_PRINCIPLE_SCREEN_HPP
#define SHADER_S_PRINCIPLE_SCREEN_HPP

#include <vector>
#include <iostream>
#include "Image.hpp"

class Screen {
public:
    Screen(int w, int h, const char fill = ' ') : width(w), height(h), buffer(w * h, fill){}
    ~Screen() =default;

    const size_t index(size_t x, size_t y) const;
    // const bool setPixel(int x, int y, char c);
    // const char getPixel(int x, int y) const;
    // void display() const;
    void display(const Image image);
    void clean(char fill = ' ');

private:
    size_t width;           size_t height;
    std::vector<char> buffer;

};

#endif //SHADER_S_PRINCIPLE_SCREEN_HPP