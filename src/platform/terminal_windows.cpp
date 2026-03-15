#include "../../include/platform/terminal_windows.hpp"
#include "../../include/core/terminal.hpp"
#include <windows.h>

using namespace AsciiGL;

Terminal::Impl::Impl() : impl_width(80), impl_height(25) {
    h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    initialize();
    updateSize();
}
    
void Terminal::Impl::initialize() {
    DWORD mode = 0;
    GetConsoleMode(h_console, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(h_console, mode);
    
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(h_console, &cursor_info);
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(h_console, &cursor_info);
}
    
void Terminal::Impl::cleanup() {
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(h_console, &cursor_info);
    cursor_info.bVisible = true;
    SetConsoleCursorInfo(h_console, &cursor_info);
}

void Terminal::Impl::updateSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h_console, &csbi);
    impl_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    impl_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Terminal::Impl::getWindowSize(size_t& w, size_t& h) const {
    w = impl_width;
    h = impl_height;
}

float Terminal::Impl::getAspectRatio() {
    CONSOLE_FONT_INFOEX info{};
    info.cbSize = sizeof(info);
    GetCurrentConsoleFontEx(h_console, FALSE, &info);
    return static_cast<float>(info.dwFontSize.Y) / 
           static_cast<float>(info.dwFontSize.X);
}

Terminal::Terminal() : pImpl(std::make_unique<Impl>()) {
    size_t w, h;
    pImpl->getWindowSize(w, h);
    width = w;
    height = h;
    cursor_x = 0;
    cursor_y = 0;
}
