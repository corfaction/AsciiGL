#include "../../include/AsciiGL/core/screen_buffer.hpp"
#include "../../include/AsciiGL/graphics/graphics_types.hpp"
#include "../../include/AsciiGL/graphics/vertex_array.hpp"
#include "../../include/AsciiGL/graphics/shader_program.hpp"
#include "../../include/AsciiGL/core/renderer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <memory>

using namespace AsciiGL;

Renderer::Renderer() : 
    shader_program(std::make_shared<DefaultShader>()),
    global_uniform_manager(std::make_shared<UniformManager>())
{}

inline bool inBound(size_t width, size_t height, int index) {
    return (index < 0 || index >= width * height) ? false : true;
}

void Renderer::draw(const VAO* vao, int vertex_num) {
    if(vertex_num % 3 != 0) 
        throw std::length_error("the triangle is missing vertices. vertex_num % 3 != 0");

    if(!target_screen_buffer) 
        throw std::runtime_error("Screen buffer is not set. Call setTarget() before using this method.");

    updateSize();

    rasterizer.clearZBuffer(width, height);
    
    std::vector<ChangedSymbol> buffer;

    // Using a vertex shader

    std::vector<Vertex> vertices;

    vertices.reserve(vao->getVertexCount());

    for(size_t vertex = 0; vertex < vao->getVertexCount(); ++vertex) {
        auto vertex_matrix = vaoToAttributeMatrix(vao, vertex);
        vertices.push_back(shader_program->vertexShader(vertex_matrix));
    }

    for(size_t triangle = 0; triangle < vertex_num / 3; ++triangle) {

        // Rasterization

        auto& v1 = vertices[vao->getIndex(triangle * 3)];
        auto& v2 = vertices[vao->getIndex(triangle * 3 + 1)];
        auto& v3 = vertices[vao->getIndex(triangle * 3 + 2)];

        std::vector<Fragment> fragments = 
            rasterizer.makeTriangle(v1, v2, v3, static_cast<float>(width), static_cast<float>(height));

        // Using a fragment shader

        if(fragments.size() == 0) { continue; }
        
        for(Fragment& fragment : fragments) {
            shader_program->fragmentShader(fragment);

            if(!inBound(width, height, fragment.index)) continue;

            ChangedSymbol changed_symbol;

            changed_symbol.index = fragment.index;
            changed_symbol.c = fragment.color.toChar();
            
            buffer.push_back(changed_symbol);
        }

    }
    target_screen_buffer->drawBuffer(buffer); 
}

std::vector<std::vector<float>> Renderer::vaoToAttributeMatrix(const VAO* vao, int index) const {
    std::vector<std::vector<float>> vertex_data;

    vertex_data.reserve(vao->getAttributeCount());

    for(int a = 0; a < vao->getAttributeCount(); ++a) {
        vertex_data.push_back(vao->getAttribute(index, a));
    }
    return vertex_data;
}

void Renderer::setShaderProgram(std::shared_ptr<ShaderProgram> program) {
    shader_program = program;
    if (shader_program) {
        shader_program->setUniformManager(global_uniform_manager);
    }
}

void Renderer::setUniformManager(std::shared_ptr<UniformManager> manager) {
    global_uniform_manager = manager;
    if (shader_program) {
        shader_program->setUniformManager(global_uniform_manager);
    }
}

void Renderer::setTarget(ScreenBuffer& input_screen_buffer) {
    target_screen_buffer = &input_screen_buffer;
}

void Renderer::updateSize() {
    size_t w = target_screen_buffer->getWidth();
    size_t h = target_screen_buffer->getHeight();

    if(w != width || h != height) {
        width = w; 
        height = h;
    }
}