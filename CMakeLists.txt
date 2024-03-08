cmake_minimum_required(VERSION 3.28)
project(VaneEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

add_subdirectory(extern/SDL2)
add_subdirectory(src/Renderer)

add_executable(VaneEngine
        src/main.cpp
        src/glad.c
)

target_include_directories(VaneEngine PUBLIC
        "include/"
        "src/Renderer/include/"
)


target_link_libraries(VaneEngine
        SDL2::SDL2
        SDL2::SDL2main
        Renderer
        d3d12
        dxgi
        d3dcompiler
)
