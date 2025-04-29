#include "ImGuiManager.h"
#include "../Core/Core.h"
#include "../Utils/Logger.h"
#include "../Utils/StringUtils.h"
#include "../Features/ConsoleManager.h"
#include "../Features/PositionTracker.h"

#include "../imgui.h"
#include "../imgui_internal.h"
#include "../backends/imgui_impl_win32.h"
#include "../backends/imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

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

        ID3D12Device* ImGuiManager::s_Device = NULL;
        ID3D12CommandQueue* ImGuiManager::s_CommandQueue = NULL;
        ID3D12DescriptorHeap* ImGuiManager::s_DescriptorHeap = NULL;
        ID3D12GraphicsCommandList* ImGuiManager::s_CommandList = NULL;
        ID3D12CommandAllocator* ImGuiManager::s_CommandAllocator = NULL;
        IDXGISwapChain3* ImGuiManager::s_SwapChain = NULL;
        UINT ImGuiManager::s_FrameIndex = 0;
        ID3D12Resource* ImGuiManager::s_RenderTargets[2] = { NULL, NULL };
        UINT ImGuiManager::s_BackBufferCount = 2;
        bool ImGuiManager::s_DeviceCaptured = false;
        bool ImGuiManager::s_CommandQueueCaptured = false;
        bool ImGuiManager::s_SwapChainCaptured = false;

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

        void ImGuiManager::CaptureDevice(ID3D12Device* device) {
            if (!s_Device && device) {
                s_Device = device;
                device->AddRef();
                s_DeviceCaptured = true;
                Utils::Logger::Info("D3D12 Device captured: 0x%p", device);
                TryInitialize();
            }
        }

        void ImGuiManager::CaptureCommandQueue(ID3D12CommandQueue* queue) {
            if (!s_CommandQueue && queue && queue->GetDesc().Type == D3D12_COMMAND_LIST_TYPE_DIRECT) {
                s_CommandQueue = queue;
                queue->AddRef();
                s_CommandQueueCaptured = true;
                Utils::Logger::Info("D3D12 CommandQueue captured: 0x%p", queue);
                TryInitialize();
            }
        }

        void ImGuiManager::CaptureSwapChain(IDXGISwapChain3* swapChain) {
            if (!s_SwapChain && swapChain) {
                s_SwapChain = swapChain;
                swapChain->AddRef();
                DXGI_SWAP_CHAIN_DESC desc;
                swapChain->GetDesc(&desc);
                s_BackBufferCount = desc.BufferCount;

                s_SwapChainCaptured = true;
                Utils::Logger::Info("DXGI SwapChain captured: 0x%p (Buffer Count: %d)", swapChain, s_BackBufferCount);
                TryInitialize();
            }
        }

        HRESULT STDMETHODCALLTYPE ImGuiManager::Present_Hook(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags) {
            if (!s_SwapChain) {
                CaptureSwapChain(pSwapChain);
            }

            if (s_Initialized && pSwapChain == s_SwapChain) {
                s_FrameIndex = pSwapChain->GetCurrentBackBufferIndex();

                s_CommandAllocator->Reset();

                s_CommandList->Reset(s_CommandAllocator, NULL);

                D3D12_RESOURCE_BARRIER barrier = {};
                barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier.Transition.pResource = s_RenderTargets[s_FrameIndex];
                barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
                barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
                barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                s_CommandList->ResourceBarrier(1, &barrier);

                ImGui_ImplDX12_NewFrame();
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

                s_CommandList->SetDescriptorHeaps(1, &s_DescriptorHeap);
                ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), s_CommandList);

                barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
                barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
                s_CommandList->ResourceBarrier(1, &barrier);

                s_CommandList->Close();

                ID3D12CommandList* ppCommandLists[] = { s_CommandList };
                s_CommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
            }

            return S_OK;
        }

        bool ImGuiManager::Initialize() {
            if (s_Initialized) {
                return true;
            }

            Utils::Logger::Info("Initializing ImGui Manager for DirectX 12...");

            s_GameWindow = Core::GetGameWindow();
            if (!s_GameWindow) {
                Utils::Logger::Error("Failed to get game window for ImGui initialization");
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

            s_InitializationMessages.push_back("ImGui Manager initialization started");
            s_InitializationMessages.push_back("Press INSERT at any time to access Level Selector");

            Utils::Logger::Info("ImGui Manager initialized - waiting for DirectX 12 resources");
            return true;
        }

        void ImGuiManager::TryInitialize() {
            if (s_Initialized || !s_DeviceCaptured || !s_CommandQueueCaptured) {
                return;
            }

            Utils::Logger::Info("All D3D12 resources captured, initializing ImGui...");

            if (!CreateResources()) {
                Utils::Logger::Error("Failed to create ImGui resources");
                return;
            }
            if (!InitializeImGui()) {
                Utils::Logger::Error("Failed to initialize ImGui");
                return;
            }

            s_Initialized = true;
            Utils::Logger::Info("ImGui initialized with DirectX 12 successfully");
            s_InitializationMessages.push_back("ImGui initialized with DirectX 12 successfully");
        }

        bool ImGuiManager::CreateResources() {
            D3D12_DESCRIPTOR_HEAP_DESC desc = {};
            desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
            desc.NumDescriptors = 1;
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
            if (FAILED(s_Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&s_DescriptorHeap)))) {
                Utils::Logger::Error("Failed to create descriptor heap");
                return false;
            }

            if (FAILED(s_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&s_CommandAllocator)))) {
                Utils::Logger::Error("Failed to create command allocator");
                return false;
            }

            if (FAILED(s_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, s_CommandAllocator, NULL, IID_PPV_ARGS(&s_CommandList)))) {
                Utils::Logger::Error("Failed to create command list");
                return false;
            }

            s_CommandList->Close();

            if (s_SwapChain && s_BackBufferCount > 0) {
                for (UINT i = 0; i < s_BackBufferCount; i++) {
                    if (s_RenderTargets[i]) {
                        s_RenderTargets[i]->Release();
                        s_RenderTargets[i] = NULL;
                    }
                    if (FAILED(s_SwapChain->GetBuffer(i, IID_PPV_ARGS(&s_RenderTargets[i])))) {
                        Utils::Logger::Warning("Failed to get render target %d", i);
                    }
                }
            }

            return true;
        }

        void ImGuiManager::Shutdown() {
            if (!s_Initialized) {
                return;
            }

            if (s_GameWindow && s_OriginalWndProc) {
                SetWindowLongPtr(s_GameWindow, GWLP_WNDPROC, (LONG_PTR)s_OriginalWndProc);
            }

            ImGui_ImplDX12_Shutdown();
            ImGui_ImplWin32_Shutdown();
            if (s_ImGuiContext) {
                ImGui::DestroyContext(s_ImGuiContext);
                s_ImGuiContext = NULL;
            }

            if (s_DescriptorHeap) { s_DescriptorHeap->Release(); s_DescriptorHeap = NULL; }
            if (s_CommandList) { s_CommandList->Release(); s_CommandList = NULL; }
            if (s_CommandAllocator) { s_CommandAllocator->Release(); s_CommandAllocator = NULL; }

            for (UINT i = 0; i < s_BackBufferCount; i++) {
                if (s_RenderTargets[i]) {
                    s_RenderTargets[i]->Release();
                    s_RenderTargets[i] = NULL;
                }
            }

            if (s_Device) { s_Device->Release(); s_Device = NULL; }
            if (s_CommandQueue) { s_CommandQueue->Release(); s_CommandQueue = NULL; }
            if (s_SwapChain) { s_SwapChain->Release(); s_SwapChain = NULL; }

            s_DeviceCaptured = false;
            s_CommandQueueCaptured = false;
            s_SwapChainCaptured = false;

            Utils::Logger::Info("ImGui Manager shutdown complete");
            s_Initialized = false;
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

            if (!ImGui_ImplDX12_Init(s_Device, s_BackBufferCount,
                DXGI_FORMAT_R8G8B8A8_UNORM, s_DescriptorHeap,
                s_DescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
                s_DescriptorHeap->GetGPUDescriptorHandleForHeapStart())) {
                Utils::Logger::Error("Failed to initialize ImGui for DirectX 12");
                return false;
            }

            PushModernStyle();

            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

            return true;
        }

        bool ImGuiManager::SetupRenderState() {
            return true;
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

        bool ImGuiManager::IsInitialized() {
            return s_Initialized;
        }

        nlohmann::json& ImGuiManager::GetLevelInfoJson() {
            return s_LevelInfoJson;
        }
    }
}