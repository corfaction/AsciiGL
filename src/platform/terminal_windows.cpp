#include "../../include/core/terminal.hpp"
#include <windows.h>

class Terminal::Impl {
private:
    HANDLE hConsole;
public:

    Impl() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hConsole, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, mode);
    }

    void getWindowSize(size_t& width, size_t& height) const {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; 
    }

    float getAspectRatio() const {
        CONSOLE_FONT_INFOEX info{};
        info.cbSize = sizeof(info);

        GetCurrentConsoleFontEx(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FALSE,
            &info
        );
        return static_cast<float>(info.dwFontSize.Y) / static_cast<float>(info.dwFontSize.X);
    }

    void setChar(size_t x, size_t y, char c) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord;
        coord.X = x;
        coord.Y = y; 

        std::cout << "\033[" + std::to_string(y + 1) + ';' + std::to_string(x + 1) + 'H' + c;
    }

    void flushBuffer() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, {0, 0});
    }
};
