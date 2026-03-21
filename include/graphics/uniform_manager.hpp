#pragma once
#include "../math/mat.hpp"
#include "../math/vec.hpp"
#include "graphics_types.hpp"
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <variant>

namespace AsciiGL {

using uniform_value = std::variant<
    float, vec2, vec3, vec4, ivec2, mat4, int,
    size_t, unsigned int 
>;

class UniformBlock {
private:

    std::unordered_map<std::string, uniform_value> uniforms;

public:
    template<typename T>
    void set(const std::string& name, const T& value) {
        uniforms[name] = uniform_value(value);
    }
    
    template<typename T>
    T get(const std::string& name) const {
        auto it = uniforms.find(name);
        if (it == uniforms.end()) {
            throw std::runtime_error("Uniform not found: " + name);
        }
        
        try {
            return std::get<T>(it->second);
        } catch (const std::bad_variant_access&) {
            throw std::runtime_error("Uniform type mismatch: " + name);
        }
    }
    
    bool has(const std::string& name) const {
        return uniforms.find(name) != uniforms.end();
    }
    
    void remove(const std::string& name) {
        uniforms.erase(name);
    }
    
    void clear() {
        uniforms.clear();
    }
    
    std::vector<std::string> getNames() const {
        std::vector<std::string> names;
        for (const auto& [name, _] : uniforms) {
            names.push_back(name);
        }
        return names;
    }
};

class UniformManager {
private:

    std::unordered_map<std::string, UniformBlock> shaders_uniforms;

public:

    UniformBlock& getShaderBlock(const std::string& shader_name) {
        return shaders_uniforms[shader_name];
    }
    
    template<typename T>
    void setUniform(const std::string& shader_name, const std::string& uniform_name, const T& value) {
        shaders_uniforms[shader_name].set(uniform_name, value);
    }
    
    template<typename T>
    T getUniform(const std::string& shader_name, const std::string& uniform_name) const {
        auto it = shaders_uniforms.find(shader_name);
        if (it == shaders_uniforms.end()) {
            throw std::runtime_error("Shader not found: " + shader_name);
        }
        return it->second.get<T>(uniform_name);
    }
    
    bool hasShader(const std::string& shader_name) const {
        return shaders_uniforms.find(shader_name) != shaders_uniforms.end();
    }
    
    bool hasUniform(const std::string& shader_name, const std::string& uniform_name) const {
        auto it = shaders_uniforms.find(shader_name);
        if (it == shaders_uniforms.end()) return false;
        return it->second.has(uniform_name);
    }
    
    void removeShader(const std::string& shader_name) {
        shaders_uniforms.erase(shader_name);
    }
    
    void clearAll() {
        shaders_uniforms.clear();
    }
    
    std::vector<std::string> getShaderNames() const {
        std::vector<std::string> names;
        for (const auto& [name, _] : shaders_uniforms) {
            names.push_back(name);
        }
        return names;
    }
};

}