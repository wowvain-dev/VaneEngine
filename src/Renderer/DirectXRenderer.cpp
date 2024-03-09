#include <DirectXRenderer.h>
#include <SDL2/SDL.h>
#include <fmt/core.h>
#include <iostream>

DirectXRenderer::~DirectXRenderer() {

}

// TODO(wowvain-dev): continue working on the initialize function
void DirectXRenderer::initialize() {
    // createDevice();
    // createCommandQueue();
    // createSwapChain();
    // createRenderTargetViews();

    // Create device, swap chain, command queue, etc.
    // This example assumes you have a HWND handle available for creating the swpa chain
    UINT dxgiFactoryFlags = 0;

    // Enable the debug layer (in debug mode)
#if defined(_DEBUG)
    {
        Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
            debugController -> EnableDebugLayer();
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
#endif

    Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
    CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));

    /// Creating the Direct3D 12 Device
    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

    if (FAILED(hr)) {
        Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
        factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));
        D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
    }



    fmt::print("DirectX 12 Renderer Initialized.\n");

    // ADDIDTIONAL INITIALIZATION LIKE CREATING COMMAND LISTS

    /// Create a direct command queue
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
    device -> CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));

    int height, width;

    SDL_GetWindowSize(this->sdlWindow, &width, &height);

    /// Describe and create the swap chain
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = width;
    swapChainDesc.Height = height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;

    factory->CreateSwapChainForHwnd(
        commandQueue.Get(),
        reinterpret_cast<HWND>(sdlWindow),
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapChain
    );
}


void DirectXRenderer::render() {
    // EXECUTE COMMAND LISTS
}

void DirectXRenderer::shutdown() {
    // Cleanup DirectX resources
    // For example, releasing ComPtr objects
}


