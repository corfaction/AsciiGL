#pragma once
#include <vector>
#include <memory>

struct ChangedSymbol {
    int x = -1, y = -1;
    size_t index;
    char c;
};

namespace AsciiGL {

class ScreenBuffer {
private:

    size_t width, height;
    size_t screen_size;
    std::unique_ptr<char[]> back_buffer;
    std::unique_ptr<char[]> front_buffer;
    char clear_color = ' ';

    void clearBuffer(char* buffer, char clear_color = ' ');

public:

    ScreenBuffer(size_t w, size_t h);

    void setClearColor(const char c);
    void swap();
    std::vector<ChangedSymbol> getChangesOnly(); 
    void drawBuffer(std::vector<ChangedSymbol> input_buffer);
    void flushBackBuffer();
    void setSize(size_t w, size_t h);

    size_t getWidth() const { return width; }
    size_t getHeight() const { return height; }
    
};

}
