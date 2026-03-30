#include <algorithm>
#include "../../include/AsciiGL/math/color.hpp"
#include "../../include/AsciiGL/math/vec.hpp"

namespace AsciiGL {

namespace Math {

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

Color::Color(float rgb) : r(rgb), g(rgb), b(rgb), a(1.0f) {}

Color::Color(float red, float green, float blue, float alpha) 
    : r(red), g(green), b(blue), a(alpha) {}

Color::Color(vec4 xyzw) : r(xyzw.x), g(xyzw.y), b(xyzw.z), a(xyzw.w) {}

Color Color::operator*(const Color& other) const {
    return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

Color Color::operator*(float scalar) const {
    return Color(r * scalar, g * scalar, b * scalar, a);
}

Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

vec4 Color::toVec4() const { return vec4(r, g, b, a); }

Color Color::alphaBlending(Color& b) const {
    return *this * a + b * (1.0f - a);
}

char Color::toChar() const {
   float index = (r * 0.2126f + g * 0.7152f + b * 0.0722f) * static_cast<float>(gradientSize);
   if(index > 0.0f && index < 1.0f) index = 1.0f;

   index = std::min(std::max(0.0f, index), static_cast<float>(gradientSize));
   return gradient[static_cast<int>(index)];
}

int Color::getGradientSize() const {return gradientSize;}

} // Math

} // AsciiGL
