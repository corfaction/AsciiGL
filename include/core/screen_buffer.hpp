#pragma once
#include <iostream>
#include "terminal.hpp"

namespace console3D {

class ScreenBuffer {
private:

    size_t width, height;
    size_t screen_size;
    char* back_buffer;
    char* front_buffer;
    char clear_color;
    Terminal& terminal;

public:

    ScreenBuffer(Terminal& input_terminal);

    void setClearColor(const char c);
    void clear();
    void swap();
    void present(); 
    void drawBuffer(char* input_buffer);

    size_t getWidth() const {return width;}
    size_t getHeight() const {return height;}

    ~ScreenBuffer();
};

}
