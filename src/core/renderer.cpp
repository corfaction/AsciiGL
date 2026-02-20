#include "../../include/core/renderer.hpp"
#include "../../include/core/screen_buffer.hpp"
#include "../../include/graphics/rasterizer.hpp"
#include "../../include/graphics/graphics_types.hpp"
#include <vector>

using namespace AsciiGL;

Renderer::Renderer(ScreenBuffer& input_screen) : 
    screen(input_screen), 
    width(screen.getWidth()), height(screen.getHeight()),
    screen_size(width * height),
    rasterizer(width, height)
{
    buffer = new char[screen_size + 1];
    buffer[screen_size] = '\0';
}

Vertex Renderer::vertexShaider(std::vector<float>& data) const {
    Vertex vertex;
    vertex.pos.x = data[0];
    vertex.pos.y = data[1];
    vertex.pos.z = data[2];
    vertex.pos.w = 1.0f;

    vertex.color.x = data[3];
    vertex.color.y = data[4];
    vertex.color.z = data[5];
    vertex.color.w = data[6];

    return vertex;
}

void Renderer::fragmentShaider(Fragment& fragment) {
    fragment.color.r = fragment.vertex_color.x;
    fragment.color.g = fragment.vertex_color.y;
    fragment.color.b = fragment.vertex_color.z;
    fragment.color.a = fragment.vertex_color.w;
}

void Renderer::drawTriangles(std::vector<std::vector<float>>& data) {
    if(data.size() % 3 != 0) 
        throw std::length_error("the triangle is missing vertices. data.size() % 3 != 0");

    for(size_t i = 0; i < data.size() / 3; ++i) {

        for(size_t j = 0; j < screen_size; ++j) {
            buffer[j] = ' ';
        }

        std::vector<Vertex> vertices;

        // Using a vertex shader

        for(size_t j = 0; j < 3; ++j) {
            vertices.push_back(vertexShaider(data[3 * i + j]));
        }

        // Rasterization

        std::vector<Fragment> fragments = rasterizer.makeTriangle(vertices);

        // Using a fragment shader

        for(size_t j = 0; j < fragments.size(); ++j) {
            Fragment& fragment = fragments[j];

            fragmentShaider(fragment);

            if(fragment.screen_pos.x < 0) continue;
            if(fragment.screen_pos.y < 0) continue;
            if(fragment.screen_pos.x >= width) continue;
            if(fragment.screen_pos.y >= height) continue;
            
            buffer[fragment.screen_pos.y * width + fragment.screen_pos.x] = fragment.color.toChar();
        }

        screen.drawBuffer(buffer);
    }
}

Renderer::~Renderer() {
    delete[] buffer;
}
