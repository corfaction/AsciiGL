#pragma once
#include "vec.hpp"
#include <stdexcept>
#include <cmath>

namespace AsciiGL {

struct mat4 {
    vec4 m[4];

    mat4(const vec4& r0, const vec4& r1, const vec4& r2, const vec4& r3) {
        m[0] = r0;
        m[1] = r1;
        m[2] = r2;
        m[3] = r3;
    }

    mat4() {
        m[0] = vec4();
        m[1] = vec4();
        m[2] = vec4();
        m[3] = vec4();
    }

    mat4(float diag) {
        m[0] = vec4(diag, 0, 0, 0);
        m[1] = vec4(0, diag, 0, 0);
        m[2] = vec4(0, 0, diag, 0);
        m[3] = vec4(0, 0, 0, diag);
    }

    float& operator()(int row, int col) {
        if (row < 0 || row >= 4 || col < 0 || col >= 4)
            throw std::out_of_range("Index out of range");

        switch (col) {
            case 0: return m[row].x;
            case 1: return m[row].y;
            case 2: return m[row].z;
            case 3: return m[row].w;
        }

        throw std::out_of_range("Invalid column");
    }

    const float& operator()(int row, int col) const {
        if (row < 0 || row >= 4 || col < 0 || col >= 4)
            throw std::out_of_range("Index out of range");

        switch (col) {
            case 0: return m[row].x;
            case 1: return m[row].y;
            case 2: return m[row].z;
            case 3: return m[row].w;
        }

        throw std::out_of_range("Invalid column");
    }

    vec4 operator*(const vec4& v) const {
        return vec4(
            m[0].x * v.x + m[0].y * v.y + m[0].z * v.z + m[0].w * v.w,
            m[1].x * v.x + m[1].y * v.y + m[1].z * v.z + m[1].w * v.w,
            m[2].x * v.x + m[2].y * v.y + m[2].z * v.z + m[2].w * v.w,
            m[3].x * v.x + m[3].y * v.y + m[3].z * v.z + m[3].w * v.w
        );
    }

    mat4 operator*(const mat4& a) const {
        mat4 result(0.0f);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result(i, j) += (*this)(i, k) * a(k, j);
                }
            }
        }

        return result;
    }

    void operator*=(const mat4& a) {
        *this = *this * a;
    }
};

namespace matrix {

    enum class Axis {X, Y, Z};

    inline mat4 translation(const vec3 t) {
        mat4 m(1.0f);
        m(0, 3) = t.x;
        m(1, 3) = t.y;
        m(2, 3) = t.z;
        return m;
    }

    inline mat4 scale(const vec3 s) {
        mat4 m(1.0f);
        m(0, 0) = s.x;
        m(1, 1) = s.y;
        m(2, 2) = s.z;
        return m;
    }

    inline mat4 rotateAxis(float angle, Axis axis) {
        if(axis == Axis::X) {
            mat4 rotate_x(1.0f);
            rotate_x(1, 1) =  cos(angle);
            rotate_x(1, 2) = -sin(angle);
            rotate_x(2, 1) =  sin(angle);
            rotate_x(2, 2) =  cos(angle);
            return rotate_x;
        }
        if(axis == Axis::Y) {
            mat4 rotation_y(1.0f);
            rotation_y(0, 0) =  cos(angle);
            rotation_y(0, 2) =  sin(angle);
            rotation_y(2, 0) = -sin(angle);
            rotation_y(2, 2) =  cos(angle);

            return rotation_y;
        }
        if(axis == Axis::Z) {
            mat4 rotation_z(1.0f);
            rotation_z(0, 0) =  cos(angle);
            rotation_z(0, 1) = -sin(angle);
            rotation_z(1, 0) =  sin(angle);
            rotation_z(1, 1) =  cos(angle);

            return rotation_z;
        }
        return mat4();
    }

    inline mat4 rotation(const vec3 r) {
        return rotateAxis(r.z, Axis::Z) * rotateAxis(r.y, Axis::Y) * rotateAxis(r.x, Axis::X);
    }

    inline mat4 perspective(float fov, float aspect, float near, float far) {
    float tanHalfFov = tan(fov / 2.0f);
    
    mat4 result(0.0f);
    
    result(0, 0) = 1.0f / (aspect * tanHalfFov);
    result(1, 1) = 1.0f / tanHalfFov;
    result(2, 2) = -(far + near) / (far - near);
    result(2, 3) = -(2.0f * far * near) / (far - near);
    result(3, 2) = -1.0f;
    
    return result;
}

}

}
