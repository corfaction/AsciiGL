#pragma once
#include <algorithm>

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

    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    Color(float rgb) : r(rgb), g(rgb), b(rgb), a(1.0f) {}

    Color(float red, float green, float blue, float alpha = 1.0f) 
        : r(red), g(green), b(blue), a(alpha) {}

    Color(vec4 xyzw) : r(xyzw.x), g(xyzw.y), b(xyzw.z), a(xyzw.w) {}

    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b, a * other.a);
    }

    Color operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar, a);
    }

    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b, a + other.a);
    }
 
    vec4 toVec4() const { return vec4(r, g, b, a); }
 
    Color alphaBlending(Color& b) const {
        return *this * a + b * (1.0f - a);
    }
 
    char toChar() const {
       float index = (r * 0.2126f + g * 0.7152f + b * 0.0722f) * static_cast<float>(gradientSize);
       if(index > 0.0f && index < 1.0f) index = 1.0f;
       index = std::min(std::max(0.0f, index), static_cast<float>(gradientSize));

       return gradient[static_cast<int>(index)];
    }

    int getGradientSize() const {return gradientSize;}
 
};   

} // Math

} // AsciiGL
