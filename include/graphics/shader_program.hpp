#pragma once
#include "graphics_types.hpp"
#include "uniform_manager.hpp"
#include <string>

namespace AsciiGL {

class ShaderProgram {
protected:
    std::string name;
    std::shared_ptr<UniformManager> uniform_manager;

public:
    ShaderProgram(const std::string& program_name = "default")
        : name(program_name), uniform_manager(std::make_shared<UniformManager>()) {}
    
    virtual ~ShaderProgram() = default;
    
    const std::string& getName() const { return name; }
    
    void setUniformManager(std::shared_ptr<UniformManager> manager) {
        uniform_manager = manager;
    }
    
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
    
    bool hasUniform(const std::string& uniform_name) const {
        return uniform_manager && uniform_manager->hasUniform(name, uniform_name);
    }
    
    virtual Vertex vertexShader(const std::vector<std::vector<float>>& attributes) const = 0;
    virtual void fragmentShader(Fragment& fragment) const = 0;
    
};

class DefaultShader : public ShaderProgram {
public:

    DefaultShader() : AsciiGL::ShaderProgram("defaultShader") {}

    Vertex vertexShader(const std::vector<std::vector<float>>& attributes) const override {
        mat4 MVP = uniform_manager->getUniform<mat4>("defaultShader", "MVP");
        
        Vertex vertex;
        vertex.pos = vec4(vec3(attributes[0]), 1.0f);
        vertex.pos = MVP * vertex.pos;

        vertex.color = vec4(vec3(attributes[1]), 1.0f);

        return vertex;
    }

    virtual void fragmentShader(Fragment& fragment) const override {
        fragment.color = Color(fragment.vertex_color);
    }

};

}
