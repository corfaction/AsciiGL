#pragma once
#include "../../include/AsciiGL/graphics/graphics_types.hpp"
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

    void perspectiveDivision(Vertex& v) const;

    template<typename T>
    T interpolate(float alpha, float beta, float gamma, T& v1, T& v2, T& v3) const {
        return v1 * alpha + v2 * beta + v3 * gamma;
    }
    
public:

    std::vector<Fragment> makeTriangle(Vertex& v1, Vertex& v2, Vertex& v3, float w, float h);
    void clearZBuffer(size_t w, size_t h);

    ~Rasterizer() { delete[] zbuffer; zbuffer = nullptr; }
};

} // AsciiGL
