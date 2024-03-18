# Vane Engine (IN DEVELOPMENT)

A 2D/3D game engine written in C++ with Vulkan/D3D11/D3D12/OpenGL support and a Qt-based editor.

It uses CMake as build system for cross-platform support.

It allows cross-compilation.

## Goal

Mostly educational but planning to be serious about it. I would like it to be my main project for a while and be the engine that I use for most of my games.

## Components
- **Vane**: The main engine, should compile to a DLL and be used as a library.
- **VaneEditor**: The editor of the engine, will link with Vane. Uses Qt.
- **Sandbox**: A testbed for the engine.

## Installation

The installation / build process is highly unstable at the moment as I am still figuring some stuff out with CMake and vcpkg. If it doesn't work, create an issue and I might be able to help. 

### Windows 

1. Clone the repository: `git clone https://github.com/wowvain-dev/VaneEngine`
2. Install `vcpkg` from: `https://github.com/microsoft/vcpkg`
3. Set the `VCPKG_ROOT` environment variable to where you cloned the `vcpkg` repo.
4. Make sure CMake is properly installed. Required version >= 3.24
5. Run `cmake --preset=MSVC` in the root directory of VaneEngine (you need Visual Studio 2022 properly installed with the appropriate C++ development build tools)
6. Run `cmake --build build/` in the root directory of VaneEngine.
7. You can now find the binaries in:
   - `build/msvc-x64/Vane/`
   - `build/msvc-x64/VaneEditor/`
   - `build/msvc-x64/Sandbox/`
