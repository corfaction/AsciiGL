#pragma once
#include "graphics_types.hpp"
#include <vector>

namespace AsciiGL {

class Rasterizer{
private:

    float width, height;
    int screen_size;
    float* zbuffer;
    
public:

    Rasterizer(const float w, const float h);

    std::vector<Fragment> makeTriangle(std::vector<Vertex>& v);
    void clearZBuffer();
    std::vector<Vertex> perspectiveDivision(std::vector<Vertex>& v) const;

    ~Rasterizer() { delete[] zbuffer; zbuffer = nullptr; }
};

}
