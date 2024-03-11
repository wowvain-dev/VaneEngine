#include <DX11Renderer.h>
#include <SDL2/SDL.h>
#include <fmt/core.h>
#include <iostream>

using namespace Vane;

DX11Renderer::~DX11Renderer() {
    this->shutdown();
}

// TODO(wowvain-dev): continue working on the initialize function
void DX11Renderer::initialize() {
}


void DX11Renderer::render() {
    // EXECUTE COMMAND LISTS
}

void DX11Renderer::shutdown() {
    // Cleanup DirectX resources
    // For example, releasing ComPtr objects
}


