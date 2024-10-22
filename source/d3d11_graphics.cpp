#include "d3d11_graphics.hpp"

void D3D11Graphics::Init(HWND output_window) {
    if(Initialized) return;

    DXGI_SWAP_CHAIN_DESC swap_chain_desc {};

    ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    swap_chain_desc.BufferDesc.Width = 0;
    swap_chain_desc.BufferDesc.Height = 0;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0;
    swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.OutputWindow = output_window;
    swap_chain_desc.Windowed = true;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Flags = 0;

    HRESULT cdasc_result = D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                0,
                nullptr,
                0,
                D3D11_SDK_VERSION,
                &swap_chain_desc,
                &SwapChainPtr,
                &DevicePtr,
                nullptr,
                &DeviceContextPtr
    );

    ID3D11Resource* back_buffer_ptr;

    SwapChainPtr->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&back_buffer_ptr));
    DevicePtr->CreateRenderTargetView(back_buffer_ptr, nullptr, &RenderTargetViewPtr);
    back_buffer_ptr->Release();

    SpriteBatch = std::make_unique<DirectX::SpriteBatch>(DeviceContextPtr);
    SpriteFont = std::make_unique<DirectX::SpriteFont>(DevicePtr, L"C:\\Users\\Fedora\\Dropbox\\Repositories\\deadcells-internal-hack\\consolas.spritefont");

    Initialized = true;
    OutputWindow = output_window;
}

void D3D11Graphics::DoFrame() {
    SpriteBatch->Begin();
    SpriteFont->DrawString(SpriteBatch.get(), L"Testing!", DirectX::XMFLOAT2(0,0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
    SpriteBatch->End();

    EndFrame();
}

void D3D11Graphics::EndFrame() {
    // SwapChainPtr->Present(1u, 0u);
}

D3D11Graphics::D3D11Graphics()
    :
      DevicePtr           { nullptr },
      SwapChainPtr        { nullptr },
      DeviceContextPtr    { nullptr },
      OutputWindow        { nullptr },
      // BackBufferPtr       { nullptr },
      Initialized         { false   }

{



}

D3D11Graphics::~D3D11Graphics() {
    if(DevicePtr              != nullptr) DevicePtr->Release();
    if(SwapChainPtr           != nullptr) SwapChainPtr->Release();
    if(DeviceContextPtr       != nullptr) DeviceContextPtr->Release();
    if(RenderTargetViewPtr    != nullptr) RenderTargetViewPtr->Release();
}
