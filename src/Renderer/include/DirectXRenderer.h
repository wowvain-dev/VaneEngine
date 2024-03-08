#pragma once

#include "Renderer.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

class DirectXRenderer : public Renderer {
public:
    DirectXRenderer();
    ~DirectXRenderer();

    void initialize() override;
    void render() override;
    void shutdown() override;

private:
    Microsoft::WRL::ComPtr<ID3D12Device> device;
};