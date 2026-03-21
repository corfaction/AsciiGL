#include "../include/AsciiGL.hpp"
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>

using namespace AsciiGL;

int main() {

    Terminal terminal;
    ScreenBuffer screen_buffer(terminal);
 
    // coordinates vertices of square

    std::vector<float> square = 

    //                VERTICES
    //     POSITION              COLOR 
    {
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
    
     0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
    
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f
    };

    VBO* vbo = new VBO();
    vbo->setData(square);

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
    
        4, 5, 6,
        4, 6, 7,
    
        8, 9, 10,
        8, 10, 11,
    
        12, 13, 14,
        12, 14, 15,
    
        16, 17, 18,
        16, 18, 19,

        20, 21, 22,
        20, 22, 23
    };

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

    auto shader = std::make_shared<DefaultShader>();

    size_t w, h;
    terminal.getWindowSize(w, h);
    float width = static_cast<float>(w), height = static_cast<float>(h);

    renderer.setShaderProgram(shader);

    float i = 0.0f;
    while(true) {
        screen_buffer.clear();

        mat4 model = matrix::translation(vec3(0.0f, 0.0f, -3.0f + sin(i)))
            * matrix::rotation(vec3(i, i, i)) 
            * matrix::scale(vec3(1.0f, 1.0f, 1.0f));
            
        mat4 MVP = matrix::perspective(60.0f * 3.14159f / 180.0f, width / height * terminal.getAspectRatio(), 0.1f, 1000.0f) 
            * mat4(1.0f) // There is no representation matrix; instead, the identity matrix is ​​used for now. 
            * model;

        shader->setUniform<mat4>("MVP", MVP);

        renderer.drawTriangles(vao, 36);
        screen_buffer.swap();
        screen_buffer.present();
        i += 0.05f;
    }

    // Here we need to delete the pointer, but there is an infinite loop here, 
    // so there is no point in it
}
