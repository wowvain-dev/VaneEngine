#pragma once

#include <SDL2/SDL.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include <cstdint>

#include "Renderer.h"


constexpr int frameBufferCount = 3;

namespace Vane::Albita {
class DX11Renderer : public Renderer {
public:
    DX11Renderer(SDL_Window* window);
    ~DX11Renderer() override;

    void initialize() override;
    void render() override;
    void shutdown() override;

    inline void clearBuffer(float red, float green, float blue) noexcept override {
        const float color[] = {red, green, blue, 1.0f};
        pContext->ClearRenderTargetView(pTarget, color);
    }

private:
    SDL_Window* sdlWindow;

    ID3D11Device* pDevice = nullptr;
    IDXGISwapChain* pSwap = nullptr;
    ID3D11DeviceContext* pContext = nullptr;
    ID3D11RenderTargetView* pTarget = nullptr;
};
} // namespace Vane
