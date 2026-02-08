#include "../../include/core/terminal.hpp"
#include <windows.h>

class Terminal::Impl {
public:
    void getWindowSize(size_t& width, size_t& height) const {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        
    }

    float getAspectRatio() const {
        CONSOLE_FONT_INFOEX info{};
        info.cbSize = sizeof(info);

        getCurrentConsoleFontEx(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FALSE,
            &info
        );
    }

    return static_cast<float>(info.dwFontSize.Y) / static_cast<float>(info.dwFontSize.X);
};
