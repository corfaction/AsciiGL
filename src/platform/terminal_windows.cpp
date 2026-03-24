#include "../../include/platform/terminal_windows.hpp"
#include <windows.h>
#include <iostream>
#include <memory>

using namespace AsciiGL;

TerminalImplWindows::TerminalImplWindows() {
    h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    initialize();
    updateSize();
}

void TerminalImplWindows::initialize() {
    DWORD mode = 0;
    GetConsoleMode(h_console, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(h_console, mode);

    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(h_console, &cursor_info);
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(h_console, &cursor_info);
}

void TerminalImplWindows::cleanup() {
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(h_console, &cursor_info);
    cursor_info.bVisible = true;
    SetConsoleCursorInfo(h_console, &cursor_info);
}

void TerminalImplWindows::updateSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h_console, &csbi);
    impl_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    impl_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void TerminalImplWindows::getWindowSize(size_t& w, size_t& h) const  {
    w = impl_width;
    h = impl_height;
}

Terminal::Terminal() : pImpl(std::make_unique<TerminalImplWindows>()) {
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
