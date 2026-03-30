#pragma once
#include "../../include/AsciiGL/math/mat.hpp"
#include "../../include/AsciiGL/math/vec.hpp"
#include <unordered_map>
#include <string>
#include <variant>

namespace AsciiGL {

using namespace Math;

using uniform_value = std::variant<
    float, vec2, vec3, vec4, ivec2, mat4, int,
    size_t, unsigned int 
>;

/**
 * Container for uniform variables associated with a single shader program.
 * 
 * UniformBlock stores a collection of named uniform values that are passed to
 * a shader program. Each uniform is identified by a string name and can hold
 * various types (scalars, vectors, matrices).
 * 
 * Features:
 * - Type-safe set() and get() operations with template methods
 * - Runtime type checking prevents invalid type conversions
 * - Iteration over all uniform names
 * - Individual uniform removal and batch clearing
 */

class UniformBlock {
private:

    std::unordered_map<std::string, uniform_value> uniforms;

public:
    
    bool has(const std::string& name) const;
    void remove(const std::string& name);
    void clear();
    
    std::vector<std::string> getNames() const;

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
};

/**
 * Central manager for uniform blocks across multiple shader programs.
 * 
 * UniformManager maintains a collection of UniformBlock objects, each associated
 * with a named shader program. This allows each shader to have its own independent
 * set of uniforms while providing a unified interface for accessing them.
 * 
 * Features:
 * - Per-shader uniform blocks identified by shader name
 * - Type-safe uniform access through template methods
 * - Automatic block creation when accessing new shaders
 * - Batch operations (clear all, remove shader)
 */

class UniformManager {
private:

    std::unordered_map<std::string, UniformBlock> shaders_uniforms;

public:

    UniformBlock& getShaderBlock(const std::string& shader_name);
    
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
    
    bool hasShader(const std::string& shader_name) const;
    bool hasUniform(const std::string& shader_name, const std::string& uniform_name) const;
    void removeShader(const std::string& shader_name);
    void clearAll();
    
    std::vector<std::string> getShaderNames() const;
};

} // AsciiGL