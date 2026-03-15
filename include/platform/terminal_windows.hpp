#include "../core/terminal.hpp"
#include <windows.h>

namespace AsciiGL {

class Terminal::Impl {
private:

    HANDLE h_console;
    size_t impl_width;
    size_t impl_height;

public:

    Impl();
    void initialize();
    void cleanup();
    void updateSize();
    void getWindowSize(size_t& w, size_t& h) const;
    float getAspectRatio();

};

}
