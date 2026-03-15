#include "../include/AsciiGL.hpp"
#include <stdexcept>
#include <iostream>

using namespace AsciiGL;

int main() {

    Terminal terminal;
    ScreenBuffer screen_buffer(terminal);
 
    // coordinates vertices of square

    std::vector<float> square = 

    //                VERTICES
    //     POSITION              COLOR
    {-0.7f, -0.7f, 0.0f,    1.0f, 0.0f, 0.0f, 
      0.7f, -0.7f, 0.0f,    0.0f, 1.0f, 0.0f,
     -0.7f,  0.7f, 0.0f,    0.0f, 0.0f, 1.0f,        
      0.7f,  0.7f, 0.0f,    1.0f, 0.0f, 0.0f};

    VBO* vbo = new VBO();
    vbo->setData(square);

    std::vector<unsigned int> indices =

    {0, 1, 2,
     2, 1, 3};

    EBO* ebo = new EBO();
    ebo->setData(indices);

    VAO* vao = new VAO();
    vao->bindEBO(ebo);
    vao->bindVBO(vbo);

    // addAttribute(index, size, offset)

    vao->addAttribute(0, 3, 0);  // Position  
    vao->addAttribute(1, 3, 3);  // Color

    Renderer renderer(screen_buffer);

    // Main loop

    while(true) {
        screen_buffer.clear();
        renderer.drawTriangles(vao, 6);
        screen_buffer.swap();
        screen_buffer.present();
    }

    // Here we need to delete the pointer, but there is an infinite loop here, 
    // so there is no point in it
}
