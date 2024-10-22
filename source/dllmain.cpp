#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <Windows.h>
#include <stdio.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// #include "d3d11_graphics.hpp"

#include <libght.hpp>
#include <MinHook.h>

#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

#include <d3d11.h>

#include "player_structure.hpp"
#include "apflask.hpp"

#include "imgui_hacks_overlay.hpp"

HMODULE DLL_HANDLE { nullptr };
FILE*   FP_CONSOLE { nullptr };

void DllExit() {
    MH_DisableHook(MH_ALL_HOOKS);

    if(FP_CONSOLE != nullptr) {
        fclose(FP_CONSOLE);
        FreeConsole();
    }

    if(DLL_HANDLE != nullptr) {
        FreeLibraryAndExitThread(DLL_HANDLE, 0);
    }
}

/*
typedef HRESULT(__stdcall IDXGISCPresentFunctionSignature)(IDXGISwapChain*, UINT, UINT);
typedef IDXGISCPresentFunctionSignature* IDXGISCPresentFunctionPointer;

IDXGISCPresentFunctionPointer IDXGISCPresentFunctionHookedLocation   { nullptr };
IDXGISCPresentFunctionPointer IDXGISCPresentFunctionOriginalLocation { nullptr };

IDXGISCPresentFunctionPointer AcquireIDXGISCPresentFunctionPointer() {
    constexpr const size_t feature_levels_len { 1 };
    constexpr const D3D_FEATURE_LEVEL feature_levels[feature_levels_len] { D3D_FEATURE_LEVEL_11_0 };

    DXGI_SWAP_CHAIN_DESC swap_chain_description;
    ZeroMemory(&swap_chain_description, sizeof(DXGI_SWAP_CHAIN_DESC));

    swap_chain_description.BufferCount          = 1;
    swap_chain_description.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_description.BufferUsage          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_description.OutputWindow         = GetForegroundWindow();
    swap_chain_description.SampleDesc.Count     = 1;
    swap_chain_description.Windowed             = true;
    swap_chain_description.SwapEffect           = DXGI_SWAP_EFFECT_DISCARD;

    IDXGISwapChain* swap_chain;
    ID3D11Device* device;

    if(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        feature_levels,
        feature_levels_len,
        D3D11_SDK_VERSION,
        &swap_chain_description,
        &swap_chain,
        &device,
        nullptr,
        nullptr
    ) == S_OK) {
        void** vtable_ptr { *reinterpret_cast<void***>(swap_chain) };
        swap_chain->Release();
        device->Release();

        return reinterpret_cast<IDXGISCPresentFunctionPointer>(vtable_ptr[8]);
    } else {
        return nullptr;
    }
}

DcInternalHacks::APFlask ap_flask;
Player player;

ID3D11Device*           p_device         { nullptr };
ID3D11DeviceContext*    p_device_context { nullptr };
ID3D11RenderTargetView* p_render_target  { nullptr };

HWND    target_window;
WNDPROC original_wndproc;

bool DetourInit = false;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
        return true;
    }

    return CallWindowProc(original_wndproc, hWnd, uMsg, wParam, lParam);
}

void ImGuiCleanup() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (p_render_target)  { p_render_target->Release();  p_render_target  = nullptr; }
    if (p_device_context) { p_device_context->Release(); p_device_context = nullptr; }
    if (p_device)         { p_device->Release();         p_device         = nullptr; }

    SetWindowLongPtr(target_window, GWLP_WNDPROC, reinterpret_cast<long>(original_wndproc));
}

HRESULT __stdcall IDXGISCPresentFunctionDetour(IDXGISwapChain* swap_chain_ptr, UINT sync_interval, UINT flags) {
    if(!DetourInit) {
        if(SUCCEEDED(swap_chain_ptr->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&p_device)))) {
            p_device->GetImmediateContext(&p_device_context);

            // Get the output window from the swap chain descriptor.
            {
                DXGI_SWAP_CHAIN_DESC swap_chain_descriptor;
                swap_chain_ptr->GetDesc(&swap_chain_descriptor);
                target_window = swap_chain_descriptor.OutputWindow;
            }

            // Create a render target view from the back buffer of the swap chain.
            {
                ID3D11Texture2D* p_back_buffer { nullptr };
                swap_chain_ptr->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&p_back_buffer));
                p_device->CreateRenderTargetView(p_back_buffer, nullptr, &p_render_target);
                p_back_buffer->Release();
            }

            // Change the WNDPROC for the target window to our custom WNDPROC, and store the original WNDPROC.
            original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(target_window, GWLP_WNDPROC, reinterpret_cast<long>(WndProc)));

            // Setup ImgGui
            ImGui::CreateContext();
            // ImGuiIO& io { ImGui::GetIO() };
            // io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

            ImGui_ImplWin32_Init(target_window);
            ImGui_ImplDX11_Init(p_device, p_device_context);

            DetourInit = true;
        } else {
            std::cout << "Failed to initialize, GetDevice call was not successful!\n";
        }
    } else {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();

        static bool test_bool = false;

        ImGui::NewFrame();
        ImGui::Begin("Test Window");

        ImGui::Checkbox("Flask Patch", &test_bool);

        if(test_bool) {
            if(!ap_flask.IsPatched()) ap_flask.Patch();
        } else {
            if(ap_flask.IsPatched()) ap_flask.Restore();
        }

        static int player_health = player.GetMaxHealth();

        if(ImGui::SliderInt("Health", &player_health, 1, player.GetMaxHealth())) {
            player.SetHealth(player_health);
        }

        ImGui::End();
        ImGui::EndFrame();
        ImGui::Render();

        p_device_context->OMSetRenderTargets(1, &p_render_target, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    return IDXGISCPresentFunctionHookedLocation(swap_chain_ptr, sync_interval, flags);
}

void CreateIDXGISCPresentFunctionHook() {
    IDXGISCPresentFunctionPointer present_function_ptr { AcquireIDXGISCPresentFunctionPointer() };

    MH_STATUS mh_create_hook_status {
        MH_CreateHook(reinterpret_cast<void*>(present_function_ptr),
                      reinterpret_cast<void*>(&IDXGISCPresentFunctionDetour),
                      reinterpret_cast<void**>(&IDXGISCPresentFunctionHookedLocation))
    };

    if(mh_create_hook_status != MH_OK) {
        std::cout << "MH_CreateHook failed! Error code: " << MH_StatusToString(mh_create_hook_status) << "\n";
        Sleep(1000);
        DllExit();
    }
}

*/

[[noreturn]] void WINAPI ThreadLoop(HMODULE dll_handle)  {
    AllocConsole();
    freopen_s(&FP_CONSOLE, "CONOUT$", "w", stdout);
    std::cout << "DLL Has been injected successfully.\n";

    if(ImGuiHacksOverlay::Constructor == nullptr) {
        std::cout << "Cannot construct ImGuiHacksOverlay instance because constructor is nullptr!\n";
        Sleep(1500);
        DllExit();
    }

    ImGuiHacksOverlay overlay { ImGuiHacksOverlay::Constructor() };
    overlay.ImGuiHacksOverlayInstance = &overlay;

    for(;;Sleep(20)) {
        if(GetAsyncKeyState(0x6B) & 0x8000) {
            break;
        }

        if(GetAsyncKeyState(0x6A) & 0x8000) {
            for(;GetAsyncKeyState(0x6A) & 0x8000;Sleep(50));

            if(overlay.IsHookEnabled()) {
                overlay.Unhook();
            } else {
                overlay.Hook();
            }
        }
    }

    overlay.Cleanup();
    DllExit();
}

bool APIENTRY DllMain(HMODULE dll_handle, DWORD reason_for_call, LPVOID reserved) {
    switch(reason_for_call) {
    case DLL_PROCESS_ATTACH : {
        DLL_HANDLE = dll_handle;
        DisableThreadLibraryCalls(dll_handle);
        CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadLoop), dll_handle, 0, nullptr));
        break;
    }

    case DLL_THREAD_ATTACH : {

        break;
    }

    case DLL_THREAD_DETACH : {

        break;
    }

    case DLL_PROCESS_DETACH : {

        break;
    }
    }

    return true;
}
