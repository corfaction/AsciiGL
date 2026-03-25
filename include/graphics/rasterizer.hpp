#pragma once
#include "graphics_types.hpp"
#include <vector>

namespace AsciiGL {

/** 
 * The Rasterizer takes primitives (triangles) defined by vertices and:
 * - Generates all fragments (pixels) covered by the primitive
 * - Interpolates vertex attributes across the primitive surface
 * - Performs clipping against screen boundaries
 * - Produces fragments for the fragment shader to process
*/

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

} // AsciiGL
