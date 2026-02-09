#include "vec.hpp"
#include <stdexcept>

namespace console3d {
    struct mat4 {
        vec4 m[4];

        mat4(const vec4& x, const vec4& y, const vec4& z, const vec4& w) {
            m[0] = x;
            m[1] = y;
            m[2] = z;
            m[3] = w;
        }

        mat4() {
            m[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
            m[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
            m[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
            m[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        }

        float& operator()(int col, int row) {
            if(col >= 4 || col < 0) 
                throw std::out_of_range("Index col out of range");

            switch(row) {
                case 1: return m[col].x;
                case 2: return m[col].y;
                case 3: return m[col].z;
                case 4: return m[col].w;
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
            return mat4(vec4(*this * a.m[0]),
                        vec4(*this * a.m[1]),
                        vec4(*this * a.m[2]),
                        vec4(*this * a.m[3]));
        }

    };

}
