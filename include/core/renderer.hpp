#pragma once
#include "screen_buffer.hpp"
#include "../graphics/rasterizer.hpp"
#include "../graphics/vertex_array.hpp"
#include "../graphics/shader_program.hpp"
#include <memory>

namespace AsciiGL {

/**
 * The Renderer class coordinates all rendering operations:
 * - Renders vertex arrays (VAO) into screen fragments
 * - Manages shader program installation and switching
 * - Controls the rasterizer for primitive rasterization
 * - Handles uniform variables and the uniform manager for shader data
 * 
 * Before calling draw(), you must:
 * 1. Set a target screen buffer using setTarget()
 * 2. Set a shader program using setShaderProgram()
*/

class Renderer {
private:

    ScreenBuffer* target_screen_buffer;

    size_t width, height; // current screen size

    Rasterizer rasterizer;

    std::shared_ptr<ShaderProgram> shader_program;
    std::shared_ptr<UniformManager> global_uniform_manager;

    std::vector<std::vector<float>> vaoToAttributeMatrix(const VAO* vao, int vertex_index) const;

public:

    Renderer();

    void updateSize();
    void draw(const VAO* vao, int vertex_num);
    void setShaderProgram(std::shared_ptr<ShaderProgram> shader_program);
    void setUniformManager(std::shared_ptr<UniformManager> manager);
    void setTarget(ScreenBuffer& input_screen_buffer);
    
};

} // AsciiGL
