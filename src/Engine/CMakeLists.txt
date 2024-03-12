add_library(Engine STATIC
        ${PROJECT_SOURCE_DIR}/src/glad.c
        Engine.cpp
        include/Engine.h
        EngineConfig.cpp
        include/EngineConfig.h
)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

target_include_directories(Engine PUBLIC
        "include/"
        "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(Engine
        tomlplusplus::tomlplusplus
        SDL2::SDL2
        SDL2::SDL2main
        fmt::fmt
        Renderer
)