#pragma once

#include "Renderer.h"

#include <cstdint>
#include <SDL2/SDL.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#define COMPTR(x) Microsoft::WRL::ComPtr<x>

const int frameBufferCount = 3;

namespace Vane {
class DX11Renderer : public Renderer {
public:
    DX11Renderer(SDL_Window* window) : sdlWindow(window) {};
    ~DX11Renderer();

    void initialize() override;
    void render() override;
    void shutdown() override;

private:
    SDL_Window* sdlWindow;
    COMPTR(ID3D12Device) device;
    COMPTR(IDXGISwapChain3) swapChain;
    COMPTR(ID3D12CommandQueue) commandQueue;
    COMPTR(ID3D12DescriptorHeap) rtvDescriptorHeap;
    COMPTR(ID3D12Device) renderTargets[frameBufferCount];
    COMPTR(ID3D12CommandAllocator) commandAllocator[frameBufferCount];
    COMPTR(ID3D12GraphicsCommandList) commandList;
    COMPTR(ID3D12Fence) fence[frameBufferCount];

    HANDLE fenceEvent;
    UINT64 fenceValue[frameBufferCount];

    int frameIndex;
    int rtvDescriptorSize;

};
}