#include "../../include/graphics/rasterizer.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

using namespace AsciiGL;

std::vector<Fragment> Rasterizer::makeTriangle(std::vector<Vertex>& v) {

    if (v.size() != 3)
        throw std::out_of_range("vertices size != 3");

    std::vector<Fragment> fragments;

    float stepX = 2.0f / width;
    float stepY = 2.0f / height;

    float& x1 = v[0].pos.x; float& y1 = v[0].pos.y;
    float& x2 = v[1].pos.x; float& y2 = v[1].pos.y;
    float& x3 = v[2].pos.x; float& y3 = v[2].pos.y;

    float inv_area = 1.0f / ((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1));

    // Bounding Box

    float minX = std::max(std::min({x1, x2, x3}), -1.0f);
    float maxX = std::min(std::max({x1, x2, x3}),  1.0f);
    float minY = std::max(std::min({y1, y2, y3}), -1.0f);
    float maxY = std::min(std::max({y1, y2, y3}),  1.0f);

    float E1_row = (minX - x1)*(y2 - y1) - (minY - y1)*(x2 - x1);
    float E2_row = (minX - x2)*(y3 - y2) - (minY - y2)*(x3 - x2);
    float E3_row = (minX - x3)*(y1 - y3) - (minY - y3)*(x1 - x3);

    // Increments

    float x_E1_it =  (y2 - y1) * stepX;
    float x_E2_it =  (y3 - y2) * stepX;
    float x_E3_it =  (y1 - y3) * stepX;

    float y_E1_it = -(x2 - x1) * stepY;
    float y_E2_it = -(x3 - x2) * stepY;
    float y_E3_it = -(x1 - x3) * stepY;

    float E1, E2, E3;

    for(float y = minY; y < maxY; y += stepY) {

        E1 = E1_row, E2 = E2_row, E3 = E3_row;

        for(float x = minX; x < maxX; x += stepX) {
            if(E1 <= 0 && E2 <= 0 && E3 <= 0) {

                //interpolation
                
                Fragment frag;

                frag.screen_pos.x = (1.0f + x) * width * 0.5f;
                frag.screen_pos.y = (1.0f - y) * height * 0.5f;

                float w1 = ((x2 - x)*(y3 - y) - (x3 - x)*(y2 - y)) * inv_area;
                float w2 = ((x3 - x)*(y1 - y) - (x1 - x)*(y3 - y)) * inv_area;
                float w3 = 1.0f - w1 - w2;

                frag.vertex_color = 
                    v[0].color * w1 +
                    v[1].color * w2 +
                    v[2].color * w3;

                fragments.push_back(frag);
            }
            E1 += x_E1_it;
            E2 += x_E2_it;
            E3 += x_E3_it;
        }
        E1_row += y_E1_it;
        E2_row += y_E2_it;
        E3_row += y_E3_it;
    }
    return fragments;
} 
