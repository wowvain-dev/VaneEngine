add_library(Renderer STATIC
        ${PROJECT_SOURCE_DIR}/src/glad.c
        Window.cpp
        GLRenderer.cpp
        DX11Renderer.cpp
        include/Window.h
        include/Renderer.h
        include/GLRenderer.h
        include/DX11Renderer.h
 "DX12Renderer.cpp" "include/DX12Renderer.h" "include/VKRenderer.h")

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

target_include_directories(Renderer PUBLIC
        "include/"
        "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(Renderer
        SDL2::SDL2
        SDL2::SDL2main
        fmt::fmt
        d3d12
        dxgi
        d3dcompiler
)