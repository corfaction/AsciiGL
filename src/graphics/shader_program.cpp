#include "../../include/graphics/shader_program.hpp"
#include "../../include/math/mat.hpp"
#include <memory>
#include <string>

namespace AsciiGL {

using namespace Math;

ShaderProgram::ShaderProgram(const std::string& program_name) : 
    name(program_name), 
    uniform_manager(std::make_shared<UniformManager>()) 
{}
    
void ShaderProgram::setUniformManager(std::shared_ptr<UniformManager> manager) {
    uniform_manager = manager;
}
    
bool ShaderProgram::hasUniform(const std::string& uniform_name) const {
    return uniform_manager && uniform_manager->hasUniform(name, uniform_name);
}


// implementation of a default shader

Vertex DefaultShader::vertexShader(const std::vector<std::vector<float>>& attributes) const {
    mat4 MVP = uniform_manager->getUniform<mat4>("defaultShader", "MVP");
        
    Vertex vertex;
    vertex.clip_pos = MVP * vec4(vec3(attributes[0]), 1.0f);

    vertex.color = vec4(vec3(attributes[1]), 1.0f);

    return vertex;
}

void DefaultShader::fragmentShader(Fragment& fragment) const {
        fragment.color = Color(fragment.vertex_color);
}



} // AsciiGL
