#include "../../include/platform/terminal_unix.hpp"
#include "../../include/core/terminal.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

using namespace AsciiGL;

Terminal::Impl::Impl() : impl_width(80), impl_height(25) {
    initialize();
    updateSize();
}
    
void Terminal::Impl::initialize() {
    std::cout << "\033[?25l";
    std::cout.flush();
}
    
void Terminal::Impl::cleanup() {
    std::cout << "\033[?25h";
    std::cout.flush();
}
    
void Terminal::Impl::updateSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    impl_width = w.ws_col;
    impl_height = w.ws_row;
}
    
void Terminal::Impl::getWindowSize(size_t& w, size_t& h) const {
    w = impl_width;
    h = impl_height;
}

Terminal::Terminal() : pImpl(std::make_unique<Impl>()) {
    size_t w, h;
    pImpl->getWindowSize(w, h);
    width = w;
    height = h;
    cursor_x = 0;
    cursor_y = 0;
}
