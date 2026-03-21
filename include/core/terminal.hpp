#pragma once
#include <memory>

class TerminalImpl {
public:
    virtual ~TerminalImpl() = default;

    virtual void getWindowSize(size_t&, size_t&) const = 0;
    virtual float getAspectRatio() const = 0;
    virtual void initialize() = 0;
    virtual void cleanup() = 0;
};

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

    std::unique_ptr<TerminalImpl> pImpl;
    
    size_t width = 80;
    size_t height = 25;
    size_t cursor_x = 0;
    size_t cursor_y = 0;
};

}
