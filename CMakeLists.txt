cmake_minimum_required(VERSION 3.16)
project(AsciiGL)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(PLATFORM_FILES src/platform/terminal_windows.cpp)
else()
    set(PLATFORM_FILES src/platform/terminal_unix.cpp)
endif()

add_library(AsciiGL
    src/core/screen_buffer.cpp
    src/core/terminal.cpp
    src/core/renderer.cpp
    src/graphics/rasterizer.cpp
    src/graphics/shader_program.cpp
    src/graphics/uniform_manager.cpp
    src/math/mat.cpp
    src/math/vec.cpp
    src/math/color.cpp
    ${PLATFORM_FILES}
)

target_include_directories(AsciiGL PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(cube examples/cube.cpp)
target_link_libraries(cube PRIVATE AsciiGL)