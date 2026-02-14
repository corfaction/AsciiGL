#pragma once 
#include <iostream>

namespace AsciiGL {

class Terminal {
public:
    Terminal();
    
    void getWindowSize(size_t& width, size_t& height) const;
    float getAspectRatio() const;

    void setChar(size_t x, size_t y, char c);
    void flushBuffer();

    ~Terminal();

private:
    class Impl;
    Impl* pImpl;
};

}
