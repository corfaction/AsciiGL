#include "../../include/core/terminal.hpp"
#include <windows.h>

namespace AsciiGL {

class Terminal::Impl {
private:
    HANDLE hConsole;
    size_t implWidth;
    size_t implHeight;

public:
    Impl() : implWidth(80), implHeight(25) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        initialize();
        updateSize();
    }
    
    void initialize() {
        DWORD mode = 0;
        GetConsoleMode(hConsole, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, mode);
        
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
    
    void cleanup() {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = true;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
    
    void updateSize() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        implWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        implHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    
    void getWindowSize(size_t& w, size_t& h) const {
        w = implWidth;
        h = implHeight;
    }
    
    float getAspectRatio() {
        CONSOLE_FONT_INFOEX info{};
        info.cbSize = sizeof(info);
        GetCurrentConsoleFontEx(hConsole, FALSE, &info);
        return static_cast<float>(info.dwFontSize.Y) / 
               static_cast<float>(info.dwFontSize.X);
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
