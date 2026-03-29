#include "rasterizer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace AsciiGL;

std::vector<Fragment> Rasterizer::makeTriangle(Vertex& v1, Vertex& v2, Vertex& v3, float w, float h) {

    perspectiveDivision(v1);
    perspectiveDivision(v2);
    perspectiveDivision(v3);

    std::vector<Fragment> fragments;

    float step_x = 2.0f / w;
    float step_y = 2.0f / h;

    float& x1 = v1.pos.x; float& y1 = v1.pos.y;
    float& x2 = v2.pos.x; float& y2 = v2.pos.y;
    float& x3 = v3.pos.x; float& y3 = v3.pos.y;    

    float area = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);

    // Checking for a degenerate triangle

    if(area == 0) return fragments;

    float inv_area = 1.0f / area;

    // Bounding box

    float min_x_ndc = std::max(std::min({x1, x2, x3}), -1.0f);
    float max_x_ndc = std::min(std::max({x1, x2, x3}),  1.0f);
    float min_y_ndc = std::max(std::min({y1, y2, y3}), -1.0f);
    float max_y_ndc = std::min(std::max({y1, y2, y3}),  1.0f);

    // Translate bounding box from float to integer

    int min_x = (int)((1.0f + min_x_ndc) * w * 0.5f);
    int max_x = (int)((1.0f + max_x_ndc) * w * 0.5f) + 1;
    int min_y = (int)((1.0f - max_y_ndc) * h * 0.5f);
    int max_y = (int)((1.0f - min_y_ndc) * h * 0.5f) + 1;

    // Limiting screen sizes

    min_x = std::max((int)min_x, 0);
    max_x = std::min(max_x, (int)w);
    min_y = std::max((int)min_y, 0);
    max_y = std::min(max_y, (int)h);

    for(int y = min_y; y < max_y; ++y) {
        
        float y_ndc = 1.0f - (y + 0.5f) * 2.0f / h;
        
        for(int x = min_x; x < max_x; ++x) {
            
            float x_ndc = (x + 0.5f) * 2.0f / w - 1.0f;

            // Edge function
            
            float e1 = (x_ndc - x1)*(y2 - y1) - (y_ndc - y1)*(x2 - x1);
            float e2 = (x_ndc - x2)*(y3 - y2) - (y_ndc - y2)*(x3 - x2);
            float e3 = (x_ndc - x3)*(y1 - y3) - (y_ndc - y3)*(x1 - x3);
            
            if(e1 <= 0.0f && e2 <= 0.0f && e3 <= 0.0f) {
                
                Fragment frag;

                frag.screen_pos.x = x;
                frag.screen_pos.y = y;
                
                float alpha = e2 * inv_area;
                float beta  = e3 * inv_area;
                float gamma = 1.0f - alpha - beta; // Because alpha + beta + gamma = 1 

                // Translate z to ndc coordinates
                
                float z_ndc = v1.pos.z * alpha + v2.pos.z * beta + v3.pos.z * gamma;

                float depth = (z_ndc + 1.0f) * 0.5f;
                depth = std::max(0.0f, std::min(1.0f, depth));
                
                int index = y * w + x;

                // checking the buffer to make sure that only objects in front are displayed 
                
                if(depth < zbuffer[index]) {
                    zbuffer[index] = depth;

                    // Interpolation
                    
                    frag.frag_pos     
                        = interpolate(alpha, beta, gamma, v1.frag_pos, v2.frag_pos, v3.frag_pos);
                    frag.vertex_color 
                        = interpolate(alpha, beta, gamma, v1.color,    v2.color,    v3.color);
                    frag.normal       
                        = interpolate(alpha, beta, gamma, v1.normal,   v2.normal,   v3.normal);

                    fragments.push_back(frag);
                }
            }
        }
    }
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

