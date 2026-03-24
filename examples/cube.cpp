#include "../include/AsciiGL.hpp"
#include <stdexcept>
#include <iostream>

using namespace AsciiGL;

int main() {

    Terminal terminal;
    size_t width, height;
    terminal.getWindowSize(width, height);

    ScreenBuffer screen_buffer(width, height);
 
    // coordinates vertices of cube

    std::vector<float> cube = 

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
    vbo->setData(cube);

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

    Renderer renderer;

    renderer.setTarget(screen_buffer);

    // Main loop

    auto shader = std::make_shared<DefaultShader>();

    renderer.setShaderProgram(shader);

    float i = 0.0f;
    while(true) {

        screen_buffer.flushBackBuffer();

        mat4 model = matrix::translation(vec3(0.0f, 0.0f, -3.0f + sin(i)))
            * matrix::rotation(vec3(i, i, i)) 
            * matrix::scale(vec3(1.0f, 1.0f, 1.0f));
            
        mat4 MVP =
            matrix::perspective(60.0f * 3.14159f / 180.0f, static_cast<float>(width) / static_cast<float>(height) * terminal.getAspectRatio(), 0.1f, 1000.0f) 
            * mat4(1.0f) // There is no representation matrix; instead, the identity matrix is ​​used for now. 
            * model;

        shader->setUniform<mat4>("MVP", MVP);

        renderer.draw(vao, 36);

        screen_buffer.swap();
        terminal.present(screen_buffer);

        if(terminal.updateSize()) {
            terminal.getWindowSize(width, height);
            screen_buffer.setSize(width, height);
            renderer.updateSize();
        }

        i += 0.05f;
    }

    delete vao;
    delete vbo;
    delete ebo;
}
