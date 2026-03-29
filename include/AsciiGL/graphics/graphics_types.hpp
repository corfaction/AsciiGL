#pragma once
#include "../math/vec.hpp"
#include "../math/color.hpp"

namespace AsciiGL {

using namespace Math;

// Vertex is data structure with interpolatable attributes
    
struct Vertex {
    vec4 pos;       // installs a rasterizer = clip_pos / clip_pos.w  
    vec4 clip_pos;  // position before perspective division
    vec3 frag_pos;  // position without using view and projection matrices

    vec4 color;
    vec3 normal;
};

// Fragment data structure containing interpolated attributes

struct Fragment {
    ivec2 screen_pos;   // a specific position in the buffer
    vec3 frag_pos;

    vec4 vertex_color;  // interpolated color
    Color color;        // final color
    vec3 normal;
};

} // AscciiGL