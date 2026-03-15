#include "vec.hpp"
#include <stdexcept>
#include <cmath>

namespace AsciiGL {
    
struct mat4 {
    vec4 m[4];

    mat4(const vec4& x, const vec4& y, const vec4& z, const vec4& w) {
        m[0] = x;
        m[1] = y;
        m[2] = z;
        m[3] = w;
    }

    mat4() {
        m[0] = vec4();
        m[1] = vec4();
        m[2] = vec4();
        m[3] = vec4();
    }

    mat4(float num) {
        m[0] = vec4(num, 0.0f, 0.0f, 0.0f);
        m[1] = vec4(0.0f, num, 0.0f, 0.0f);
        m[2] = vec4(0.0f, 0.0f, num, 0.0f);
        m[3] = vec4(0.0f, 0.0f, 0.0f, num);
    }

    float& operator()(int col, int row) {
        if(col >= 4 || col < 0) 
            throw std::out_of_range("Index col out of range");

        switch(row) {
            case 0: return m[col].x;
            case 1: return m[col].y;
            case 2: return m[col].z;
            case 3: return m[col].w;
        }

        throw std::out_of_range("Index row out of range");
    }

    vec4 operator*(const vec4& a) const {
        return
            m[0] * a.x +
            m[1] * a.y +
            m[2] * a.z +
            m[3] * a.w;
    }

    mat4 operator*(const mat4& a) const {
        return mat4 (
            vec4(*this * a.m[0]),
            vec4(*this * a.m[1]),
            vec4(*this * a.m[2]),
            vec4(*this * a.m[3])
        );
    }

    void operator*=(const mat4& a) {
        mat4 new_matrix = *this * a;
        *this = new_matrix;
    }

};

namespace matrix {

    enum class Axis {X, Y, Z};

    mat4 translation(const vec3 coordinates) {
        mat4 translation_matrix(1.0f);
        translation_matrix(3, 0) = coordinates.x;
        translation_matrix(3, 1) = coordinates.y;
        translation_matrix(3, 2) = coordinates.z;
        return translation_matrix;
    }

    mat4 scale(const vec3 size) {
        mat4 scale_matrix(1.0f);
        scale_matrix(0, 0) = size.x;
        scale_matrix(1, 1) = size.y;
        scale_matrix(2, 2) = size.z;
        return scale_matrix;
    }

    mat4 rotateAxis(float angle, Axis axis) {
        if(axis == Axis::X) {
            mat4 rotation_x(1.0f);
            rotation_x(1, 1) =  std::cos(angle);
            rotation_x(2, 1) = -std::sin(angle);
            rotation_x(1, 2) =  std::sin(angle);
            rotation_x(2, 2) =  std::cos(angle);

            return rotation_x;
        }
        if(axis == Axis::Y) {
            mat4 rotation_y(1.0f);
            rotation_y(0, 0) =  std::cos(angle);
            rotation_y(0, 2) = -std::sin(angle);
            rotation_y(2, 0) =  std::sin(angle);
            rotation_y(2, 2) =  std::cos(angle);

            return rotation_y;
        }
        if(axis == Axis::Z) {
            mat4 rotation_z(1.0f);
            rotation_z(0, 0) =  std::cos(angle);
            rotation_z(1, 0) = -std::sin(angle);
            rotation_z(0, 1) =  std::sin(angle);
            rotation_z(1, 1) =  std::cos(angle);

            return rotation_z;
        }
        return mat4();
    }

    mat4 rotation(const vec3 rotate) {
        mat4 rotation_matrix(1.0f);

        rotation_matrix *= rotateAxis(rotate.x, Axis::X);
        rotation_matrix *= rotateAxis(rotate.y, Axis::Y);
        rotation_matrix *= rotateAxis(rotate.z, Axis::Z);

        return rotation_matrix;
    }

    mat4 perspective(float fov, float aspect, float near, float far) {
        mat4 perspective_matrix;
    
        float tanHalfFov = std::tan(fov / 2.0f);
    
        perspective_matrix(0, 0) = 1.0f / (aspect * tanHalfFov);
        perspective_matrix(1, 1) = 1.0f / tanHalfFov;
        perspective_matrix(2, 2) = -(far + near) / (far - near);
        perspective_matrix(2, 3) = -1.0f;
        perspective_matrix(3, 2) = -(2.0f * far * near) / (far - near);
    
        return perspective_matrix;
    }

}

}
