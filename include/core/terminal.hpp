#pragma once
#include <memory>

namespace AsciiGL {

class Terminal {
public:
    Terminal();
    ~Terminal();
    
    void setChar(size_t x, size_t y, char c);
    void resetCursor();
    void getWindowSize(size_t& w, size_t& h) const;
    float getAspectRatio() const;
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
    
    size_t width = 80;
    size_t height = 25;
    size_t cursorX = 0;
    size_t cursorY = 0;
};

}
