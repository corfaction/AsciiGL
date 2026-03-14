#pragma once
#include "screen_buffer.hpp"
#include "../graphics/rasterizer.hpp"
#include "../graphics/vertex_array.hpp"

namespace AsciiGL {

class Renderer {
private:

    ScreenBuffer& screen;
    size_t width, height;
    size_t screen_size;
    Rasterizer rasterizer;
    char* buffer;

    Vertex vertexShaider(std::vector<std::vector<float>>& data) const;
    void fragmentShaider(Fragment& fragment);
    std::vector<std::vector<float>> vaoToAttributeMatrix(const VAO* vao, int vertex_index) const;
    void clearBuffer();

public:

    Renderer(ScreenBuffer& input_screen);

    void drawTriangles(const VAO* vao, int vertex_num);

    ~Renderer();
};

}
