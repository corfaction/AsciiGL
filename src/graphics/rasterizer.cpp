#include "rasterizer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace AsciiGL;

inline float edgeFunction(const vec2& A, const vec2& B, const float& x, const float& y) {
    return (x - A.x)*(B.y - A.y) - (y - A.y)*(B.x - A.x);
}

struct BoundingBox {
    int min_x, min_y, max_x, max_y;
    
    BoundingBox(const vec2& A, const vec2& B, const vec2& C, const float& w, const float& h) {

        // Calculate bounding box

        min_x = (int)((1.0f + std::max(std::min({A.x, B.x, C.x}), -1.0f)) * w * 0.5f);
        max_x = (int)((1.0f + std::min(std::max({A.x, B.x, C.x}),  1.0f)) * w * 0.5f) + 1;
        min_y = (int)((1.0f - std::min(std::max({A.y, B.y, C.y}),  1.0f)) * h * 0.5f);
        max_y = (int)((1.0f - std::max(std::min({A.y, B.y, C.y}), -1.0f)) * h * 0.5f) + 1;

        // Limiting screen sizes

        min_x = std::max((int)min_x, 0);
        max_x = std::min(max_x, (int)w);
        min_y = std::max((int)min_y, 0);
        max_y = std::min(max_y, (int)h);
    }
};

std::vector<Fragment> Rasterizer::makeTriangle(Vertex& v1, Vertex& v2, Vertex& v3, float w, float h) {

    perspectiveDivision(v1);
    perspectiveDivision(v2);
    perspectiveDivision(v3);

    std::vector<Fragment> fragments;

    float step_x = 2.0f / w;
    float step_y = 2.0f / h;

    vec2 A = v1.pos.xy(); 
    vec2 B = v2.pos.xy(); 
    vec2 C = v3.pos.xy();

    float area = (B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y);

    // Checking for a degenerate triangle and a CW triangle
    if(area <= 0) return fragments;

    float inv_area = 1.0f / area;

    BoundingBox box(A, B, C, w, h);

    fragments.reserve(std::abs(box.max_x - box.min_x * box.max_y - box.min_y) / 2);

    for(int y = box.min_y; y < box.max_y; ++y) {
        
        float y_ndc = 1.0f - (y + 0.5f) * step_y;

        float x_start = box.min_x;
        float x_ndc_start = (x_start + 0.5f) * step_x - 1.0f;
        
        // Increments for the edge function
        float e1_dx = (B.y - A.y) * step_x;
        float e2_dx = (C.y - B.y) * step_x;
        float e3_dx = (A.y - C.y) * step_x;
        
        float e1 = edgeFunction(A, B, x_ndc_start, y_ndc);
        float e2 = edgeFunction(B, C, x_ndc_start, y_ndc);
        float e3 = edgeFunction(C, A, x_ndc_start, y_ndc);
        
        for(int x = box.min_x; x < box.max_x; ++x) {

            if(x != box.min_x) {
                e1 += e1_dx; 
                e2 += e2_dx; 
                e3 += e3_dx; 
            }
            
            if(e1 > 0.0f || e2 > 0.0f || e3 > 0.0f) continue;
            
            float alpha = e2 * inv_area;
            float beta  = e3 * inv_area;
            float gamma = 1.0f - alpha - beta;

            // Translate z to ndc coordinates
            float z_ndc = interpolate(alpha, beta, gamma, v1.pos.z, v2.pos.z, v3.pos.z);
            
            float depth = (z_ndc + 1.0f) * 0.5f;
            depth = std::max(0.0f, std::min(1.0f, depth));
            
            int index = y * w + x;

            Fragment frag;

            frag.index = index;

            // checking the buffer to make sure that only objects in front are displayed 
            if(depth >= zbuffer[index]) continue; 
            
            zbuffer[index] = depth;

            // Interpolation
            frag.frag_pos     = interpolate(alpha, beta, gamma, v1.frag_pos, v2.frag_pos, v3.frag_pos);
            frag.vertex_color = interpolate(alpha, beta, gamma, v1.color,    v2.color,    v3.color);
            frag.normal       = interpolate(alpha, beta, gamma, v1.normal,   v2.normal,   v3.normal);

            fragments.push_back(frag);
            
        }
    }
    fragments.shrink_to_fit();
    return fragments;
}

void Rasterizer::perspectiveDivision(Vertex& v) const {
    if(v.clip_pos.w != 0) {
        v.pos.x = v.clip_pos.x / v.clip_pos.w;
        v.pos.y = v.clip_pos.y / v.clip_pos.w;
        v.pos.z = v.clip_pos.z / v.clip_pos.w;
        v.pos.w = 1.0f;
    }
}

void Rasterizer::clearZBuffer(size_t w, size_t h) {
    if(zbuffer) delete[] zbuffer;
    zbuffer = new float[w * h];

    std::fill(zbuffer, zbuffer + w * h, 1.0f);
}

