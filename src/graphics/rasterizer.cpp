#include "../../include/graphics/rasterizer.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

using namespace AsciiGL;

std::vector<Fragment> Rasterizer::makeTriangle(std::vector<Vertex>& v) {

    if (v.size() != 3)
        throw std::out_of_range("vertices size != 3");

    std::vector<Fragment> fragments;

    float stepX = 2.0f / (width * 3.0f);
    float stepY = 2.0f / (height * 3.0f);

    float& x1 = v[0].pos.x; float& y1 = v[0].pos.y;
    float& x2 = v[1].pos.x; float& y2 = v[1].pos.y;
    float& x3 = v[2].pos.x; float& y3 = v[2].pos.y;

    float area = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);

    float minX = std::min({x1, x2, x3});
    float maxX = std::max({x1, x2, x3});
    float minY = std::min({y1, y2, y3});
    float maxY = std::max({y1, y2, y3});

    for(float y = minY; y < maxY; y += stepY) {
        for(float x = minX; x < maxX; x += stepX) {
            float E1 = (x - x1)*(y2 - y1) - (y - y1)*(x2 - x1);
            float E2 = (x - x2)*(y3 - y2) - (y - y2)*(x3 - x2);
            float E3 = (x - x3)*(y1 - y3) - (y - y3)*(x1 - x3);

            if(E1 <= 0 && E2 <= 0 && E3 <= 0) {
                Fragment frag;

                frag.screen_pos.x = (1.0f + x) * width * 0.5f;
                frag.screen_pos.y = (1.0f - y) * height * 0.5f;

                float w1 = ((x2 - x)*(y3 - y) - (x3 - x)*(y2 - y)) / area;
                float w2 = ((x3 - x)*(y1 - y) - (x1 - x)*(y3 - y)) / area;
                float w3 = 1.0f - w1 - w2;

                frag.vertex_color = 
                    v[0].color * w1 +
                    v[1].color * w2 +
                    v[2].color * w3;

                fragments.push_back(frag);
            }
        }
    }
    return fragments;
}
