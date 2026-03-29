#pragma once
#include <memory>
#include "screen_buffer.hpp"

namespace AsciiGL {

/**
 * Abstract base class for cross-platform terminal operations.
 * 
 * This class defines the interface for terminal manipulation:
 * - Character output
 * - Cursor positioning
 * - Window size retrieval
 */

class TerminalImpl {
public:
    virtual ~TerminalImpl() = default;

    virtual void getWindowSize(size_t&, size_t&) const = 0;
    virtual float getAspectRatio() const = 0;
    virtual void initialize() = 0;
    virtual void cleanup() = 0;
    virtual void updateSize() = 0;
};

/**
 * This class provides methods for:
 * - Getting the current terminal window size for proper scaling
 * - Getting the character aspect ratio
 * - Displays the contents of the screen buffer by calling the screen buffer.getChangesOnly() method.
 * - When you change the screen size, the indents are removed and new ones are added.
*/

class Terminal {
public:

    Terminal();
    ~Terminal();
    
    void resetCursor();
    void getWindowSize(size_t& w, size_t& h) const;
    float getAspectRatio() const;
    void present(ScreenBuffer& screen_buffer);
    bool updateSize();
    
private:

    std::unique_ptr<TerminalImpl> pImpl;
    
    size_t width = 80;
    size_t height = 25;
    size_t cursor_x = 0;
    size_t cursor_y = 0;
};

} // AsciiGL
