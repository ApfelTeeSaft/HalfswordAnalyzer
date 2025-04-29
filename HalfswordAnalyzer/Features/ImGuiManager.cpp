#include "ImGuiManager.h"
#include "../Core/Core.h"
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
        bool ImGuiManager::s_ShowDemo = false;
        bool ImGuiManager::s_CoreInitialized = false;
        bool ImGuiManager::s_GameInitialized = false;
        bool ImGuiManager::s_LevelDataCollected = false;
        bool ImGuiManager::s_InitScreenClosed = false;
        bool ImGuiManager::s_ShowLevelSelector = false;
        HWND ImGuiManager::s_GameWindow = NULL;
        WNDPROC ImGuiManager::s_OriginalWndProc = NULL;
        ImGuiContext* ImGuiManager::s_ImGuiContext = NULL;
        ID3D11Device* ImGuiManager::s_Device = NULL;
        ID3D11DeviceContext* ImGuiManager::s_DeviceContext = NULL;
        IDXGISwapChain* ImGuiManager::s_SwapChain = NULL;
        ID3D11RenderTargetView* ImGuiManager::s_RenderTargetView = NULL;
        nlohmann::json ImGuiManager::s_LevelInfoJson = nlohmann::json::array();
        std::vector<std::string> ImGuiManager::s_InitializationMessages;
        float ImGuiManager::s_InitProgress = 0.0f;
        int ImGuiManager::s_SelectedLevelIndex = 0;
        std::vector<ImGuiManager::InitStage> ImGuiManager::s_InitStages = {
            {"DLL Injection", "Waiting", false},
            {"Core Initialization", "Waiting", false},
            {"Game SDK Detection", "Waiting", false},
            {"Hooks Installation", "Waiting", false},
            {"UE Console Setup", "Waiting", false},
            {"Level Data Collection", "Waiting", false}
        };

        bool ImGuiManager::Initialize() {
            if (s_Initialized) {
                return true;
            }

            Utils::Logger::Info("Initializing ImGui Manager...");

            s_GameWindow = Core::GetGameWindow();
            if (!s_GameWindow) {
                Utils::Logger::Error("Failed to get game window for ImGui initialization");
                return false;
            }

            if (!InitializeDirectX()) {
                Utils::Logger::Error("Failed to initialize DirectX for ImGui");
                return false;
            }

            if (!InitializeImGui()) {
                Utils::Logger::Error("Failed to initialize ImGui context");
                return false;
            }

            s_OriginalWndProc = (WNDPROC)GetWindowLongPtr(s_GameWindow, GWLP_WNDPROC);
            if (!s_OriginalWndProc) {
                Utils::Logger::Error("Failed to get original window procedure for ImGui");
                return false;
            }

            SetWindowLongPtr(s_GameWindow, GWLP_WNDPROC, (LONG_PTR)WndProcHandler);

            s_InitStages[0].status = "Completed";
            s_InitStages[0].completed = true;
            s_InitProgress = 0.1f;

            s_InitializationMessages.push_back("ImGui Manager initialized successfully");
            s_InitializationMessages.push_back("Press INSERT at any time to access Level Selector");

            Utils::Logger::Info("ImGui Manager initialized successfully");
            Utils::Logger::Info("Press INSERT at any time to access Level Selector");
            s_Initialized = true;
            return true;
        }

        void ImGuiManager::Shutdown() {
            if (!s_Initialized) {
                return;
            }

            if (s_GameWindow && s_OriginalWndProc) {
                SetWindowLongPtr(s_GameWindow, GWLP_WNDPROC, (LONG_PTR)s_OriginalWndProc);
            }

            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext(s_ImGuiContext);

            if (s_RenderTargetView) s_RenderTargetView->Release();
            if (s_SwapChain) s_SwapChain->Release();
            if (s_DeviceContext) s_DeviceContext->Release();
            if (s_Device) s_Device->Release();

            Utils::Logger::Info("ImGui Manager shutdown complete");
            s_Initialized = false;
        }

        bool ImGuiManager::InitializeDirectX() {
            RECT rect;
            GetClientRect(s_GameWindow, &rect);
            UINT width = rect.right - rect.left;
            UINT height = rect.bottom - rect.top;

            DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
            swapChainDesc.BufferDesc.Width = width;
            swapChainDesc.BufferDesc.Height = height;
            swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
            swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = 1;
            swapChainDesc.OutputWindow = s_GameWindow;
            swapChainDesc.Windowed = TRUE;
            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            UINT createDeviceFlags = 0;
#ifdef _DEBUG
            createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

            D3D_FEATURE_LEVEL featureLevel;
            const D3D_FEATURE_LEVEL featureLevelArray[1] = { D3D_FEATURE_LEVEL_11_0 };

            HRESULT hr = D3D11CreateDeviceAndSwapChain(
                NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
                featureLevelArray, 1, D3D11_SDK_VERSION,
                &swapChainDesc, &s_SwapChain, &s_Device, &featureLevel, &s_DeviceContext);

            if (FAILED(hr)) {
                Utils::Logger::Error("D3D11CreateDeviceAndSwapChain failed with error code: 0x%X", hr);
                return false;
            }

            ID3D11Texture2D* backBuffer = NULL;
            hr = s_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
            if (FAILED(hr)) {
                Utils::Logger::Error("Failed to get back buffer from swap chain: 0x%X", hr);
                return false;
            }

            hr = s_Device->CreateRenderTargetView(backBuffer, NULL, &s_RenderTargetView);
            backBuffer->Release();
            if (FAILED(hr)) {
                Utils::Logger::Error("Failed to create render target view: 0x%X", hr);
                return false;
            }

            s_DeviceContext->OMSetRenderTargets(1, &s_RenderTargetView, NULL);

            D3D11_VIEWPORT viewport;
            viewport.Width = (float)width;
            viewport.Height = (float)height;
            viewport.MinDepth = 0.0f;
            viewport.MaxDepth = 1.0f;
            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;
            s_DeviceContext->RSSetViewports(1, &viewport);

            return true;
        }

        bool ImGuiManager::InitializeImGui() {
            s_ImGuiContext = ImGui::CreateContext();
            if (!s_ImGuiContext) {
                Utils::Logger::Error("Failed to create ImGui context");
                return false;
            }

            ImGui::SetCurrentContext(s_ImGuiContext);

            if (!ImGui_ImplWin32_Init(s_GameWindow)) {
                Utils::Logger::Error("Failed to initialize ImGui for Win32");
                return false;
            }

            if (!ImGui_ImplDX11_Init(s_Device, s_DeviceContext)) {
                Utils::Logger::Error("Failed to initialize ImGui for DirectX 11");
                return false;
            }

            PushModernStyle();

            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

            return true;
        }

        void ImGuiManager::Render() {
            if (!s_Initialized) {
                return;
            }

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            s_CoreInitialized = Core::IsHotkeyActive();
            s_GameInitialized = (SDK::UWorld::GetWorld() != nullptr);

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

            if (s_GameInitialized && !s_LevelDataCollected) {
                CollectLevelData();
                s_LevelDataCollected = true;
                s_InitStages[5].status = "Completed";
                s_InitStages[5].completed = true;
                s_InitProgress = 1.0f;
                s_InitializationMessages.push_back("Level data collected successfully");
            }

            if (s_LevelDataCollected && !s_InitScreenClosed) {
                RenderInitializationScreen();
            }
            else if (s_ShowLevelSelector && s_InitScreenClosed) {
                RenderLevelSelector();
            }
            else if (s_InitScreenClosed) {
                RenderMainInterface();
            }

            if (s_ShowDemo) {
                ImGui::ShowDemoWindow(&s_ShowDemo);
            }

            ImGui::Render();
            s_DeviceContext->OMSetRenderTargets(1, &s_RenderTargetView, NULL);
            ImVec4 clearColor(0.0f, 0.0f, 0.0f, 0.0f);
            s_DeviceContext->ClearRenderTargetView(s_RenderTargetView, (float*)&clearColor);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            s_SwapChain->Present(1, 0);
        }

        void ImGuiManager::RenderInitializationScreen() {
            RECT windowRect;
            GetClientRect(s_GameWindow, &windowRect);
            ImVec2 windowSize(
                static_cast<float>(windowRect.right - windowRect.left),
                static_cast<float>(windowRect.bottom - windowRect.top)
            );

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(windowSize);

            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.25f));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

            if (ImGui::Begin("##InitScreen", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoScrollWithMouse |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoNavFocus |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoFocusOnAppearing)) {

                ImGui::SetCursorPos(ImVec2(10, 10));
                ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.7f, 0.7f), "made with <3 by apfelteesaft");

                ImVec2 contentSize(windowSize.x * 0.6f, windowSize.y * 0.7f);
                ImGui::SetCursorPos(ImVec2(
                    (windowSize.x - contentSize.x) * 0.5f,
                    (windowSize.y - contentSize.y) * 0.5f
                ));

                ImGui::BeginChild("InitContent", contentSize, true);

                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                ImGui::SetCursorPosX((contentSize.x - ImGui::CalcTextSize("HALFSWORD ANALYZER").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "HALFSWORD ANALYZER");
                ImGui::PopFont();

                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::SetCursorPosX((contentSize.x - ImGui::CalcTextSize("Initialization Status").x) * 0.5f);
                ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.8f), "Initialization Status");

                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::SetCursorPosX(contentSize.x * 0.1f);
                DrawProgressBar(s_InitProgress, ImVec2(contentSize.x * 0.8f, 24));

                ImGui::Spacing();
                ImGui::Spacing();

                for (const auto& stage : s_InitStages) {
                    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "%s:", stage.name.c_str());
                    ImGui::SameLine(contentSize.x * 0.6f);

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
                ImGui::Spacing();

                ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Initialization Log:");
                ImGui::BeginChild("LogMessages", ImVec2(contentSize.x - 16, contentSize.y * 0.3f), true);

                for (const auto& message : s_InitializationMessages) {
                    ImGui::TextWrapped("%s", message.c_str());
                }

                ImGui::SetScrollY(ImGui::GetScrollMaxY());
                ImGui::EndChild();

                if (s_LevelDataCollected) {
                    ImGui::Spacing();
                    ImGui::Spacing();

                    float time = ImGui::GetTime();
                    float alpha = 0.5f + 0.5f * sinf(time * 2.0f);

                    const char* pressKeyText = "Press any key to continue...";
                    ImVec2 textSize = ImGui::CalcTextSize(pressKeyText);
                    ImGui::SetCursorPosX((contentSize.x - textSize.x) * 0.5f);
                    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, alpha), "%s", pressKeyText);

                    ImGui::Spacing();

                    const char* insertKeyText = "(Press INSERT at any time to access the Level Selector)";
                    textSize = ImGui::CalcTextSize(insertKeyText);
                    ImGui::SetCursorPosX((contentSize.x - textSize.x) * 0.5f);
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 0.7f), "%s", insertKeyText);
                }

                ImGui::EndChild();
            }
            ImGui::End();

            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor();
        }

        void ImGuiManager::RenderMainInterface() {
            RECT windowRect;
            GetClientRect(s_GameWindow, &windowRect);
            ImVec2 windowSize(
                static_cast<float>(windowRect.right - windowRect.left),
                static_cast<float>(windowRect.bottom - windowRect.top)
            );

            ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(500, 700), ImGuiCond_FirstUseEver);

            if (ImGui::Begin("Halfsword Analyzer", nullptr, ImGuiWindowFlags_NoCollapse)) {
                if (ImGui::BeginTabBar("MainTabs")) {
                    if (ImGui::BeginTabItem("Level Data")) {
                        ImGui::Text("Discovered Levels: %zu", s_LevelInfoJson.size());
                        ImGui::Separator();

                        if (ImGui::BeginTable("LevelTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {
                            ImGui::TableSetupColumn("Map Name");
                            ImGui::TableSetupColumn("Content Path");
                            ImGui::TableHeadersRow();

                            for (const auto& levelInfo : s_LevelInfoJson) {
                                ImGui::TableNextRow();

                                ImGui::TableSetColumnIndex(0);
                                ImGui::Text("%s", levelInfo["mapName"].get<std::string>().c_str());

                                ImGui::TableSetColumnIndex(1);
                                ImGui::Text("%s", levelInfo["contentPath"].get<std::string>().c_str());
                            }

                            ImGui::EndTable();
                        }

                        ImGui::Spacing();
                        ImGui::Spacing();

                        bool refreshClicked = false;
                        DrawModernButton("Refresh Level Data", &refreshClicked, ImVec2(200, 40));

                        if (refreshClicked) {
                            s_LevelInfoJson.clear();
                            s_LevelDataCollected = false;
                            s_InitializationMessages.push_back("Refreshing level data...");
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Position Tracker")) {
                        ImGui::Text("Current Level: %s", PositionTracker::GetCurrentLevelName().c_str());
                        ImGui::Separator();

                        bool recordClicked = false;
                        DrawModernButton("Record Current Position", &recordClicked, ImVec2(200, 40));

                        if (recordClicked) {
                            PositionTracker::RecordPlayerPosition();
                            PositionTracker::LogPositionInfo();
                            s_InitializationMessages.push_back("Recorded player position");
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Settings")) {
                        ImGui::Checkbox("Show ImGui Demo Window", &s_ShowDemo);

                        ImGui::Separator();
                        ImGui::Text("Initialization Log:");

                        if (ImGui::BeginChild("SettingsLogMessages", ImVec2(0, 300), true)) {
                            for (const auto& message : s_InitializationMessages) {
                                ImGui::TextWrapped("%s", message.c_str());
                            }
                        }
                        ImGui::EndChild();

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
            }
            ImGui::End();
        }

        void ImGuiManager::RenderLevelSelector() {
            RECT windowRect;
            GetClientRect(s_GameWindow, &windowRect);
            ImVec2 windowSize(
                static_cast<float>(windowRect.right - windowRect.left),
                static_cast<float>(windowRect.bottom - windowRect.top)
            );

            const float width = 400.0f;
            const float height = 300.0f;

            ImGui::SetNextWindowPos(ImVec2((windowSize.x - width) * 0.5f, (windowSize.y - height) * 0.5f), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

            if (ImGui::Begin("Level Selector", &s_ShowLevelSelector,
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoSavedSettings)) {

                ImGui::SetCursorPosX((width - ImGui::CalcTextSize("LEVEL SELECTOR").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "LEVEL SELECTOR");

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Current Level:");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", PositionTracker::GetCurrentLevelName().c_str());

                ImGui::Spacing();
                ImGui::Spacing();

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
                    ImGui::BeginChild("LevelInfo", ImVec2(0, 120), true);

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
                }
                else {
                    ImGui::BeginChild("LevelInfo", ImVec2(0, 120), true);
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Select a level to view its details");
                    ImGui::EndChild();
                }

                ImGui::Spacing();

                bool loadClicked = false;
                ImGui::SetCursorPosX((width - 120) * 0.5f);
                DrawModernButton("Load Level", &loadClicked, ImVec2(120, 40));

                if (loadClicked && s_SelectedLevelIndex >= 0 && s_SelectedLevelIndex < s_LevelInfoJson.size()) {
                    std::string mapName = s_LevelInfoJson[s_SelectedLevelIndex]["mapName"].get<std::string>();
                    SwitchLevel(mapName);
                }

                ImGui::Spacing();

                ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 0.5f), "Press INSERT to toggle this menu");
            }
            ImGui::End();

            ImGui::PopStyleVar(2);
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

            s_ShowLevelSelector = false;
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

        bool ImGuiManager::IsInitialized() {
            return s_Initialized;
        }

        nlohmann::json& ImGuiManager::GetLevelInfoJson() {
            return s_LevelInfoJson;
        }

        LRESULT CALLBACK ImGuiManager::WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
            if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
                return true;
            }

            if (msg == WM_KEYDOWN && wParam == VK_INSERT) {
                if (s_LevelDataCollected && s_InitScreenClosed) {
                    s_ShowLevelSelector = !s_ShowLevelSelector;
                    return true;
                }
            }

            if (!s_InitScreenClosed && s_LevelDataCollected && msg == WM_KEYDOWN) {
                s_InitScreenClosed = true;
                return true;
            }

            return CallWindowProc(s_OriginalWndProc, hWnd, msg, wParam, lParam);
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

        void ImGuiManager::DrawProgressBar(float progress, const ImVec2& size) {
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.0f, 0.7f, 1.0f, 0.8f));

            std::string progressPercentage = std::to_string(static_cast<int>(progress * 100)) + "%";
            ImGui::ProgressBar(progress, size, progressPercentage.c_str());

            ImGui::PopStyleColor(2);
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

        void ImGuiManager::PopModernStyle() {
            ImGui::GetIO().FontGlobalScale = 1.0f;
        }
    }
}