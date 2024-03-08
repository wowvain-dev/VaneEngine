#include <DirectXRenderer.h>
#include <iostream>

DirectXRenderer::DirectXRenderer() {

}

DirectXRenderer::~DirectXRenderer() {

}

void DirectXRenderer::initialize() {
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

    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

    if (FAILED(hr)) {
        Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
        factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));
        D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
    }

    std::cout << "DirectX 12 Renderer Initialized." << std::endl;

    // ADDIDTIONAL INITIALIZATION LIKE CREATING COMMAND LISTS
}

void DirectXRenderer::render() {
    // EXECUTE COMMAND LISTS
}

void DirectXRenderer::shutdown() {
    // Cleanup DirectX resources
    // For example, releasing ComPtr objects
}


