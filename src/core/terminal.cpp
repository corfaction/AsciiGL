#include "../../include/AsciiGL/core/terminal.hpp"
#include <stdexcept>
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
        
        int x = change.index % width;
        int y = change.index / width;

        if (cursor_x == x && cursor_y == y) {
            std::cout << change.c; 
            if (++cursor_x == width) {
                cursor_x = 0; ++cursor_y; 
            }
            return; 
        }

        std::cout << "\033[" << (y + 1) << ';' << (x + 1) << 'H' << change.c;
        
        if (++cursor_x == width) {
            cursor_x = 0; ++cursor_y;
        }
    }
    std::cout.flush();
    resetCursor();
}

bool Terminal::updateSize() {
    if(!pImpl) throw std::logic_error("Pimpl is null in Terminal: invariant violation");
    
    pImpl->updateSize();

    size_t width_clone = width;
    size_t height_clone = height;

    pImpl->getWindowSize(width, height);

    if(width != width_clone || height != height_clone) {
        resetCursor();
        
        std::cout << "\033[2J";
        std::cout << "\033[H";
        
        std::cout.flush();
    }

    resetCursor();
    std::cout.flush();

    return width != width_clone || height != height_clone; 
}

} // AsciiGL