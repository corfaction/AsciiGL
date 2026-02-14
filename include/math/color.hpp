#pragma once

namespace AsciiGL {
     struct Color {
         float r, g, b, a;

    	 static constexpr char gradient[] = " .,:;|WB@";
	 static constexpr int gradientSize = 8;
    
         Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

         Color(float rgb) : r(rgb), g(rgb), b(rgb), a(1) {}

         Color(float red, float green, float blue, float alpha = 1.0f) 
             : r(red), g(green), b(blue), a(alpha) {}

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
	     int index = static_cast<int>(r * 0.2126f + g * 0.7152f + b * 0.0722f) * gradientSize;

	     return gradient[index];
	 }

	 int getGradientSize() const {return gradientSize;}
     
         static const Color Red;
         static const Color Green;
         static const Color Blue;
    };
   
    const Color Color::Red(1.0f, 0.0f, 0.0f);
    const Color Color::Green(0.0f, 1.0f, 0.0f);
    const Color Color::Blue(0.0f, 0.0f, 1.0f);
}
