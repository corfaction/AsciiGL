#pragma once
#include "graphics_types.hpp"
#include "uniform_manager.hpp"
#include <memory>
#include <string>

namespace AsciiGL {
/**
 * The rendering pipeline flow:
 * 1. Vertex shader transforms each vertex (position, attributes)
 * 2. Rasterizer interpolates attributes across primitives
 * 3. Fragment shader determines final color for each fragment
 * 
 * Example implementation:

class ExampleShader : public ShaderProgram {
public:
    ExampleShader() : ShaderProgram("ExampleShader") {}
    Vertex vertexShader(const std::vector<std::vector<float>>& attributes) const override {
        mat4 MVP = uniform_manager->getUniform<mat4>("ExampleShader", "MVP");
        Vertex vertex;
        vertex.clip_pos = MVP * vec4(vec3(attributes[0]), 1.0f);
        return vertex;
    }

    virtual void fragmentShader(Fragment& fragment) const override {
        vec3 color = uniform_manager->getUniform<vec3>("ExampleShader", "color");
        fragment.color = Color(vec4(color, 1.0f));
    }
}; 
*/

class ShaderProgram {
protected:
    std::string name;
    std::shared_ptr<UniformManager> uniform_manager;

public:
    ShaderProgram(const std::string& program_name = "default");
    
    virtual ~ShaderProgram() = default;
    
    const std::string& getName() const { return name; }
    
    void setUniformManager(std::shared_ptr<UniformManager> manager);
    
    bool hasUniform(const std::string& uniform_name) const;
    
    virtual Vertex vertexShader(const std::vector<std::vector<float>>& attributes) const = 0;
    virtual void fragmentShader(Fragment& fragment) const = 0;

    template<typename T>
    void setUniform(const std::string& uniform_name, const T& value) {
        if (uniform_manager) {
            uniform_manager->setUniform(name, uniform_name, value);
        }
    }
    
    template<typename T>
    T getUniform(const std::string& uniform_name) const {
        if (!uniform_manager) {
            throw std::runtime_error("Uniform manager not set");
        }
        return uniform_manager->getUniform<T>(name, uniform_name);
    }
    
};

// default shader declaration

class DefaultShader : public ShaderProgram {
public:

    DefaultShader() : AsciiGL::ShaderProgram("defaultShader") {}

    Vertex vertexShader(const std::vector<std::vector<float>>& attributes) const override;

    virtual void fragmentShader(Fragment& fragment) const override;

};

} // AsciiGL
