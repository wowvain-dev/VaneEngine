# Vane Engine (IN DEVELOPMENT)

A 2D/3D game engine written in C++ with Vulkan/D3D11/D3D12/OpenGL support and a ~~Qt~~ImGui-based editor.

It uses ~~CMake~~ Premake5 as build system for cross-platform support.

It allows cross-compilation.

## Goal

Mostly educational but planning to be serious about it. I would like it to be my main project for a while and be the engine that I use for most of my games.

## Documentation

### Work in progress.

## Components
- **Vane**: The main engine, should compile to a DLL and be used as a library.
- **VaneEditor**: The editor of the engine, will link with Vane. Uses ~~Qt~~ ImGui.
- **Sandbox**: A testbed for the engine.

## Installation

The installation / build process is highly unstable at the moment as I am still figuring some stuff out with Premake5 and vcpkg. If it doesn't work, create an issue and I might be able to help.

### Pre-build binaries

#### Work in progress. Will support Linux & Windows with full testing. I am developing with macOS in mind but I do not own a Mac so it will be untested.

### Build it yourself

#### Windows

1. Clone the repository: `git clone https://github.com/wowvain-dev/VaneEngine`
2. Install `vcpkg` from: https://github.com/microsoft/vcpkg
3. Set the `VCPKG_ROOT` environment variable to where you cloned the `vcpkg` repo.
4. Make sure to download `Premake5` from https://premake.github.io/download and Lua from https://www.lua.org/download.html (also make sure to put them somewhere on the %PATH% env variable)
5. Make sure you have the `gcc/g++` compiler installed / the VS2022 build tools.
6. Run `premake5 vs2022` (haven't tested VS2017 build config yet, will do)
7. Run ~~`make`~~. Compile from Visual Studio solution.
8. The binaries will be found in `build/[triplet]/{Sandbox | VaneEngine | Vane}` 

#### Linux

Most of the steps are the same as on Windows. 

Use gmake instead of vs2022 on premake.
Build with `make`. 

With my current setup its a bit hard to consistently test both Windows and Linux, but I'll keep both as up-to-date as I can.

Extra dependencies: [***WORK IN PROGRESS***]

For now you can just run `premake5 gmake` and see what build fails, find the lib missing which caused the failure, install it, and repeat until it fully builds.

