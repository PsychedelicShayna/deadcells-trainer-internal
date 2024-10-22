#include "imgui_hacks_overlay.hpp"

HRESULT __stdcall ImGuiHacksOverlay::presentFunctionDetour(IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags) {
    ImGuiHacksOverlay* instance { GetInstance() };
    if(!instance->imGuiInitialized) instance->initializeImGui(swap_chain);

    if(instance->imGuiInitialized) {
        if(!instance->imGuiUiValuesInitialized) instance->imGuiUiInitializeValues();
        instance->imGuiDisplay();
    }

    return instance->minHookVars.hookedPresentFunctionPointer(swap_chain, sync_interval, flags);
}

LRESULT __stdcall ImGuiHacksOverlay::customWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    ImGuiHacksOverlay* instance { GetInstance() };

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
        return true;
    }

    return CallWindowProc(instance->imGuiVars.originalWndProc, hWnd, uMsg, wParam, lParam);
}

IDXGISCPresentFunctionPointer ImGuiHacksOverlay::acquirePresentFunctionPointer() {
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

void ImGuiHacksOverlay::initializeImGui(IDXGISwapChain* swap_chain) {
    if(!imGuiInitialized) {
        if(SUCCEEDED(swap_chain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&imGuiVars.pDevice)))) {
            imGuiVars.pDevice->GetImmediateContext(&imGuiVars.pDeviceContext);

            // Get the output window from the swap chain descriptor.
            {
                DXGI_SWAP_CHAIN_DESC swap_chain_descriptor;
                swap_chain->GetDesc(&swap_chain_descriptor);
                imGuiVars.targetWindow = swap_chain_descriptor.OutputWindow;
            }

            // Create a render target view from the back buffer of the swap chain.
            {
                ID3D11Texture2D* p_back_buffer { nullptr };
                swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&p_back_buffer));
                imGuiVars.pDevice->CreateRenderTargetView(p_back_buffer, nullptr, &imGuiVars.pRenderTarget);
                p_back_buffer->Release();
            }

            // Change the WNDPROC for the target window to our custom WNDPROC, and store the original WNDPROC.
            imGuiVars.originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(imGuiVars.targetWindow, GWLP_WNDPROC, reinterpret_cast<long>(customWndProc)));

            // Setup ImgGui
            ImGui::CreateContext();
            // ImGuiIO& io { ImGui::GetIO() };
            // io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

            ImGui_ImplWin32_Init(imGuiVars.targetWindow);
            ImGui_ImplDX11_Init(imGuiVars.pDevice, imGuiVars.pDeviceContext);

            imGuiInitialized = true;
        } else {
            std::cout << "Failed to initialize ImGui, GetDevice call was not successful!\n";
        }
    }
}

void ImGuiHacksOverlay::imGuiUiInitializeValues() {
    ImGui_HealthSliderValue                 = NULL;
    ImGui_MaxHealthInputValue               = NULL;
    ImGui_MoneyInputValue                   = NULL;
    ImGui_CellsInputValue                   = NULL;
    ImGui_FlaskChargesInputValue            = NULL;
    ImGui_FlaskPatchCheckBoxValue           = false;
    ImGui_NoclipCheckBoxValue               = false;
    ImGui_InfiniteJumpPatchCheckBoxValue    = false;

    imGuiUiValuesInitialized = true;
}

void ImGuiHacksOverlay::initializeMinHook() {
    if(!minHookInitialized) {
        MH_STATUS minhook_status { MH_Initialize() };

        if(minhook_status != MH_OK) {
            std::cout << "MinHook failed to initialize! Error message: "
                      << MH_StatusToString(minhook_status)
                      << "\n";
        } else {
            minHookVars.originalPresentFunctionPointer = acquirePresentFunctionPointer();

            MH_STATUS mh_create_hook_status {
                MH_CreateHook(reinterpret_cast<void*>(minHookVars.originalPresentFunctionPointer),
                              reinterpret_cast<void*>(&presentFunctionDetour),
                              reinterpret_cast<void**>(&minHookVars.hookedPresentFunctionPointer))
            };

            if(mh_create_hook_status != MH_OK) {
                std::cout << "MH_CreateHook failed! Error code: "
                          << MH_StatusToString(mh_create_hook_status)
                          << "\n";
            } else {
                minHookInitialized = true;
            }
        }
    }
}

void ImGuiHacksOverlay::imGuiUiGetValuesFromGame() {
    ImGui_HealthSliderValue                = DcHacks_PlayerStruct.GetHealth();
    ImGui_MaxHealthInputValue              = DcHacks_PlayerStruct.GetMaxHealth();
    ImGui_MoneyInputValue                  = DcHacks_PlayerStruct.GetMoney();
    ImGui_CellsInputValue                  = DcHacks_PlayerStruct.GetCells();
    ImGui_FlaskChargesInputValue           = DcHacks_PlayerStruct.GetFlaskCharges();
    ImGui_FlaskPatchCheckBoxValue          = AP_InfiniteFlasks.IsPatched();
    ImGui_InfiniteJumpPatchCheckBoxValue   = AP_InfiniteJump.IsPatched();
}

void ImGuiHacksOverlay::imGuiDisplay() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("DeadCells Internal Hack");

    // ----------------------------------------------------------------------------------------------------
    imGuiUiGetValuesFromGame();

    ImGui::Spacing();
    ImGui::Text("Health Hacks");
    ImGui::Separator();

    if(ImGui::InputInt("Maximum Health", &ImGui_MaxHealthInputValue, 1, 100)) {
        DcHacks_PlayerStruct.SetMaxHealth(ImGui_MaxHealthInputValue);
    }

    if(ImGui::SliderInt("Health", &ImGui_HealthSliderValue, 0, DcHacks_PlayerStruct.GetMaxHealth())) {
        DcHacks_PlayerStruct.SetHealth(ImGui_HealthSliderValue);
    }

    ImGui::Spacing();
    ImGui::Text("Money Hacks");
    ImGui::Separator();

    if(ImGui::InputInt("Money", &ImGui_MoneyInputValue, 1, 1000)) {
        DcHacks_PlayerStruct.SetMoney(ImGui_MoneyInputValue);
    }

    ImGui::Spacing();
    ImGui::Text("Cell Hacks");
    ImGui::Separator();

    if(ImGui::InputInt("Cells", &ImGui_CellsInputValue, 1, 100)) {
        DcHacks_PlayerStruct.SetCells(ImGui_CellsInputValue);
    }

    ImGui::Spacing();
    ImGui::Text("Flask Hacks");
    ImGui::Separator();

    if(ImGui::InputInt("Flask Charges", &ImGui_FlaskChargesInputValue, 1, 100)) {
        DcHacks_PlayerStruct.SetFlaskCharges(ImGui_FlaskChargesInputValue);
    }


    if(ImGui::Checkbox("Unlimited Flasks Patch", &ImGui_FlaskPatchCheckBoxValue)) {
        if(ImGui_FlaskPatchCheckBoxValue) AP_InfiniteFlasks.Patch();
        else AP_InfiniteFlasks.Restore();
    }

    ImGui::Spacing();
    ImGui::Text("Misc Hacks");
    ImGui::Separator();

    if(ImGui::Checkbox("Crude Noclip", &ImGui_NoclipCheckBoxValue)) {
        if(ImGui_NoclipCheckBoxValue) {
            DcHacks_Noclip.SyncToPlayerPosition();
            std::cout << "Out Of Bounds On: " << AP_DisableOutOfBounds.Patch() << "\n";
            std::cout << "Inertia MultiPatch On: " << AP_InertiaMultiPatch.Patch() << "\n";
        } else {
            std::cout << "Out Of Bounds Off: " << AP_DisableOutOfBounds.Restore() << "\n";
            std::cout << "Inertia MultiPatch Off: " << AP_InertiaMultiPatch.Restore() << "\n";
        }
    }

    if(ImGui_NoclipCheckBoxValue) DcHacks_Noclip.NoclipTick();

    if(ImGui::Checkbox("Infinite Jump Patch", &ImGui_InfiniteJumpPatchCheckBoxValue)) {
        if(ImGui_InfiniteJumpPatchCheckBoxValue) {
            std::cout << "Infinite Jump Patch Returned " << AP_InfiniteJump.Patch() << "\n";
            std::cout << "InfJump Addr: " << std::setw(2) << std::setfill('0') << std::hex << reinterpret_cast<uintptr_t>(AP_InfiniteJump.LatestMatchLocation) << "\n";
        }
        else {
            std::cout << "Infinite Jump Restore Returned " << AP_InfiniteJump.Restore() << "\n";
        }
    }

    // ----------------------------------------------------------------------------------------------------

    ImGui::End();
    ImGui::EndFrame();
    ImGui::Render();

    imGuiVars.pDeviceContext->OMSetRenderTargets(1, &imGuiVars.pRenderTarget, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

ImGuiHacksOverlay::ImGuiHacksOverlay()
    :
      imGuiInitialized                  { false },
      minHookInitialized                { false },
      isPresentFunctionHookEnabled      { false },
      imGuiUiValuesInitialized          { false }
{
    ZeroMemory(&minHookVars, sizeof(MinHookVarsStruct));
    ZeroMemory(&imGuiVars, sizeof(ImGuiVarsStruct));
}

void ImGuiHacksOverlay::Hook() {
    if(!minHookInitialized) initializeMinHook();

    if(minHookInitialized) {
        MH_EnableHook(reinterpret_cast<void*>(minHookVars.originalPresentFunctionPointer));
        isPresentFunctionHookEnabled = true;

        if(imGuiInitialized) {
            SetWindowLongPtr(imGuiVars.targetWindow, GWLP_WNDPROC, reinterpret_cast<long>(customWndProc));
        }
    }
}

void ImGuiHacksOverlay::Unhook() {
    if(minHookInitialized) {
        MH_DisableHook(reinterpret_cast<void*>(minHookVars.originalPresentFunctionPointer));
        isPresentFunctionHookEnabled = false;

        if(imGuiInitialized) {
            SetWindowLongPtr(imGuiVars.targetWindow, GWLP_WNDPROC, reinterpret_cast<long>(imGuiVars.originalWndProc));
        }
    }
}

bool ImGuiHacksOverlay::IsHookEnabled() {
    return isPresentFunctionHookEnabled;
}

ImGuiHacksOverlay* ImGuiHacksOverlay::GetInstance() {
    return ImGuiHacksOverlayInstance;
}

ImGuiHacksOverlay ImGuiHacksOverlay::Construct() {
    Constructor = nullptr;
    return std::move(ImGuiHacksOverlay());
}

ImGuiHacksOverlay(*ImGuiHacksOverlay::Constructor)() = ImGuiHacksOverlay::Construct;
ImGuiHacksOverlay* ImGuiHacksOverlay::ImGuiHacksOverlayInstance = nullptr;

void ImGuiHacksOverlay::Cleanup() {
    if(IsHookEnabled()) {
        Unhook();
    }

    if(imGuiInitialized) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if (imGuiVars.pRenderTarget)  { imGuiVars.pRenderTarget->Release();  imGuiVars.pRenderTarget  = nullptr; }
        if (imGuiVars.pDeviceContext) { imGuiVars.pDeviceContext->Release(); imGuiVars.pDeviceContext = nullptr; }
        if (imGuiVars.pDevice)        { imGuiVars.pDevice->Release();        imGuiVars.pDevice        = nullptr; }

        SetWindowLongPtr(imGuiVars.targetWindow, GWLP_WNDPROC, reinterpret_cast<long>(imGuiVars.originalWndProc));
    }
}

ImGuiHacksOverlay::~ImGuiHacksOverlay() {
    ImGuiHacksOverlayInstance = nullptr;
    Constructor = ImGuiHacksOverlay::Construct;
}
