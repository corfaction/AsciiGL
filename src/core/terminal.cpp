#include "../../include/core/terminal.hpp"
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #include "../platform/terminal_windows.cpp"

#elif defined(__linux__) || defined(__APPLE__)
    #include "../platform/terminal_linux.cpp"

#endif


Terminal::Terminal() : pImpl(nullptr) {
    #if defined(_WIN32) || defined(_WIN64)
        //pImpl = new TerminalWindows::Impl();
        pImpl = new Impl();
        pImpl->getWindowSize(width, height);
        cursorX = 0; cursorY = 0;

    #elif defined(__linux__) || defined(__APPLE__)
        //pImpl = new TerminalLinux::Impl();
        pImpl = new Impl();
        pImpl->getWindowSize(width, height);
        cursorX = 0; cursorY = 0;

    #endif
}

using namespace AsciiGL;

void Terminal::setChar(size_t x, size_t y, char c) { 
    if(cursorX == x && cursorY == y) {
        std::cout << c;
        if(++cursorX == width) {
            cursorX = 0; ++cursorY;
        }
        return;
    }
    std::cout << "\033[" + std::to_string(y + 1) + ';' + std::to_string(x + 1) + 'H' + c;
    cursorX = x + 1; cursorY = y;

    if(cursorX == width) {
        cursorX = 0;
        ++cursorY;
    }

}

void Terminal::resetCursor() {
    std::cout << "\033[0;0H";
}

void Terminal::getWindowSize(size_t& w, size_t& h) const {
    w = width; h = height;
}

float Terminal::getAspectRatio() const {
    return pImpl->getAspectRatio();
}

Terminal::~Terminal() {
    delete pImpl;
    std::cout << "\033[" + std::to_string(height) + ';' + std::to_string(width) + 'H';
}
