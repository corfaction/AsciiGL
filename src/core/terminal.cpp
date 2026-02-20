#include "../../include/core/terminal.hpp"
#include <iostream>

namespace AsciiGL {

class Terminal::Impl {
public:
    virtual ~Impl() = default;
    virtual void getWindowSize(size_t& width, size_t& height) const = 0;
    virtual float getAspectRatio() = 0;
    virtual void initialize() = 0;
    virtual void cleanup() = 0;
};

Terminal::~Terminal() {
    if (pImpl) {
        std::cout << "\033[" << height << ";0H\n";
        pImpl->cleanup();
    }
}

void Terminal::setChar(size_t x, size_t y, char c) {
    if (!pImpl) return;
    
    if (x >= width || y >= height) return;
    
    if (cursorX == x && cursorY == y) {
        std::cout << c;
        if (++cursorX == width) {
            cursorX = 0;
            ++cursorY;
        }
        return;
    }
    
    std::cout << "\033[" << (y + 1) << ';' << (x + 1) << 'H' << c;
    cursorX = x + 1;
    cursorY = y;
    
    if (cursorX == width) {
        cursorX = 0;
        ++cursorY;
    }
    std::cout.flush();
}

void Terminal::resetCursor() {
    std::cout << "\033[0;0H";
    cursorX = 0;
    cursorY = 0;
}

void Terminal::getWindowSize(size_t& w, size_t& h) const {
    w = width;
    h = height;
}

float Terminal::getAspectRatio() const {
    return pImpl ? pImpl->getAspectRatio() : 1.0f;
}

}
