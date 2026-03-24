#pragma once
#include <vector>
#include <cmath>

namespace AsciiGL {

struct vec2 {
    float x, y;

    vec2() : x(0.0f), y(0.0f) {}
    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator*(const vec2& a) const {
        return vec2(a.x * x, a.y * y);
    }

    vec2 operator*(const float& a) const {
        return vec2(x * a, y * a);
    }

    vec2 operator+(const vec2& a) const {
        return vec2(a.x + x, a.y + y);
    }
};

struct vec4;

struct vec3 {
    float x, y, z;

    vec3(float a) : x(a), y(a), z(a) {}
    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    vec3(const std::vector<float>& xyz) {
        if(xyz.size() > 2) {
            x = xyz[0]; y = xyz[1]; z = xyz[2];   
        }
    }

    vec3(const vec4& v);

    vec3 operator*(const vec3& a) const {
        return vec3(a.x * x, a.y * y, a.z * z);
    }

    vec3 operator*(const float& a) const {
        return vec3(x * a, y * a, z * a);
    }

    vec3 operator+(const vec3& a) const {
        return vec3(a.x + x, a.y + y, a.z + z);
    }

    vec3 operator-(const vec3& a) const {
        return vec3(a.x - x, a.y - y, a.z - z);
    }
};

inline float dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float length(const vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vec3 normalize(const vec3& v) {
    float len = length(v);
    if (len == 0.0f) return v;
    return { v.x / len, v.y / len, v.z / len };
}

struct vec4 {
    float x, y, z, w;

    vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    vec4(vec3 xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {} 

    vec4 operator*(const vec4& a) const {
        return vec4(a.x * x, a.y * y, a.z * z, a.w * w);
    }

    vec4 operator*(const float& a) const {
        return vec4(x * a, y * a, z * a, w * a);
    }

    vec4 operator+(const vec4& a) const {
        return vec4(a.x + x, a.y + y, a.z + z, a.w + w);
    }
};

struct ivec2 {
    int x, y;

    ivec2() : x(0), y(0) {}
    ivec2(int x, int y) : x(x), y(y) {}


    ivec2 operator*(const ivec2 a) const {
        return ivec2(a.x * x, a.y * y);
    }

    ivec2 operator*(const float& a) const {
        return ivec2(x * a, y * a);
    }

    ivec2 operator+(const ivec2& a) const {
        return ivec2(x + a.x, y + a.y);
    }
};

inline vec3::vec3(const vec4& v) : x(v.x), y(v.y), z(v.z) {}

}
