#include "../../include/core/terminal.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

namespace AsciiGL {

class Terminal::Impl {
private:
    size_t implWidth;
    size_t implHeight;

public:
    Impl() : implWidth(80), implHeight(25) {
        initialize();
        updateSize();
    }
    
    void initialize() {
        std::cout << "\033[?25l";
        std::cout.flush();
    }
    
    void cleanup() {
        std::cout << "\033[?25h";
        std::cout.flush();
    }
    
    void updateSize() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        implWidth = w.ws_col;
        implHeight = w.ws_row;
    }
    
    void getWindowSize(size_t& w, size_t& h) const {
        w = implWidth;
        h = implHeight;
    }
    
    float getAspectRatio() {
        return 2.0f;
    }
};

Terminal::Terminal() : pImpl(std::make_unique<Impl>()) {
    size_t w, h;
    pImpl->getWindowSize(w, h);
    width = w;
    height = h;
    cursorX = 0;
    cursorY = 0;
}

}
