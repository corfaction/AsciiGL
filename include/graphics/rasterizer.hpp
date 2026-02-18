#pragma once
#include "graphics_types.hpp"
#include <vector>

namespace AsciiGL {

class Rasterizer{
private:
    float width, height;
public:

    Rasterizer(float w, float h) : width(w), height(h) {}

    std::vector<Fragment> makeTriangle(std::vector<Vertex>& v);
};

}
