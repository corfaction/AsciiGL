#pragma once
#include "../../include/AsciiGL/core/terminal.hpp"
#include <windows.h>

namespace AsciiGL {

/**
 * Implementation terminal work for windows
 * - ANSI escape sequences for cursor control
 * - CONSOLE_SCREEN_BUFFER_INFO for window size retrieval
*/

class TerminalImplWindows : public TerminalImpl {
private:

    HANDLE h_console;
    size_t impl_width = 80;
    size_t impl_height = 25;

    float getAspectRatioAlternative() const;

public:

    TerminalImplWindows();
    void getWindowSize(size_t& w, size_t& h) const override;
    float getAspectRatio() const override { return 0.5f; };
    void initialize() override;
    void cleanup() override;
    void updateSize() override;
};

} // AsciiGL