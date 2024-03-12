#include <DX11Renderer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <fmt/core.h>

#include <iostream>

using namespace Vane::Albita;

DX11Renderer::DX11Renderer(SDL_Window* window) { sdlWindow = window; }

DX11Renderer::~DX11Renderer() { this->DX11Renderer::shutdown(); }

void DX11Renderer::initialize() {
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version)
    SDL_GetWindowWMInfo(sdlWindow, &wmInfo);

    HWND hwnd = wmInfo.info.win.window;

    DXGI_SWAP_CHAIN_DESC sd = {};

    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = hwnd;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
                                  nullptr, 0, D3D11_SDK_VERSION, &sd, &pSwap,
                                  &pDevice, nullptr, &pContext);

    ID3D11Resource* pBackBuffer = nullptr;
    pSwap->GetBuffer(0, __uuidof(ID3D11Resource),
                     reinterpret_cast<void**>(&pBackBuffer));
    pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
    pBackBuffer->Release();
}

void DX11Renderer::render() {
    HRESULT hr;

    if (hr = FAILED(pSwap->Present(1u, 0u))) {
        if (hr == DXGI_ERROR_DEVICE_REMOVED) {}
    }
    pSwap->Present(1u, 0u);
}

void DX11Renderer::shutdown() {
    std::cout << "\nShutting down renderer.";
    if (pContext != nullptr) {
        pContext->Release();
    }

    if (pSwap != nullptr) {
        pSwap->Release();
    }

    if (pDevice != nullptr) {
        pDevice->Release();
    }

    if (pTarget != nullptr) {
        pTarget->Release();
    }
}
