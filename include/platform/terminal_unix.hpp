#pragma once
#include "../core/terminal.hpp"

namespace AsciiGL {

/**
 * Implementation terminal work for unix-like system
 * - ANSI escape sequences for clean and cursor control
 * - ioctl() for window size retrieval (TIOCGWINSZ)
*/

class TerminalImplUnix : public TerminalImpl {
private:

    size_t impl_width = 80;
    size_t impl_height = 25;

public:

    TerminalImplUnix();
    void getWindowSize(size_t& w, size_t& h) const override;
    float getAspectRatio() const override { return 0.5f; }
    void initialize() override;
    void cleanup() override;
    void updateSize() override;
};

} // AsciiGL
