#include "../../include/core/terminal.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

using namespace AsciiGL;

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

};
