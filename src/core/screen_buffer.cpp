#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "../../include/core/screen_buffer.hpp"

    using namespace console3D;

    ScreenBuffer::ScreenBuffer(Terminal& input_terminal) : terminal(input_terminal) {

        terminal.getWindowSize(width, height);
        screen_size = width * height;

        back_buffer = new char[screen_size + 1];
        front_buffer = new char[screen_size + 1];

        for(size_t i = 0; i < screen_size; ++i) {
            back_buffer[i] = ' ';
            front_buffer[i] = ' ';
        }

        back_buffer[screen_size] = '\0';
        front_buffer[screen_size] = '\0';

        clear_color = ' ';

        for(size_t i = 0; i < height; i++) {
                std::cout << std::endl;
        }
    }

    void ScreenBuffer::setClearColor(char c) {
            clear_color = c;
    }

    void ScreenBuffer::clear() {
        for(size_t i = 0; i < screen_size; ++i) {
            back_buffer[i] = clear_color;
        }
    }

    void ScreenBuffer::swap() {
        std::swap(back_buffer, front_buffer);
    }

    void ScreenBuffer::present() {
        int index = 0;
        for(size_t y = 0; y < height; ++y) {
            for(size_t x = 0; x < width; ++x) {

                if(front_buffer[index] != back_buffer[index]) {
                    terminal.setChar(x, y, front_buffer[index]);
                }
                index++;
            }
        }
        terminal.flushBuffer();
    }

    void ScreenBuffer::drawBuffer(char* input_buffer) {
        for(size_t i = 0; i < screen_size; ++i) {
            if(input_buffer[i] != ' ') 
                back_buffer[i] = input_buffer[i];

        }
    }

    ScreenBuffer::~ScreenBuffer() {
        delete[] back_buffer;
        delete[] front_buffer;
        back_buffer = nullptr;
        front_buffer = nullptr;
    }
