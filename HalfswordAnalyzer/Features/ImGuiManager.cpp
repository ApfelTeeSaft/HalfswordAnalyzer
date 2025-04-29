#include "ImGuiManager.h"
#include "../Core/Core.h"
#include "../Core/Hooks.h"
#include "../Utils/Logger.h"
#include "../Utils/StringUtils.h"
#include "../Features/ConsoleManager.h"
#include "../Features/PositionTracker.h"

#include "../imgui.h"
#include "../imgui_internal.h"
#include "../backends/imgui_impl_win32.h"
#include "../backends/imgui_impl_dx11.h"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace HalfswordAnalyzer {
    namespace Features {
        bool ImGuiManager::s_Initialized = false;
        bool ImGuiManager::s_Visible = false;
        bool ImGuiManager::s_Running = false;
        bool ImGuiManager::s_ShowDemo = false;
        bool ImGuiManager::s_CoreInitialized = false;
        bool ImGuiManager::s_GameInitialized = false;
        bool ImGuiManager::s_LevelDataCollected = false;
        bool ImGuiManager::s_InitScreenClosed = true;
        bool ImGuiManager::s_ShowLevelSelector = false;
        HWND ImGuiManager::s_GameWindow = NULL;
        HWND ImGuiManager::s_ImGuiWindow = NULL;
        WNDPROC ImGuiManager::s_OriginalWndProc = NULL;
        ImGuiContext* ImGuiManager::s_ImGuiContext = NULL;
        HANDLE ImGuiManager::s_RenderThread = NULL;

        nlohmann::json ImGuiManager::s_LevelInfoJson = nlohmann::json::array();
        std::vector<std::string> ImGuiManager::s_InitializationMessages;
        float ImGuiManager::s_InitProgress = 0.0f;
        int ImGuiManager::s_SelectedLevelIndex = 0;
        std::vector<ImGuiManager::InitStage> ImGuiManager::s_InitStages = {
            {"DLL Injection", "Completed", true},
            {"Core Initialization", "Waiting", false},
            {"Game SDK Detection", "Waiting", false},
            {"Hooks Installation", "Waiting", false},
            {"UE Console Setup", "Waiting", false},
            {"Level Data Collection", "Waiting", false}
        };

        static ID3D11Device* g_pd3dDevice = NULL;
        static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
        static IDXGISwapChain* g_pSwapChain = NULL;
        static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

        static bool CreateDeviceD3D(HWND hWnd)
        {
            DXGI_SWAP_CHAIN_DESC sd;
            ZeroMemory(&sd, sizeof(sd));
            sd.BufferCount = 2;
            sd.BufferDesc.Width = 0;
            sd.BufferDesc.Height = 0;
            sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            sd.BufferDesc.RefreshRate.Numerator = 60;
            sd.BufferDesc.RefreshRate.Denominator = 1;
            sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
            sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            sd.OutputWindow = hWnd;
            sd.SampleDesc.Count = 1;
            sd.SampleDesc.Quality = 0;
            sd.Windowed = TRUE;
            sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            UINT createDeviceFlags = 0;
            D3D_FEATURE_LEVEL featureLevel;
            const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
            if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
                return false;

            CreateRenderTarget();
            return true;
        }

        static void CleanupDeviceD3D()
        {
            CleanupRenderTarget();
            if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
            if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
            if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
        }

        static void CreateRenderTarget()
        {
            ID3D11Texture2D* pBackBuffer;
            g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
            g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
            pBackBuffer->Release();
        }

        static void CleanupRenderTarget()
        {
            if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
        }

        LRESULT CALLBACK ImGuiManager::WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
                return true;

            switch (msg)
            {
            case WM_SIZE:
                if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
                {
                    CleanupRenderTarget();
                    g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                    CreateRenderTarget();
                }
                return 0;
            case WM_SYSCOMMAND:
                if ((wParam & 0xfff0) == SC_KEYMENU)
                    return 0;
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            }
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }

        LRESULT CALLBACK ImGuiManager::GameWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            if (msg == WM_KEYDOWN && wParam == VK_INSERT) {
                ToggleVisibility();
                return 0;
            }

            return Hooks::WndProcHook(hWnd, msg, wParam, lParam);
        }

        DWORD WINAPI ImGuiManager::RenderThreadProc(LPVOID lpParam)
        {
            IMGUI_CHECKVERSION();
            s_ImGuiContext = ImGui::CreateContext();
            ImGui::SetCurrentContext(s_ImGuiContext);
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.IniFilename = NULL;

            ImGui_ImplWin32_Init(s_ImGuiWindow);
            ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

            PushModernStyle();

            MSG msg;
            ZeroMemory(&msg, sizeof(msg));
            while (s_Running && msg.message != WM_QUIT)
            {
                if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                    continue;
                }

                s_CoreInitialized = Core::IsHotkeyActive();
                s_GameInitialized = (SDK::UWorld::GetWorld() != nullptr);

                if (s_GameInitialized && !s_LevelDataCollected && s_Visible) {
                    CollectLevelData();
                    s_LevelDataCollected = true;
                    s_InitStages[5].status = "Completed";
                    s_InitStages[5].completed = true;
                    s_InitProgress = 1.0f;
                    s_InitializationMessages.push_back("Level data collected successfully");
                }

                if (s_CoreInitialized && !s_InitStages[1].completed) {
                    s_InitStages[1].status = "Completed";
                    s_InitStages[1].completed = true;
                    s_InitProgress = 0.3f;
                    s_InitializationMessages.push_back("Core initialized successfully");
                }

                if (s_GameInitialized && !s_InitStages[2].completed) {
                    s_InitStages[2].status = "Completed";
                    s_InitStages[2].completed = true;
                    s_InitProgress = 0.5f;
                    s_InitializationMessages.push_back("Game SDK detected successfully");
                }

                if (s_CoreInitialized && !s_InitStages[3].completed) {
                    s_InitStages[3].status = "Completed";
                    s_InitStages[3].completed = true;
                    s_InitProgress = 0.7f;
                    s_InitializationMessages.push_back("Hooks installed successfully");
                }

                if (s_GameInitialized && !s_InitStages[4].completed && Features::ConsoleManager::IsConsoleEnabled()) {
                    s_InitStages[4].status = "Completed";
                    s_InitStages[4].completed = true;
                    s_InitProgress = 0.9f;
                    s_InitializationMessages.push_back("UE Console setup successfully");
                }

                ImGui_ImplDX11_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                RenderMainInterface();

                if (s_ShowDemo) {
                    ImGui::ShowDemoWindow(&s_ShowDemo);
                }

                ImGui::Render();
                g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
                const float clear_color_with_alpha[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
                g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                g_pSwapChain->Present(1, 0);
            }

            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            CleanupDeviceD3D();
            DestroyWindow(s_ImGuiWindow);
            UnregisterClass(L"HalfswordAnalyzerWindow", GetModuleHandle(NULL));

            return 0;
        }

        void ImGuiManager::SetVisible(bool visible)
        {
            s_Visible = visible;
            if (s_ImGuiWindow)
            {
                ShowWindow(s_ImGuiWindow, visible ? SW_SHOW : SW_HIDE);
                if (visible)
                {
                    SetForegroundWindow(s_ImGuiWindow);
                    if (s_GameInitialized && !s_LevelDataCollected)
                    {
                        CollectLevelData();
                        s_LevelDataCollected = true;
                    }
                }
            }
        }

        void ImGuiManager::ToggleVisibility()
        {
            SetVisible(!s_Visible);
        }

        bool ImGuiManager::Initialize() {
            if (s_Initialized) {
                return true;
            }

            Utils::Logger::Info("Initializing ImGui Manager with external window...");

            s_GameWindow = Core::GetGameWindow();
            if (!s_GameWindow) {
                Utils::Logger::Error("Failed to get game window for ImGui initialization");
                return false;
            }

            if (!CreateExternalWindow()) {
                Utils::Logger::Error("Failed to create external ImGui window");
                return false;
            }

            s_OriginalWndProc = (WNDPROC)GetWindowLongPtr(s_GameWindow, GWLP_WNDPROC);
            if (!s_OriginalWndProc) {
                Utils::Logger::Error("Failed to get original window procedure for ImGui");
                return false;
            }

            SetWindowLongPtr(s_GameWindow, GWLP_WNDPROC, (LONG_PTR)GameWndProcHandler);

            s_Running = true;
            s_RenderThread = CreateThread(NULL, 0, RenderThreadProc, NULL, 0, NULL);
            if (!s_RenderThread) {
                Utils::Logger::Error("Failed to create render thread");
                return false;
            }

            s_InitializationMessages.push_back("ImGui Manager initialized with external window");
            s_InitializationMessages.push_back("Press INSERT at any time to toggle the analyzer window");

            s_Initialized = true;
            Utils::Logger::Info("ImGui Manager initialized with external window");

            return true;
        }

        bool ImGuiManager::CreateExternalWindow() {
            WNDCLASSEX wc = {
                sizeof(WNDCLASSEX),
                CS_CLASSDC,
                WndProcHandler,
                0L,
                0L,
                GetModuleHandle(NULL),
                NULL,
                NULL,
                NULL,
                NULL,
                L"HalfswordAnalyzerWindow",
                NULL
            };

            RegisterClassEx(&wc);

            s_ImGuiWindow = CreateWindow(
                wc.lpszClassName,
                L"Halfsword Analyzer",
                WS_OVERLAPPEDWINDOW,
                100, 100, 800, 600,
                NULL, NULL, wc.hInstance, NULL
            );

            if (!s_ImGuiWindow) {
                Utils::Logger::Error("Failed to create ImGui window");
                return false;
            }

            if (!CreateDeviceD3D(s_ImGuiWindow)) {
                Utils::Logger::Error("Failed to create D3D device");
                CleanupDeviceD3D();
                DestroyWindow(s_ImGuiWindow);
                UnregisterClass(wc.lpszClassName, wc.hInstance);
                return false;
            }

            ShowWindow(s_ImGuiWindow, SW_HIDE);
            UpdateWindow(s_ImGuiWindow);

            return true;
        }

        void ImGuiManager::Shutdown() {
            if (!s_Initialized) {
                return;
            }

            if (s_GameWindow && s_OriginalWndProc) {
                SetWindowLongPtr(s_GameWindow, GWLP_WNDPROC, (LONG_PTR)s_OriginalWndProc);
            }

            s_Running = false;
            if (s_RenderThread) {
                WaitForSingleObject(s_RenderThread, 1000);
                CloseHandle(s_RenderThread);
                s_RenderThread = NULL;
            }

            s_Initialized = false;
            Utils::Logger::Info("ImGui Manager shutdown complete");
        }

        void ImGuiManager::RenderMainInterface() {
            RECT rect;
            GetClientRect(s_ImGuiWindow, &rect);
            ImVec2 windowSize(
                static_cast<float>(rect.right - rect.left),
                static_cast<float>(rect.bottom - rect.top)
            );

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(windowSize);

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

            ImGuiWindowFlags windowFlags =
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoBringToFrontOnFocus;

            if (ImGui::Begin("HalfswordAnalyzerMainWindow", NULL, windowFlags)) {
                if (ImGui::BeginMenuBar()) {
                    if (ImGui::BeginMenu("File")) {
                        if (ImGui::MenuItem("Refresh Data")) {
                            s_LevelDataCollected = false;
                            if (SDK::UWorld::GetWorld() != nullptr) {
                                CollectLevelData();
                                s_LevelDataCollected = true;
                            }
                        }
                        ImGui::Separator();
                        if (ImGui::MenuItem("Hide Window")) {
                            SetVisible(false);
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Tools")) {
                        ImGui::MenuItem("Show Demo Window", NULL, &s_ShowDemo);
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenuBar();
                }

                ImGui::BeginChild("StatusBar", ImVec2(windowSize.x, 30), true);
                ImGui::Text("Game Status: %s", s_GameInitialized ? "Connected" : "Not Connected");
                ImGui::SameLine(150);
                ImGui::Text("Current Level: %s", PositionTracker::GetCurrentLevelName().c_str());
                ImGui::SameLine(350);
                ImGui::Text("Hotkeys %s", s_CoreInitialized ? "Active" : "Inactive");
                ImGui::SameLine(windowSize.x - 200);
                ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.7f, 0.7f), "made with <3 by apfelteesaft");
                ImGui::EndChild();

                ImGui::BeginChild("MainContent", ImVec2(windowSize.x, windowSize.y - 60), false);
                if (ImGui::BeginTabBar("MainTabs")) {
                    if (ImGui::BeginTabItem("Level Selector")) {
                        RenderLevelSelector();
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Position Tracker")) {
                        RenderPositionTab();
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Settings")) {
                        RenderSettingsTab();
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndChild();

                ImGui::BeginChild("Footer", ImVec2(windowSize.x, 30), true);
                ImGui::Text("Press INSERT to toggle this window");
                ImGui::SameLine(windowSize.x - 300);
                ImGui::Text("Halfsword Analyzer v1.0");
                ImGui::EndChild();
            }
            ImGui::End();

            ImGui::PopStyleVar(3);
        }

        void ImGuiManager::RenderLevelSelector() {
            ImGui::BeginChild("LevelSelectorContent", ImVec2(0, 0), true);

            ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "LEVEL SELECTOR");
            ImGui::Separator();
            ImGui::Spacing();

            if (!s_GameInitialized) {
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Game not connected or initialized.");
                ImGui::Text("Please wait for the game to fully initialize.");
                ImGui::EndChild();
                return;
            }

            ImGui::Text("Select Level:");
            if (ImGui::BeginCombo("##LevelCombo", s_SelectedLevelIndex >= 0 && s_SelectedLevelIndex < s_LevelInfoJson.size() ?
                s_LevelInfoJson[s_SelectedLevelIndex]["mapName"].get<std::string>().c_str() : "Select Level")) {

                for (int i = 0; i < s_LevelInfoJson.size(); i++) {
                    const bool isSelected = (s_SelectedLevelIndex == i);
                    std::string levelName = s_LevelInfoJson[i]["mapName"].get<std::string>();

                    if (ImGui::Selectable(levelName.c_str(), isSelected)) {
                        s_SelectedLevelIndex = i;
                    }

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            ImGui::Spacing();

            if (s_SelectedLevelIndex >= 0 && s_SelectedLevelIndex < s_LevelInfoJson.size()) {
                ImGui::BeginChild("LevelDetails", ImVec2(0, 140), true);

                auto& levelInfo = s_LevelInfoJson[s_SelectedLevelIndex];
                std::string mapName = levelInfo["mapName"].get<std::string>();
                std::string contentPath = levelInfo["contentPath"].get<std::string>();

                ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Map Name:");
                ImGui::SameLine(120);
                ImGui::TextWrapped("%s", mapName.c_str());

                ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Content Path:");
                ImGui::SameLine(120);
                ImGui::TextWrapped("%s", contentPath.c_str());

                ImGui::EndChild();

                bool loadClicked = false;
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f - 60.0f);
                DrawModernButton("Load Level", &loadClicked, ImVec2(120, 40));

                if (loadClicked) {
                    std::string mapName = s_LevelInfoJson[s_SelectedLevelIndex]["mapName"].get<std::string>();
                    SwitchLevel(mapName);
                }
            }
            else {
                ImGui::BeginChild("LevelDetails", ImVec2(0, 140), true);
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Select a level to view its details");
                ImGui::EndChild();
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Text("All Available Levels:");
            if (ImGui::BeginTable("LevelTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {
                ImGui::TableSetupColumn("Map Name");
                ImGui::TableSetupColumn("Content Path");
                ImGui::TableHeadersRow();

                for (int i = 0; i < s_LevelInfoJson.size(); i++) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    bool isSelected = (s_SelectedLevelIndex == i);
                    if (ImGui::Selectable(s_LevelInfoJson[i]["mapName"].get<std::string>().c_str(), isSelected, ImGuiSelectableFlags_SpanAllColumns)) {
                        s_SelectedLevelIndex = i;
                    }

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%s", s_LevelInfoJson[i]["contentPath"].get<std::string>().c_str());
                }

                ImGui::EndTable();
            }

            ImGui::Spacing();
            bool refreshClicked = false;
            DrawModernButton("Refresh Level Data", &refreshClicked, ImVec2(200, 40));

            if (refreshClicked) {
                s_LevelDataCollected = false;
                CollectLevelData();
                s_LevelDataCollected = true;
                s_InitializationMessages.push_back("Level data refreshed");
            }

            ImGui::EndChild();
        }

        void ImGuiManager::RenderPositionTab() {
            ImGui::BeginChild("PositionTrackerContent", ImVec2(0, 0), true);

            ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "POSITION TRACKER");
            ImGui::Separator();
            ImGui::Spacing();

            if (!s_GameInitialized) {
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Game not connected or initialized.");
                ImGui::Text("Please wait for the game to fully initialize.");
                ImGui::EndChild();
                return;
            }

            ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Current Level:");
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", PositionTracker::GetCurrentLevelName().c_str());

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            SDK::UWorld* World = SDK::UWorld::GetWorld();
            if (World && World->OwningGameInstance) {
                SDK::APlayerController* PC = nullptr;
                if (World->OwningGameInstance->LocalPlayers.Num() > 0) {
                    PC = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
                }

                if (PC && PC->AcknowledgedPawn) {
                    SDK::APawn* Pawn = static_cast<SDK::APawn*>(PC->AcknowledgedPawn);
                    SDK::FVector Location = Pawn->K2_GetActorLocation();
                    SDK::FRotator Rotation = Pawn->K2_GetActorRotation();

                    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Player Location:");
                    ImGui::SameLine(150);
                    ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f", Location.X, Location.Y, Location.Z);

                    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Player Rotation:");
                    ImGui::SameLine(150);
                    ImGui::Text("Pitch: %.2f  Yaw: %.2f  Roll: %.2f", Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

                    if (PC->PlayerCameraManager) {
                        SDK::FVector CamLocation = PC->PlayerCameraManager->GetCameraLocation();
                        SDK::FRotator CamRotation = PC->PlayerCameraManager->GetCameraRotation();
                        float CamFOV = PC->PlayerCameraManager->GetFOVAngle();

                        ImGui::Spacing();
                        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Camera Location:");
                        ImGui::SameLine(150);
                        ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f", CamLocation.X, CamLocation.Y, CamLocation.Z);

                        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Camera Rotation:");
                        ImGui::SameLine(150);
                        ImGui::Text("Pitch: %.2f  Yaw: %.2f  Roll: %.2f", CamRotation.Pitch, CamRotation.Yaw, CamRotation.Roll);

                        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Camera FOV:");
                        ImGui::SameLine(150);
                        ImGui::Text("%.2f", CamFOV);
                    }
                }
                else {
                    ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "No player or pawn detected");
                }
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (World && World->OwningGameInstance) {
                SDK::APlayerController* PC = nullptr;
                if (World->OwningGameInstance->LocalPlayers.Num() > 0) {
                    PC = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
                }

                if (PC && PC->AcknowledgedPawn) {
                    SDK::APawn* Pawn = static_cast<SDK::APawn*>(PC->AcknowledgedPawn);
                    SDK::FVector Location = Pawn->K2_GetActorLocation();
                    SDK::FRotator Rotation = Pawn->K2_GetActorRotation();

                    SDK::FVector CamLocation;
                    SDK::FRotator CamRotation;
                    float CamFOV = 90.0f;

                    if (PC->PlayerCameraManager) {
                        CamLocation = PC->PlayerCameraManager->GetCameraLocation();
                        CamRotation = PC->PlayerCameraManager->GetCameraRotation();
                        CamFOV = PC->PlayerCameraManager->GetFOVAngle();
                    }

                    ImGui::Text("UE C++ Code:");
                    ImGui::BeginChild("CodeDisplay", ImVec2(0, 150), true);
                    ImGui::TextColored(ImVec4(0.4f, 0.7f, 1.0f, 1.0f), "// Position data for %s", PositionTracker::GetCurrentLevelName().c_str());
                    ImGui::Text("PlayerLocation = FVector(%.2ff, %.2ff, %.2ff);", Location.X, Location.Y, Location.Z);
                    ImGui::Text("PlayerRotation = FRotator(%.2ff, %.2ff, %.2ff);", Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
                    ImGui::Text("CameraLocation = FVector(%.2ff, %.2ff, %.2ff);", CamLocation.X, CamLocation.Y, CamLocation.Z);
                    ImGui::Text("CameraRotation = FRotator(%.2ff, %.2ff, %.2ff);", CamRotation.Pitch, CamRotation.Yaw, CamRotation.Roll);
                    ImGui::Text("CameraFOV = %.2ff;", CamFOV);
                    ImGui::EndChild();
                }
            }

            ImGui::Spacing();

            bool recordClicked = false;
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() * 0.5f - 100.0f);
            DrawModernButton("Record Current Position", &recordClicked, ImVec2(200, 40));

            if (recordClicked) {
                PositionTracker::RecordPlayerPosition();
                PositionTracker::LogPositionInfo();
                s_InitializationMessages.push_back("Recorded player position");
            }

            ImGui::EndChild();
        }

        void ImGuiManager::RenderSettingsTab() {
            ImGui::BeginChild("SettingsContent", ImVec2(0, 0), true);

            ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "SETTINGS & LOG");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "General Settings:");
            ImGui::Checkbox("Show ImGui Demo Window", &s_ShowDemo);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Initialization Status:");
            ImGui::Spacing();

            for (const auto& stage : s_InitStages) {
                ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "%s:", stage.name.c_str());
                ImGui::SameLine(ImGui::GetWindowWidth() * 0.6f);
                if (stage.completed) {
                    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", stage.status.c_str());
                }
                else if (stage.status == "In Progress") {
                    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "%s", stage.status.c_str());
                }
                else {
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "%s", stage.status.c_str());
                }
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Log Messages:");
            ImGui::BeginChild("LogMessages", ImVec2(0, 300), true);
            for (const auto& message : s_InitializationMessages) {
                ImGui::TextWrapped("%s", message.c_str());
            }
            ImGui::SetScrollY(ImGui::GetScrollMaxY());
            ImGui::EndChild();

            ImGui::Spacing();

            bool clearLogClicked = false;
            DrawModernButton("Clear Log", &clearLogClicked, ImVec2(120, 30));

            if (clearLogClicked) {
                s_InitializationMessages.clear();
                s_InitializationMessages.push_back("Log cleared");
            }

            ImGui::EndChild();
        }

        void ImGuiManager::CollectLevelData() {
            s_LevelInfoJson.clear();

            Utils::Logger::Info("Collecting level data from GObjects...");
            s_InitializationMessages.push_back("Collecting level data from GObjects...");

            if (!SDK::UObject::GObjects) {
                Utils::Logger::Error("GObjects is null");
                s_InitializationMessages.push_back("Error: GObjects is null");
                return;
            }

            int numObjects = SDK::UObject::GObjects->Num();
            Utils::Logger::Info("Scanning %d objects...", numObjects);
            s_InitializationMessages.push_back("Scanning " + std::to_string(numObjects) + " objects...");

            int levelCount = 0;

            for (int i = 0; i < numObjects; i++) {
                SDK::UObject* object = SDK::UObject::GObjects->GetByIndex(i);
                if (!object) continue;

                if (object->IsA(SDK::ULevel::StaticClass())) {
                    SDK::ULevel* level = static_cast<SDK::ULevel*>(object);

                    std::string levelName = Utils::StringUtils::GetObjectName(level);
                    std::string contentPath = "";

                    SDK::UObject* outerObj = level->Outer;
                    if (outerObj) {
                        contentPath = Utils::StringUtils::GetObjectName(outerObj);
                    }

                    nlohmann::json levelInfo;
                    levelInfo["mapName"] = levelName;
                    levelInfo["contentPath"] = contentPath;
                    s_LevelInfoJson.push_back(levelInfo);

                    levelCount++;

                    Utils::Logger::Info("Found level: %s (Content Path: %s)",
                        levelName.c_str(), contentPath.c_str());
                }
            }

            Utils::Logger::Info("Found %d levels", levelCount);
            s_InitializationMessages.push_back("Found " + std::to_string(levelCount) + " levels");

            std::sort(s_LevelInfoJson.begin(), s_LevelInfoJson.end(),
                [](const nlohmann::json& a, const nlohmann::json& b) {
                    return a["mapName"].get<std::string>() < b["mapName"].get<std::string>();
                });
        }

        void ImGuiManager::SwitchLevel(const std::string& levelName) {
            SDK::UWorld* World = SDK::UWorld::GetWorld();
            if (!World) {
                Utils::Logger::Error("Failed to get World instance");
                s_InitializationMessages.push_back("Error: Failed to get World instance");
                return;
            }

            SDK::APlayerController* PC = nullptr;
            if (World->OwningGameInstance && World->OwningGameInstance->LocalPlayers.Num() > 0) {
                PC = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
            }

            if (!PC) {
                Utils::Logger::Error("Failed to get PlayerController instance");
                s_InitializationMessages.push_back("Error: Failed to get PlayerController instance");
                return;
            }

            std::wstring wideLevelName = std::wstring(levelName.begin(), levelName.end());
            SDK::FString levelNameF(wideLevelName.c_str());
            Utils::Logger::Info("Switching to level: %s", levelName.c_str());
            s_InitializationMessages.push_back("Switching to level: " + levelName);

            PC->SwitchLevel(levelNameF);
        }

        void ImGuiManager::DrawModernButton(const char* label, bool* clicked, const ImVec2& size) {
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 0.8f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.5f, 0.9f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.3f, 0.7f, 1.0f));

            *clicked = ImGui::Button(label, size);

            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();
        }

        void ImGuiManager::PushModernStyle() {
            ImGuiStyle& style = ImGui::GetStyle();

            ImVec4* colors = style.Colors;

            ImGuiIO& io = ImGui::GetIO();
            io.FontGlobalScale = 1.2f;

            colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.94f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.25f, 0.50f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.54f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.67f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.24f, 0.52f, 0.88f, 0.40f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.24f, 0.52f, 0.88f, 0.31f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.52f, 0.88f, 0.80f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
            colors[ImGuiCol_Separator] = ImVec4(0.24f, 0.52f, 0.88f, 0.50f);
            colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.52f, 0.88f, 0.78f);
            colors[ImGuiCol_SeparatorActive] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.52f, 0.88f, 0.20f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.52f, 0.88f, 0.67f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.24f, 0.52f, 0.88f, 0.95f);
            colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.52f, 0.88f, 0.80f);
            colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.24f, 0.52f, 0.88f, 0.63f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 0.60f, 1.00f, 1.00f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.52f, 0.88f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

            style.FrameRounding = 4.0f;
            style.WindowRounding = 6.0f;
            style.PopupRounding = 4.0f;
            style.ChildRounding = 4.0f;
            style.ScrollbarRounding = 4.0f;
            style.TabRounding = 4.0f;
            style.WindowPadding = ImVec2(8, 8);
            style.FramePadding = ImVec2(5, 5);
            style.ItemSpacing = ImVec2(6, 6);
            style.ItemInnerSpacing = ImVec2(6, 6);
            style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
            style.GrabMinSize = 6.0f;
            style.GrabRounding = 4.0f;
        }

        bool ImGuiManager::IsInitialized() {
            return s_Initialized;
        }

        nlohmann::json& ImGuiManager::GetLevelInfoJson() {
            return s_LevelInfoJson;
        }
    }
}