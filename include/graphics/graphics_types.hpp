#pragma once
#include "../math/vec.hpp"
#include "../math/color.hpp"

namespace AsciiGL {
    struct Vertex {
        vec4 pos;
        vec4 color;
    };

    struct Fragment {
        ivec2 screen_pos;
        vec4 vertex_color;
        Color color;
    };
}
