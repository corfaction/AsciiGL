#include "../../include/core/terminal.hpp"
#include <memory>
#include <iostream>

namespace AsciiGL {

Terminal::~Terminal() {
    if (pImpl) {
        std::cout << "\033[" << height << ";0H\n";
        pImpl->cleanup();
    }
}

float Terminal::getAspectRatio() const {
    return pImpl ? pImpl->getAspectRatio() : 1.0f;
}

void Terminal::getWindowSize(size_t& w, size_t& h) const {
    w = width;
    h = height;
}

void Terminal::resetCursor() {
    std::cout << "\033[0;0H";
    cursor_x = 0;
    cursor_y = 0;
}

void Terminal::setChar(size_t x, size_t y, char c) {

    if (!pImpl) return;
    if (x >= width || y >= height) return;

    if (cursor_x == x && cursor_y == y) {
        std::cout << c; 
        if (++cursor_x == width) {
             cursor_x = 0; ++cursor_y; 
        }
        return; 
    }

    std::cout << "\033[" << (y + 1) << ';' << (x + 1) << 'H' << c;

    cursor_x = x + 1; cursor_y = y;

    if (cursor_x == width) {
         cursor_x = 0; ++cursor_y;
    }

    std::cout.flush();

}

}