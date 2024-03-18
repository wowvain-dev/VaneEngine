cmake_minimum_required(VERSION 3.24)
project(Vane CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(VulkanHeaders CONFIG)
# find_package(VulkanMemoryAllocator CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_library(Vane STATIC
        entry.cpp
        entry.h
)

set_target_properties(Vane PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Vane PRIVATE
    fmt::fmt

    Vulkan::Vulkan
    Vulkan::Headers
    # GPUOpen::VulkanMemoryAllocator

    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

message("Loading Vane...")