#include "uniform_manager.hpp"
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <variant>

namespace AsciiGL {

using namespace Math;
    
bool UniformBlock::has(const std::string& name) const {
    return uniforms.find(name) != uniforms.end();
}
    
void UniformBlock::remove(const std::string& name) {
    uniforms.erase(name);
}
    
void UniformBlock::clear() {
    uniforms.clear();
}
    
std::vector<std::string> UniformBlock::getNames() const {
    std::vector<std::string> names;
    for (const auto& [name, _] : uniforms) {
        names.push_back(name);
    }
    return names;
}

UniformBlock& UniformManager::getShaderBlock(const std::string& shader_name) {
    return shaders_uniforms[shader_name];
}
    
bool UniformManager::hasShader(const std::string& shader_name) const {
    return shaders_uniforms.find(shader_name) != shaders_uniforms.end();
}
    
bool UniformManager::hasUniform(const std::string& shader_name, const std::string& uniform_name) const {
    auto it = shaders_uniforms.find(shader_name);
    if (it == shaders_uniforms.end()) return false;
    return it->second.has(uniform_name);
}
    
void UniformManager::removeShader(const std::string& shader_name) {
    shaders_uniforms.erase(shader_name);
}
    
void UniformManager::clearAll() {
    shaders_uniforms.clear();
}
    
std::vector<std::string> UniformManager::getShaderNames() const {
    std::vector<std::string> names;
    for (const auto& [name, _] : shaders_uniforms) {
        names.push_back(name);
    }
    return names;
}

} // AsciiGL