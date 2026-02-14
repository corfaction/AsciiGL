#include "../include/AsciiGL.hpp"

using namespace AsciiGL;

int main() {

    size_t width, height;
    Terminal terminal;
    ScreenBuffer screen_buffer(terminal);

    terminal.getWindowSize(width, height);

    char* buffer = new char[width * height];
    
    for(int i = 0; i < width * height; i++) {
        buffer[i] = 'B';
    }

    mat4 m;
    vec4 v;
 
    while(true) {
        screen_buffer.clear();
        screen_buffer.drawBuffer(buffer);
        screen_buffer.swap();
        screen_buffer.present();
    }
}
