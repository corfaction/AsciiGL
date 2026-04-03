
// This file contains declaration vectors and math methods for work with them

#pragma once
#include <vector>
#include <cmath>

namespace AsciiGL {

namespace Math {

struct vec2 {
    float x, y;

    vec2();
    vec2(float x, float y);

    vec2 operator*(const vec2& a) const;
    vec2 operator*(const float& a) const;

    vec2 operator+(const vec2& a) const;
    vec2 operator-(const vec2& a) const;
};

float dot(const vec2& a, const vec2& b);
float length(const vec2& v);
vec2 normalize(const vec2& v);

struct vec4;

struct vec3 {
    float x, y, z;

    vec3();

    vec3(float a);
    vec3(float x, float y, float z);
    vec3(const std::vector<float>& xyz);

    vec3(const vec4& v);

    vec3 operator*(const vec3& a) const;
    vec3 operator*(const float& a) const;

    vec3 operator+(const vec3& a) const;
    vec3 operator-(const vec3& a) const;

    vec2 xy() const {return vec2(x, y);}
};

float dot(const vec3& a, const vec3& b);
float length(const vec3& v);
vec3 normalize(const vec3& v);

struct vec4 {
    float x, y, z, w;

    vec4();
    vec4(float x, float y, float z, float w);
    vec4(vec3 xyz, float w);

    vec4 operator*(const vec4& a) const;
    vec4 operator*(const float& a) const;

    vec4 operator+(const vec4& a) const;
    vec4 operator-(const vec4& a) const;

    vec2 xy() const {return vec2(x, y);}
    vec3 xyz() const {return vec3(x, y, z);}
};

struct ivec2 {
    int x, y;

    ivec2();
    ivec2(int x, int y);

    ivec2 operator*(const ivec2 a) const;
    ivec2 operator*(const float& a) const;
    ivec2 operator+(const ivec2& a) const;
};

float dot(const vec4& a, const vec4& b);
float length(const vec3& v);
vec4 normalize(const vec4& v);

} // Math

} // AsciiGL
