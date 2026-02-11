#include "../../include/core/terminal.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

class Terminal::Impl {
public:
    void getWindowSize(size_t& width, size_t& height) const {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        width = w.ws_col;
        height = w.ws_row;
    }

    float getAspectRatio() const {
        return 2.0f;
    }

    void setChar(size_t x, size_t y, char c) {

        std::string output;
    
        output += "\033[";
        output += std::to_string(y + 1);
        output += ';';
        output += std::to_string(x + 1);
        output += 'H';
        output += c;
            
        std::cout << "\033[" + std::to_string(y + 1) + ';' + std::to_string(x + 1) + 'H' + c;
    }

    void flushBuffer() {
        std::cout << "\033[1;1H";
        std::cout.flush();
        fsync(1);
    }
};
