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
};

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
};

struct ivec2 {
    int x, y;

    ivec2();
    ivec2(int x, int y);

    ivec2 operator*(const ivec2 a) const;
    ivec2 operator*(const float& a) const;
    ivec2 operator+(const ivec2& a) const;
};

}

}
