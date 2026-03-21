#pragma once
#include "screen_buffer.hpp"
#include "../graphics/rasterizer.hpp"
#include "../graphics/vertex_array.hpp"
#include "../graphics/shader_program.hpp"
#include <memory>

namespace AsciiGL {

class Renderer {
private:

    ScreenBuffer& screen;
    size_t width, height;
    size_t screen_size;
    Rasterizer rasterizer;
    std::shared_ptr<ShaderProgram> shader_program;
    std::shared_ptr<UniformManager> global_uniform_manager;
    char* buffer;

    std::vector<std::vector<float>> vaoToAttributeMatrix(const VAO* vao, int vertex_index) const;
    void clearBuffer();

public:

    Renderer(ScreenBuffer& input_screen);

    void drawTriangles(const VAO* vao, int vertex_num);
    void setShaderProgram(std::shared_ptr<ShaderProgram> shader_program);
    void setUniformManager(std::shared_ptr<UniformManager> manager);

    ~Renderer();
};

}
