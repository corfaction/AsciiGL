#include "terminal_unix.hpp"
#include "../../include/AsciiGL/core/terminal.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

using namespace AsciiGL;

TerminalImplUnix::TerminalImplUnix() : impl_width(80), impl_height(25) {
    initialize();
    updateSize();
}
    
void TerminalImplUnix::initialize() {
    std::cout << "\033[?25l";
    std::cout.flush();
}
    
void TerminalImplUnix::cleanup() {
    std::cout << "\033[?25h";
    std::cout.flush();
}
    
void TerminalImplUnix::updateSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    impl_width = w.ws_col;
    impl_height = w.ws_row;
}
    
void TerminalImplUnix::getWindowSize(size_t& w, size_t& h) const {
    w = impl_width;
    h = impl_height;
}

Terminal::Terminal() : pImpl(std::make_unique<TerminalImplUnix>()) {
    size_t w, h;
    pImpl->getWindowSize(w, h);
    width = w;
    height = h;
    cursor_x = 0;
    cursor_y = 0;
    for(size_t i = 0; i < height; i++) {
        std::cout << std::endl;
    }
}
