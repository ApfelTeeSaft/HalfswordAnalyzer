#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../SDK/SDK.hpp"
#include <dxgi1_4.h>
#include <d3d12.h>

struct ImGuiContext;
struct ImVec2;
struct ImVec4;

namespace HalfswordAnalyzer {
    namespace Features {
        class ImGuiManager {
        public:
            /**
             * Initializes the ImGui system
             * @return True if initialization was successful
             */
            static bool Initialize();

            /**
             * Shuts down the ImGui system
             */
            static void Shutdown();

            /**
             * Present hook callback for rendering ImGui
             * @param pSwapChain The game's swap chain
             * @param SyncInterval Sync interval
             * @param Flags Presentation flags
             * @return HRESULT from original function
             */
            static HRESULT WINAPI Present_Hook(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);

            /**
             * Capture the D3D12 device for ImGui initialization
             * @param device The D3D12 device to capture
             */
            static void CaptureDevice(ID3D12Device* device);

            /**
             * Capture the D3D12 command queue for ImGui rendering
             * @param commandQueue The D3D12 command queue to capture
             */
            static void CaptureCommandQueue(ID3D12CommandQueue* commandQueue);

            /**
             * Capture the DXGI swap chain for ImGui rendering
             * @param swapChain The DXGI swap chain to capture
             */
            static void CaptureSwapChain(IDXGISwapChain3* swapChain);

            /**
             * Checks if ImGui is initialized
             * @return True if ImGui is initialized
             */
            static bool IsInitialized();

            /**
             * Get the JSON object containing level information
             * @return JSON object with level info
             */
            static nlohmann::json& GetLevelInfoJson();

        private:
            static bool s_Initialized;
            static bool s_ShowDemo;
            static bool s_CoreInitialized;
            static bool s_GameInitialized;
            static bool s_LevelDataCollected;
            static bool s_InitScreenClosed;
            static bool s_ShowLevelSelector;
            static HWND s_GameWindow;
            static WNDPROC s_OriginalWndProc;
            static ImGuiContext* s_ImGuiContext;

            static ID3D12Device* s_Device;
            static ID3D12CommandQueue* s_CommandQueue;
            static ID3D12DescriptorHeap* s_DescriptorHeap;
            static ID3D12GraphicsCommandList* s_CommandList;
            static ID3D12CommandAllocator* s_CommandAllocator;
            static IDXGISwapChain3* s_SwapChain;
            static UINT s_FrameIndex;
            static ID3D12Resource* s_RenderTargets[2];
            static UINT s_BackBufferCount;
            static bool s_DeviceCaptured;
            static bool s_CommandQueueCaptured;
            static bool s_SwapChainCaptured;

            static nlohmann::json s_LevelInfoJson;
            static std::vector<std::string> s_InitializationMessages;
            static float s_InitProgress;
            static int s_SelectedLevelIndex;
            struct InitStage {
                std::string name;
                std::string status;
                bool completed;
            };
            static std::vector<InitStage> s_InitStages;

            static LRESULT CALLBACK WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

            static bool InitializeImGui();
            static bool SetupRenderState();
            static bool CreateResources();

            static void RenderInitializationScreen();
            static void RenderMainInterface();
            static void RenderLevelSelector();
            static void SwitchLevel(const std::string& levelName);
            static void CollectLevelData();

            static void DrawModernButton(const char* label, bool* clicked, const ImVec2& size);
            static void DrawProgressBar(float progress, const ImVec2& size);
            static void PushModernStyle();
            static void PopModernStyle();

            static void TryInitialize();
        };
    }
}