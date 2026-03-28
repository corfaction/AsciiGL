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
    
public:

    void bindVBO(const VBO* vbo) { vertex_buffer = vbo; }
    void bindEBO(const EBO* ebo) { index_buffer = ebo; }
    
    void addAttribute(int index, int size, int offset) {
        attributes.push_back({index, size, offset});
        stride = std::max(stride, offset + size);
    }
    
    std::vector<float> getAttribute(int vertex_index, int attribute_index) const {
        std::vector<float> attr_data;
        if (!vertex_buffer) return attr_data;
        
        const auto& data = vertex_buffer->getData();
        
        for (const auto& attr : attributes) {
            if (attr.index == attribute_index) {
                size_t pos = vertex_index * stride + attr.offset;
                if (pos < data.size()) {
                    for(int num = pos; num < attr.size + pos; ++num) {
                        attr_data.push_back(data[num]);
                    }
                    return attr_data;
                }
            }
        }
        return attr_data;
    }
    
    bool hasEBO() const { return index_buffer != nullptr; }
    unsigned int getIndex(int i) const { 
        return index_buffer ? index_buffer->getData()[i] : i; 
    }
    size_t getAttributeCount() const { return attributes.size(); }

    size_t getVertexCount() const {
        return vertex_buffer->getData().size() / stride;
    }
};

} // AsciiGL