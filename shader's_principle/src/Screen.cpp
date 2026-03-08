//
// Created by Neuroil on 2026/3/7.
//

#include "../include/Screen.hpp"

const size_t Screen::index(size_t x, size_t y) const {
    return y * width + x;
}

void Screen::display(const Image image) {
}

/*
const bool Screen::setPixel(int x, int y, char c) {
    if (x >= 0 && x < width && y >= 0 && y< height) {
        buffer[index(x, y)] = c;
        return true;
    }
    return false;
}

const char Screen::getPixel(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return buffer[index(x, y)];
    }
    return '\0';
}

void Screen::display() const {
    for (int h = 0; h != height; ++h) {
        for (int w = 0; w != width; ++w) {
            std::cout << buffer[width * h + w];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
*/

void Screen::clean(const char fill) {
    std::fill(buffer.begin(), buffer.end(), fill);
}
