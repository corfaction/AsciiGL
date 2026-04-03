![Гифка с кубом](cube.gif)

# 🎮 AsciiGL

AsciiGL is a lightweight C++ library for rendering 2D/3D graphics directly in the terminal using ASCII characters.

Instead of a GPU, the library uses the CPU and emulates a simplified graphics pipeline (similar to OpenGL), outputting the result directly to the console.

---

## ✨ Key Features

- 📦 OpenGL-like pipeline — a familiar graphics programming model
- 🧩 Custom shaders — full control over vertex and fragment stages
- 🖥️ Double buffering — smooth output without flickering
- ⚡ Diff rendering — only changed characters are updated for maximum performance
- 🔺 VAO / VBO / EBO — efficient geometry management
- 🎨 ASCII gradients — symbol "density" is determined by color brightness
- 🔄 Resize adaptation — automatic scaling to terminal window size
---

## 🧠 Architecture

### 🎛️ Renderer

The main control class that coordinates the entire rendering process:

```cpp
Renderer renderer;
renderer.setTarget(screen_buffer);
renderer.setShaderProgram(shader);
renderer.draw(vao, vertex_count);

```

Responsibilities:
- Running the vertex shader
- Rasterization
- Running the fragment shader

### VAO / VBO / EBO
- VBO — stores vertices
- EBO — stores indices
- VAO — describes the data layout

```cpp
vao->addAttribute(0, 3, 0); // position
vao->addAttribute(1, 3, 3); // color

```

### ShaderProgram

Example of creating a custom shader:

```cpp
class MyShader : public ShaderProgram {
public:
    MyShader() : ShaderProgram("MyShader") {}
    Vertex vertexShader(const std::vector<std::vector<float>>& attributes) const override {
        mat4 MVP = uniform_manager->getUniform<mat4>("MyShader", "MVP");
        Vertex vertex;
        vertex.clip_pos = ...
        return vertex;
    }

    void fragmentShader(Fragment& fragment) const override {
        vec3 color = uniform_manager->getUniform<vec3>("MyShader", "color");
        fragment.color = ...
    }
};

```

After that:

```cpp
auto shader = std::make_shared<MyShader>();
renderer.setShaderProgram(shader);

shader->setUniform<mat4>("MVP", mat4(1.0f));
shader->setUniform<vec3>("color", vec3(1.0f, 1.0f, 1.0f))
```

### Terminal

Abstraction over the terminal:

- Getting window size
- Outputting the buffer
- Handling resize

### ScreenBuffer

#### Double buffer:

back buffer — for rendering
front buffer — current terminal state
```cpp
screen_buffer.swap();
terminal.present(screen_buffer);
```

Optimization: only changed characters are output.

## 🧮 Mathematics

Built-in math library:

- vec2, vec3, vec4
- mat3, mat4

Transformations:

- Translation
- Rotation
- Scale
- Perspective

## 🎨 ASCII Gradient
" .,:;if|}]ILNMWB@"

The brighter the color — the "denser" the character.

## ⚙️ Installation
git clone https://github.com/your-repo/AsciiGL

## Include:

#include <AsciiGL/AsciiGL.hpp>

## 🧩 Quick Start
- Create a Terminal
- Create a ScreenBuffer
- Set up the Renderer
- Create VAO/VBO
- Write a shader
- Connect the shader

In the main loop:
- Set uniforms in the shader
- Clear the screenBuffer
- Call draw()
- Call swap()
- Output to the terminal

## 📁 A complete working example can be found in the repository:
examples/cube.cpp — a rotating 3D cube with camera and perspective projection like the GIF above

## 💡 Highlights
- 🔥 Fully CPU-based — no graphics accelerator required
- 📚 Great tool for learning computer graphics
- 🎪 Suitable for demoscene and ASCII art
- 🎮 Suitable for terminal games and visualizations

## Perfect for:
- Learning graphics
- Demoscene
- ASCII games
- Terminal visualizations

## 📌 TODO
- The ability to import your own textures and 3D models
- Multithreading support

### 🧑‍💻 Автор

A project made for learning and experimentation 🚀

## License: MIT License