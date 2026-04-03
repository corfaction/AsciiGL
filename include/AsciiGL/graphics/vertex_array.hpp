#pragma once
#include "buffer.hpp"
#include <algorithm>
#include <vector>

namespace AsciiGL {

struct Attribute {
    int index;
    int size; 
    int offset; 
};

/**
 * Vertex Array Object that defines how vertex data is interpreted.
 * 
 * VAO stores the layout of vertex attributes within a VBO and optionally
 * associates an EBO for indexed rendering.
 * 
 * Key responsibilities:
 * - Defines attribute layout (stride, offsets, sizes)
 * - Associates VBO with vertex data
* - Optionally associates EBO for indexed drawing
 * - Provides methods to extract per-vertex attribute data
 */

class VAO {
private:

    int stride = 0;
    const VBO* vertex_buffer = nullptr;
    const EBO* index_buffer = nullptr;
    std::vector<Attribute> attributes;

    std::vector<float> extractAttributeData(const Attribute& attr, size_t vertex_index) const;
    
public:

    void bindVBO(const VBO* vbo) { vertex_buffer = vbo; }
    void bindEBO(const EBO* ebo) { index_buffer = ebo; }
    
    void addAttribute(int index, int size, int offset);
    
    std::vector<float> getAttribute(int vertex_index, int attribute_index) const;
    
    bool hasEBO() const { return index_buffer != nullptr; }

    unsigned int getIndex(int i) const;

    size_t getAttributeCount() const { return attributes.size(); }

    size_t getVertexCount() const;
};

} // AsciiGL