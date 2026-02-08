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

    #elif defined(__linux__) || defined(__APPLE__)
        //pImpl = new TerminalLinux::Impl();
        pImpl = new Impl();

    #endif
}

void Terminal::getWindowSize(size_t& width, size_t& height) const {
    pImpl->getWindowSize(width, height);
}

float Terminal::getAspectRatio() const {
    return pImpl->getAspectRatio();
}

void Terminal::setChar(size_t x, size_t y, char c) {
    pImpl->setChar(x, y, c);
}

void Terminal::flushBuffer() {
    pImpl->flushBuffer();
}

Terminal::~Terminal() {
    delete pImpl;
}
