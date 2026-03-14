#pragma once
#include <vector>

namespace AsciiGL {

class VBO {
private:
    std::vector<float> data;
public:
    void setData(const std::vector<float>& input_data) { data = input_data; }
    const std::vector<float>& getData() const { return data; }
    int getSize() {return data.size();}
};

class EBO {
private:
    std::vector<unsigned int> indices;
public:
    void setData(const std::vector<unsigned int>& input_indices) { indices = input_indices; }
    const std::vector<unsigned int>& getData() const { return indices; }
    size_t getSize() const { return indices.size(); }
};

}