#include "../../include/AsciiGL/core/terminal.hpp"
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

void Terminal::present(ScreenBuffer& screen_buffer) {
    std::vector<ChangedSymbol> changes = screen_buffer.getChangesOnly();

    for(auto& change : changes) {
        if (cursor_x == change.x && cursor_y == change.y) {
            std::cout << change.c; 
            if (++cursor_x == width) {
                cursor_x = 0; ++cursor_y; 
            }
            return; 
        }

        std::cout << "\033[" << (change.y + 1) << ';' << (change.x + 1) << 'H' << change.c;
        
        if (cursor_x == width) {
            cursor_x = 0; ++cursor_y;
        }
    }
    std::cout.flush();
    resetCursor();
}

bool Terminal::updateSize() {
    if(pImpl) {
        pImpl->updateSize();

        size_t width_clone = width;
        size_t height_clone = height;

        pImpl->getWindowSize(width, height);

        if(width != width_clone || height != height_clone) {

            resetCursor();

            std::cout << "\033[J";

            for(int i = 0; i < height; i++) {
                std::cout << std::endl;
            }

        }

        resetCursor();

        return width != width_clone || height != height_clone; 
    }
}

} // AsciiGL