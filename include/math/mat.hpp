// This file contains declaration matrices and math methods for work with them

#pragma once
#include "vec.hpp"
#include <stdexcept>

namespace AsciiGL {

namespace Math {

constexpr float PI = 3.14159265358979323846f;

struct mat4;

struct mat3 {
    vec3 m[3];

    mat3(const vec3& r0, const vec3& r1, const vec3& r2);
    mat3();
    mat3(float diag);
    mat3(const mat4& m);
    mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;

    vec3 operator*(const vec3& v) const;
    mat3 operator*(const mat3& a) const;
    void operator*=(const mat3& a);
};

mat3 transpose(const mat3& a);
mat3 inverse(const mat3& a);
float determinant(const mat3& a);

struct mat4 {
    vec4 m[4];

    mat4(const vec4& r0, const vec4& r1, const vec4& r2, const vec4& r3);
    mat4();
    mat4(float diag);
    mat4(const mat3& m);

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;

    vec4 operator*(const vec4& v) const;
    mat4 operator*(const mat4& a) const;
    void operator*=(const mat4& a);
};

enum class Axis {X, Y, Z};

mat4 transpose(const mat4& a);
mat4 inverse(const mat4& a);
float determinant(const mat4& a);

mat4 translation(const vec3 t);
mat4 scale(const vec3 s);
mat4 rotateAxis(float angle, Axis axis);

mat4 rotation(const vec3 r);
mat4 perspective(float fov, float aspect, float near, float far);

float degreesToRadians(float degrees);

} // Math

} // AsciiGL