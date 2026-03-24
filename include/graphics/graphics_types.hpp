#pragma once
#include "../math/vec.hpp"
#include "../math/color.hpp"

namespace AsciiGL {
    
struct Vertex {
    vec4 pos;
    vec3 frag_pos;
    vec4 clip_pos;

    vec4 color;
    vec3 normal;
};

struct Fragment {
    ivec2 screen_pos;
    vec3 frag_pos;

    vec4 vertex_color;
    Color color;
    vec3 normal;
};

}
