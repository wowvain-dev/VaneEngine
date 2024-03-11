cmake_minimum_required(VERSION 3.28)

project(VaneEngine VERSION 0.0.1)

message("START OF CMAKELIST...")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

# CHOOSING THE RENDERER
add_definitions(-DUSE_OPENGL)
#add_definitions(-DUSE_DIRECTX)

add_subdirectory(extern/SDL2)
add_subdirectory(extern/fmt)

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
        fmt::fmt
        Renderer
        d3d11
        dxguid
        d3dcompiler
        dxgi
)

message("END OF CMAKELIST...")
