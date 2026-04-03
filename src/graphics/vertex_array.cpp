#include "../../include/AsciiGL/graphics/vertex_array.hpp"
#include <algorithm>
#include <vector>

using namespace AsciiGL;

std::vector<float> VAO::extractAttributeData(const Attribute& attr, size_t vertex_index) const {
    std::vector<float> attr_data;
    size_t pos = vertex_index * stride + attr.offset;
    
    if (pos < vertex_buffer->getData().size()) {
        const auto& data = vertex_buffer->getData();
        attr_data.reserve(attr.size);
        for (size_t num = pos; num < attr.size + pos; ++num) {
            attr_data.push_back(data[num]);
        }
    }
    return attr_data;
}
    
void VAO::addAttribute(int index, int size, int offset) {
    attributes.push_back({index, size, offset});
    stride = std::max(stride, offset + size);
}
    
std::vector<float> VAO::getAttribute(int vertex_index, int attribute_index) const {
    if (!vertex_buffer) return {};
    
    const auto& data = vertex_buffer->getData();

    // if attributes were assigned an index equal to their actual index in the attribute array
    // for example: addAttribute(0, 3, 0); add Attribute(1, 3, 3)

    if(attributes[attribute_index].index == attribute_index) {
        return extractAttributeData(attributes[attribute_index], vertex_index);
    }

    // if attribute indices were added out of order
    // for example: addAttribute(23, 3, 0); add Attribute(10, 3, 3);
    
    for (const auto& attr : attributes) {
        if (attr.index == attribute_index) {
            return extractAttributeData(attr, vertex_index);
        }
    }
    return {};
}
    
unsigned int VAO::getIndex(int i) const { 
    return index_buffer ? index_buffer->getData()[i] : i; 
}

size_t VAO::getVertexCount() const {
    return vertex_buffer->getData().size() / stride;
}