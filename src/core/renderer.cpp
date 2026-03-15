#include "../../include/core/renderer.hpp"
#include "../../include/core/screen_buffer.hpp"
#include "../../include/graphics/rasterizer.hpp"
#include "../../include/graphics/graphics_types.hpp"
#include "../../include/graphics/vertex_array.hpp"
#include <stdexcept>
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

Vertex Renderer::vertexShaider(std::vector<std::vector<float>>& data) const {
    Vertex vertex;
    vertex.pos = vec4(vec3(data[0]), 1.0f);
    vertex.color = vec4(vec3(data[1]), 1.0f);

    return vertex;
}

void Renderer::fragmentShaider(Fragment& fragment) {
    fragment.color = Color(fragment.vertex_color);
}

void Renderer::drawTriangles(const VAO* vao, int vertex_num) {
    if(vertex_num % 3 != 0) 
        throw std::length_error("the triangle is missing vertices. data.size() % 3 != 0");

    for(size_t triangle = 0; triangle < vertex_num / 3; ++triangle) {

        std::vector<Vertex> vertices;

        // Using a vertex shader

        for(size_t vertex = 0; vertex < 3; ++vertex) {
            auto vertex_matrix = vaoToAttributeMatrix(vao, 3 * triangle + vertex);
            vertices.push_back(vertexShaider(vertex_matrix));
        }

        // Rasterization

        std::vector<Fragment> fragments = rasterizer.makeTriangle(vertices);

        // Using a fragment shader

        clearBuffer();

        for(Fragment& fragment : fragments) {
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

std::vector<std::vector<float>> Renderer::vaoToAttributeMatrix(const VAO* vao, int vertex_index) const {
    int index = vao->getIndex(vertex_index);
    std::vector<std::vector<float>> vertex_data;
    for(int a = 0; a < vao->getAttributeCount(); ++a) {
        vertex_data.push_back(vao->getAttribute(index, a));
    }
    return vertex_data;
}

void Renderer::clearBuffer() {
    for(size_t j = 0; j < screen_size; ++j) {
        buffer[j] = ' ';
    }
}

Renderer::~Renderer() {
    delete[] buffer;
}
