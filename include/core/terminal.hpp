#pragma once 
#include <iostream>

namespace AsciiGL {

class Terminal {
public:
    Terminal();
    
    void getWindowSize(size_t& w, size_t& h) const;
    float getAspectRatio() const;

    void setChar(size_t x, size_t y, char c);
    void resetCursor();

    ~Terminal();

private:
    size_t width, height;
    int cursorX, cursorY;

    class Impl;
    Impl* pImpl;
};

}
