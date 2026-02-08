cmake_minimum_required(VERSION 3.16)
project(console3D)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_executable(console3D
        examples/cube.cpp
        src/core/screen_buffer.cpp
        src/core/terminal.cpp
        src/platform/terminal_windows.cpp
    )

else()
    add_executable(console3D
        examples/cube.cpp
        src/core/screen_buffer.cpp
        src/core/terminal.cpp
        src/platform/terminal_linux.cpp
    )

endif()
