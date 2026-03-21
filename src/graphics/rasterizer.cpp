#include "../../include/graphics/rasterizer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace AsciiGL;

Rasterizer::Rasterizer(const float w, const float h) : width(w), height(h) {
    screen_size = static_cast<int>(w * h);
    zbuffer = new float[screen_size];
    clearZBuffer();
}   

std::vector<Fragment> Rasterizer::makeTriangle(std::vector<Vertex>& input_vertex) {

    if (input_vertex.size() != 3)
        throw std::length_error("vertices size != 3");

    std::vector<Vertex> v = perspectiveDivision(input_vertex);

    std::vector<Fragment> fragments;

    float step_x = 2.0f / width;
    float step_y = 2.0f / height;

    float& x1 = v[0].pos.x; float& y1 = v[0].pos.y;
    float& x2 = v[1].pos.x; float& y2 = v[1].pos.y;
    float& x3 = v[2].pos.x; float& y3 = v[2].pos.y;    

    float area = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);

    if(area == 0) return fragments;

    float inv_area = 1.0f / area;

    float min_x_ndc = std::max(std::min({x1, x2, x3}), -1.0f);
    float max_x_ndc = std::min(std::max({x1, x2, x3}),  1.0f);
    float min_y_ndc = std::max(std::min({y1, y2, y3}), -1.0f);
    float max_y_ndc = std::min(std::max({y1, y2, y3}),  1.0f);

    int min_x = (int)((1.0f + min_x_ndc) * width * 0.5f);
    int max_x = (int)((1.0f + max_x_ndc) * width * 0.5f) + 1;
    int min_y = (int)((1.0f - max_y_ndc) * height * 0.5f);
    int max_y = (int)((1.0f - min_y_ndc) * height * 0.5f) + 1;

    min_x = std::max((int)min_x, 0);
    max_x = std::min(max_x, (int)width);
    min_y = std::max((int)min_y, 0);
    max_y = std::min(max_y, (int)height);

    float start_x_ndc = (min_x + 0.5f) * 2.0f / width - 1.0f;
    float start_y_ndc = 1.0f - (min_y + 0.5f) * 2.0f / height;

    float E1, E2, E3;

    for(int y = min_y; y < max_y; ++y) {
        
        float y_ndc = 1.0f - (y + 0.5f) * 2.0f / height;
        
        for(int x = min_x; x < max_x; ++x) {
            
            float x_ndc = (x + 0.5f) * 2.0f / width - 1.0f;
            
            float e1 = (x_ndc - x1)*(y2 - y1) - (y_ndc - y1)*(x2 - x1);
            float e2 = (x_ndc - x2)*(y3 - y2) - (y_ndc - y2)*(x3 - x2);
            float e3 = (x_ndc - x3)*(y1 - y3) - (y_ndc - y3)*(x1 - x3);
            
            if(e1 <= 0.0f && e2 <= 0.0f && e3 <= 0.0f) {
                
                Fragment frag;
                frag.screen_pos.x = x;
                frag.screen_pos.y = y;
                
                float alpha = e2 * inv_area;
                float beta  = e3 * inv_area;
                float gamma = 1.0f - alpha - beta;
                
                float z_ndc = v[0].pos.z * alpha + v[1].pos.z * beta + v[2].pos.z * gamma;

                float depth = (z_ndc + 1.0f) * 0.5f;
                depth = std::max(0.0f, std::min(1.0f, depth));
                
                int index = y * width + x;
                
                if(depth < zbuffer[index]) {
                    zbuffer[index] = depth;

                    frag.vertex_color = v[0].color * alpha + v[1].color * beta + v[2].color * gamma;

                    fragments.push_back(frag);
                }
            }
        }
    }
    return fragments;
}

std::vector<Vertex> Rasterizer::perspectiveDivision(std::vector<Vertex>& v) const {
    std::vector<Vertex> ndcVertices(3);
    for (int i = 0; i < v.size(); ++i) {
        if (v[i].pos.w != 0.0f) {
            ndcVertices[i].pos.x = v[i].pos.x / v[i].pos.w;
            ndcVertices[i].pos.y = v[i].pos.y / v[i].pos.w;
            ndcVertices[i].pos.z = v[i].pos.z / v[i].pos.w;
            ndcVertices[i].pos.w = 1.0f;
        } else {
            ndcVertices[i].pos = v[i].pos;
        }
        ndcVertices[i].color = v[i].color;
    }
    return ndcVertices;
}

void Rasterizer::clearZBuffer() {
    std::fill(zbuffer, zbuffer + screen_size, 1.0f);
}