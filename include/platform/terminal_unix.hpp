#include "../core/terminal.hpp"

namespace AsciiGL {

class Terminal::Impl {
private:

    size_t impl_width;
    size_t impl_height;

public:

    Impl();
    void initialize();
    void cleanup();
    void updateSize();
    void getWindowSize(size_t& w, size_t& h) const;
    float getAspectRatio() { return 2.0f; }
};

}
