#include "../include/AsciiGL.hpp"

using namespace AsciiGL;

int main() {

    size_t width, height;
    Terminal terminal;
    ScreenBuffer screen_buffer(terminal);

    terminal.getWindowSize(width, height);

    //std::vector<std::vector<float>> triangle = {{-0.9f, -0.9f, 0.0f,   1.0f, 0.0f, 0.0f},
    //                                            { 0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f},
    //                                            { 0.0f,  0.9f, 0.0f,   0.0f, 0.0f, 1.0f}};
    
    std::vector<std::vector<float>> square = {{-0.7f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f},
                                              { 0.7f, -0.7f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f},
                                              {-0.7f,  0.7f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f},
                                                
                                              {-0.7f,  0.7f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f},
                                              { 0.7f, -0.7f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f},
                                              { 0.7f,  0.7f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f}};

    Renderer renderer(screen_buffer);


    while(true) {
        screen_buffer.clear();
        renderer.drawTriangles(square);
        screen_buffer.swap();
        screen_buffer.present();
    }
}
