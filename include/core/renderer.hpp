#pragma once
#include "screen_buffer.hpp"
#include "../graphics/rasterizer.hpp"

namespace AsciiGL {

class Renderer {
private:

    ScreenBuffer& screen;
    size_t width, height;
    size_t screen_size;
    Rasterizer rasterizer;
    char* buffer;

    Vertex vertexShaider(std::vector<float>& data) const;
    void fragmentShaider(Fragment& fragment);

public:

    Renderer(ScreenBuffer& input_screen);

    void drawTriangles(std::vector<std::vector<float>>& data);

    ~Renderer();
};

}
