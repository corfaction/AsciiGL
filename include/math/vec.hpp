#pragma once

namespace AsciiGL {

struct vec2 {
    float x, y;

    vec2() : x(0.0f), y(0.0f) {}
    vec2(float i_x, float i_y) : x(i_x), y(i_y) {}

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

struct vec3 {
    float x, y, z;

    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float i_x, float i_y, float i_z) : x(i_x), y(i_y), z(i_z) {}

    vec3 operator*(const vec3& a) const {
        return vec3(a.x * x, a.y * y, a.z * z);
    }

    vec3 operator*(const float& a) const {
        return vec3(x * a, y * a, z * a);
    }

    vec3 operator+(const vec3& a) const {
        return vec3(a.x + x, a.y + y, a.z + z);
    }
};

struct vec4 {
    float x, y, z, w;

    vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    vec4(float i_x, float i_y, float i_z, float i_w) : x(i_x), y(i_y), z(i_z), w(i_w) {}

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
    ivec2(int i_x, int i_y) : x(i_x), y(i_y) {}


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

}
