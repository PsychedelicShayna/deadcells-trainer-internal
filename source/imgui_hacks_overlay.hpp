#ifndef IMGUI_HACKS_OVERLAY
#define IMGUI_HACKS_OVERLAY

#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <functional>

// Windows Libraries
#include <Windows.h>
#include <d3d11.h>

// MinHook
#include <MinHook.h>

// ImGui
#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

// Game Hacking Toolkit
#include <libght.hpp>

#include "player_structure.hpp"

#include "dc_asm_patches.hpp"

#include "vmnoclip.hpp"

typedef HRESULT(__stdcall IDXGISCPresentFunctionSignature)(IDXGISwapChain*, UINT, UINT);
typedef IDXGISCPresentFunctionSignature* IDXGISCPresentFunctionPointer;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ImGuiHacksOverlay {
protected:
    bool imGuiInitialized;
    bool minHookInitialized;

    bool isPresentFunctionHookEnabled;

    struct MinHookVarsStruct {
        IDXGISCPresentFunctionPointer    hookedPresentFunctionPointer;
        IDXGISCPresentFunctionPointer    originalPresentFunctionPointer;
    } minHookVars;

    struct ImGuiVarsStruct {
        ID3D11Device*                    pDevice;
        ID3D11DeviceContext*             pDeviceContext;
        ID3D11RenderTargetView*          pRenderTarget;

        HWND                             targetWindow;
        WNDPROC                          originalWndProc;
    } imGuiVars;

    static IDXGISCPresentFunctionPointer acquirePresentFunctionPointer();
    static HRESULT __stdcall presentFunctionDetour(IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags);
    static LRESULT __stdcall customWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void initializeImGui(IDXGISwapChain* swap_chain);
    void initializeMinHook();

protected:
    Player                   DcHacks_PlayerStruct;
    VMNoclip                 DcHacks_Noclip;

    int32_t ImGui_HealthSliderValue;
    int32_t ImGui_MaxHealthInputValue;
    int32_t ImGui_MoneyInputValue;
    int32_t ImGui_CellsInputValue;
    int32_t ImGui_FlaskChargesInputValue;
    bool    ImGui_FlaskPatchCheckBoxValue;
    bool    ImGui_NoclipCheckBoxValue;
    bool    ImGui_InfiniteJumpPatchCheckBoxValue;


    bool imGuiUiValuesInitialized;
    void imGuiUiInitializeValues();

    void imGuiUiGetValuesFromGame();
    void imGuiDisplay();
    ImGuiHacksOverlay();

public:
    void Hook();
    void Unhook();

    bool IsHookEnabled();

    static ImGuiHacksOverlay* GetInstance();
    static ImGuiHacksOverlay Construct();

    static ImGuiHacksOverlay* ImGuiHacksOverlayInstance;
    static ImGuiHacksOverlay(*Constructor)();

    void Cleanup();

    ~ImGuiHacksOverlay();
};

#endif // IMGUI_HACKS_OVERLAY
