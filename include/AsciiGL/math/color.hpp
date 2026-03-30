#pragma once
#include "vec.hpp"

namespace AsciiGL {

namespace Math {

/**
 * This structure provides convenient operations for:
 * - Converting between RGB and gradient characters
 * - Blending and interpolating colors
 * 
 * Terminal color support:
 * - numbers from 0.0f to 1.0f
 * - alpha channel
*/

struct Color {
    float r, g, b, a;

    static constexpr char gradient[] = " .,:;if|}]ILNMWB@";
    static constexpr int gradientSize = 16;

    Color();
    Color(float rgb);
    Color(float red, float green, float blue, float alpha = 1.0f);
    Color(vec4 xyzw);

    Color operator*(const Color& other) const;
    Color operator*(float scalar) const;
    Color operator+(const Color& other) const;
 
    Color alphaBlending(Color& b) const;

    vec4 toVec4() const;
    char toChar() const;

    int getGradientSize() const;
 
};   

} // Math

} // AsciiGL
