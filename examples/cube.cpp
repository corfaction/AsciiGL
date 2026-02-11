#include "../include/core/screen_buffer.hpp"
#include "../include/core/terminal.hpp"
#include "../include/math/vec.hpp"
#include "../include/math/mat.hpp"

int main() {

    size_t width, height;
    Terminal terminal;
    console3D::ScreenBuffer screen_buffer(terminal);

    terminal.getWindowSize(width, height);

    char* buffer = new char[width * height];
    
    for(int i = 0; i < width * height; i++) {
        buffer[i] = 'B';
    }
 
    while(true) {
        screen_buffer.clear();
        screen_buffer.drawBuffer(buffer);
        screen_buffer.swap();
        screen_buffer.present();
    }
}
