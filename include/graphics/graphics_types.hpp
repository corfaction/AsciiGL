#pragma once
#include "../math/vec.hpp"

namespace AsciiGL {
    struct Vertex {
        vec4 pos;
        vec4 color;
    };

    struct Fragment {
        int screen_x;
        int screen_y;
        vec4 color;
    };
}
