#pragma once
#include <vector>
#include "graphics_types.hpp"

namespace AsciiGL {

class Rasterizer{
private:
    float width, height;
public:

    Rasterizer(float w, float h) : width(w), height(h) {}

    std::vector<Fragment> drawTriangle(std::vector<Vertex>& vertices) {
        if(vertices.size() != 3) throw std::out_of_range("vertices size != 3");

        float stepX = 2.0f / width;
        float stepY = 2.0f / height;
        
        //for A vertex
        float& x1 = vertices[0].pos.x;
        float& y1 = vertices[0].pos.y;

        //for B vertex
        float& x2 = vertices[1].pos.x;
        float& y2 = vertices[1].pos.y;

        //for C vertex
        float& x3 = vertices[2].pos.x;
        float& y3 = vertices[2].pos.y;

        // edge projection
        float AB_x = x2 - x1;
        float AB_y = y2 - y1;
        float BC_x = x3 - x2;
        float BC_y = y3 - y2;
        float CA_x = x1 - x3;
        float CA_y = y1 - y3;

        // Increments for edges
        float i_E1_x =  AB_y;
        float i_E1_y = -AB_x;
        float i_E2_x =  BC_y;
        float i_E2_y = -BC_x;
        float i_E3_x =  CA_y;
        float i_E3_y = -CA_x;

        // BoundingBox
        float minX = std::min(x1, std::min(x2, x3));
        float maxX = std::max(x1, std::max(x2, x3));
        float minY = std::min(y1, std::min(y2, y3));
        float maxY = std::max(y1, std::max(y2, y3));

        float S_ABC = AB_x * (y3 - y1) - (x3 - x1) * AB_y;
        if (S_ABC == 0) return {};

        std::vector<Fragment> fragments;

        for(float y = maxY; y > minY; y -= stepY) {  

            // edge Function
            float E1 = (minX - x1) * AB_y - (y - y1) * AB_x;
            float E2 = (minX - x2) * BC_y - (y - y2) * BC_x;
            float E3 = (minX - x3) * CA_y - (y - y3) * CA_x;

            for(float x = minX; x < maxX; x += stepX) {

                if(E1 >= 0 && E2 >= 0 && E3 >= 0) {
                    
                    Fragment fragment;

                    fragment.screen_x = (1.0f + x) * width * 0.5f;
                    fragment.screen_y = (1.0f - y) * height * 0.5f;

                    // interpolation

                    float w1 = E2 / S_ABC;
                    float w2 = E3 / S_ABC;
                    float w3 = 1.0f - w1 - w2;

                    fragment.color = vertices[0].color * w1 
                        + vertices[1].color * w2 + vertices[2].color * w3;

                    fragments.push_back(fragment);
                    
                }

                E1 += i_E1_x;
                E2 += i_E2_x;
                E3 += i_E3_x;
            }
            E1 += i_E1_y;
            E2 += i_E2_y;
            E3 += i_E3_y;
        }
        return fragments;
    }

};

}
