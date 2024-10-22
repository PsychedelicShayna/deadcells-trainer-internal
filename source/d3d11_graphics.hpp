#ifndef D3D11GRAPHICS_HPP
#define D3D11GRAPHICS_HPP

#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <Windows.h>
#include <d3d11.h>

#include <SpriteBatch.h>
#include <SpriteFont.h>

#include <memory>

class D3D11Graphics {
public:
    ID3D11Device*              DevicePtr;
    IDXGISwapChain*            SwapChainPtr;
    ID3D11DeviceContext*       DeviceContextPtr;
    // ID3D11Resource*            BackBufferPtr;
    ID3D11RenderTargetView*    RenderTargetViewPtr;
    HWND                       OutputWindow;

    std::unique_ptr<DirectX::SpriteFont> SpriteFont;
    std::unique_ptr<DirectX::SpriteBatch> SpriteBatch;

    bool Initialized;

    void Init(HWND output_window);

    void DoFrame();
    void EndFrame();

    D3D11Graphics();
    ~D3D11Graphics();
};

#endif // D3D11GRAPHICS_HPP
