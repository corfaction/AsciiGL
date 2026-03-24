#pragma once
#include "graphics_types.hpp"
#include <vector>

namespace AsciiGL {

class Rasterizer{
private:

    float* zbuffer = nullptr;

    void perspectiveDivision(std::vector<Vertex>& v) const;
    void updateSize(float w, float h);
    
public:

    std::vector<Fragment> makeTriangle(std::vector<Vertex>& v, float w, float h);
    void clearZBuffer(size_t w, size_t h);

    ~Rasterizer() { delete[] zbuffer; zbuffer = nullptr; }
};

}
