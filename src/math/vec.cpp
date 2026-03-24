#include "../../include/math/vec.hpp"

namespace AsciiGL {

namespace Math {

vec2::vec2() : x(0.0f), y(0.0f) {}
vec2::vec2(float x, float y) : x(x), y(y) {}

vec2 vec2::operator*(const vec2& a) const {
    return vec2(a.x * x, a.y * y);
}

vec2 vec2::operator*(const float& a) const {
    return vec2(x * a, y * a);
}

vec2 vec2::operator+(const vec2& a) const {
    return vec2(a.x + x, a.y + y);
}

vec2 vec2::operator-(const vec2& a) const {
    return vec2(x - a.x, y - a.y);
}

float dot(const vec2& a, const vec2& b) {
    return a.x * b.x + a.y * b.y;
}

float length(const vec2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

vec2 normalize(const vec2& v) {
    float len = length(v);
    if (len == 0.0f) return v;
    return { v.x / len, v.y / len};
}


vec3::vec3(float a) : x(a), y(a), z(a) {}
vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {}
vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}
vec3::vec3(const vec4& v) : x(v.x), y(v.y), z(v.z) {}

vec3::vec3(const std::vector<float>& xyz) {
    if(xyz.size() > 2) {
        x = xyz[0]; y = xyz[1]; z = xyz[2];   
    }
}

vec3 vec3::operator*(const vec3& a) const {
    return vec3(a.x * x, a.y * y, a.z * z);
}

vec3 vec3::operator*(const float& a) const {
    return vec3(x * a, y * a, z * a);
}

vec3 vec3::operator+(const vec3& a) const {
    return vec3(a.x + x, a.y + y, a.z + z);
}

vec3 vec3::operator-(const vec3& a) const {
    return vec3(x - a.x, y - a.y, z - a.z);
}

float dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length(const vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 normalize(const vec3& v) {
    float len = length(v);
    if (len == 0.0f) return v;
    return { v.x / len, v.y / len, v.z / len };
}


vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
vec4::vec4(vec3 xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {} 

vec4 vec4::operator*(const vec4& a) const {
    return vec4(a.x * x, a.y * y, a.z * z, a.w * w);
}

vec4 vec4::operator*(const float& a) const {
    return vec4(x * a, y * a, z * a, w * a);
}

vec4 vec4::operator+(const vec4& a) const {
    return vec4(a.x + x, a.y + y, a.z + z, a.w + w);
}

vec4 vec4::operator-(const vec4& a) const {
    return vec4(x - a.x, y - a.y, z - a.z, w - a.w);
}

float dot(const vec4& a, const vec4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float length(const vec4& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec4 normalize(const vec4& v) {
    float len = length(v);
    if (len == 0.0f) return v;
    return { v.x / len, v.y / len, v.z / len, v.w / len };
}


ivec2::ivec2() : x(0), y(0) {}
ivec2::ivec2(int x, int y) : x(x), y(y) {}

ivec2 ivec2::operator*(const ivec2 a) const {
    return ivec2(a.x * x, a.y * y);
}

ivec2 ivec2::operator*(const float& a) const {
    return ivec2(x * a, y * a);
}

ivec2 ivec2::operator+(const ivec2& a) const {
    return ivec2(x + a.x, y + a.y);
}

}

}
