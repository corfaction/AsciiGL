#include <iostream>
#include <algorithm>
#include <cstring>
#include "../../include/core/screen_buffer.hpp"

using namespace AsciiGL;

ScreenBuffer::ScreenBuffer(size_t w, size_t h) : width(w), height(h), screen_size(w * h) {

    back_buffer = std::make_unique<char[]>(screen_size);
    front_buffer = std::make_unique<char[]>(screen_size);

    clearBuffer(back_buffer.get());
    clearBuffer(front_buffer.get());

}

void ScreenBuffer::clearBuffer(char* buffer, char clear_color) {
    std::memset(buffer, clear_color, screen_size);
}

void ScreenBuffer::flushBackBuffer() {
    clearBuffer(back_buffer.get(), clear_color);
}

void ScreenBuffer::setClearColor(char c) {
    clear_color = c;
}

void ScreenBuffer::swap() {
    std::swap(back_buffer, front_buffer);
}

std::vector<ChangedSymbol> ScreenBuffer::getChangesOnly() {
    std::vector<ChangedSymbol> changes;

    for(size_t i = 0; i < screen_size; ++i) {
        if(front_buffer[i] != back_buffer[i]) {
            ChangedSymbol changed_symbol;

            changed_symbol.index = i;
            changed_symbol.c = front_buffer[i];

            changed_symbol.x = i % width;
            changed_symbol.y = i / width;

            changes.push_back(changed_symbol);
        }
    }

    return changes;
}

void ScreenBuffer::drawBuffer(std::vector<ChangedSymbol> input_buffer) {
    for(auto& sym : input_buffer) {
        back_buffer[sym.index] = sym.c;
    }
}

void ScreenBuffer::setSize(size_t w, size_t h) {

    back_buffer.reset(new char[screen_size]);
    front_buffer.reset(new char[screen_size]);

    clearBuffer(back_buffer.get());
    clearBuffer(front_buffer.get());

    width = w;
    height = h;
}

