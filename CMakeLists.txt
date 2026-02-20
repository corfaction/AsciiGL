cmake_minimum_required(VERSION 3.16)
project(AskiiGL)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(PLATFORM_FILES src/platform/terminal_windows.cpp)
else()
    set(PLATFORM_FILES src/platform/terminal_linux.cpp)
endif()

add_executable(AsciiGL
    examples/cube.cpp
    src/core/screen_buffer.cpp
    src/core/terminal.cpp
    src/platform/terminal_windows.cpp
    src/core/renderer.cpp
    src/graphics/rasterizer.cpp
)
