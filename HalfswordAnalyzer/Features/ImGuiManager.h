#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../SDK/SDK.hpp"

struct ImGuiContext;
struct ImVec2;
struct ImVec4;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;

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
             * Renders the ImGui interface
             * Call this every frame
             */
            static void Render();

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
            static ID3D11Device* s_Device;
            static ID3D11DeviceContext* s_DeviceContext;
            static IDXGISwapChain* s_SwapChain;
            static ID3D11RenderTargetView* s_RenderTargetView;
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

            static bool InitializeDirectX();

            static bool InitializeImGui();

            static void RenderInitializationScreen();

            static void RenderMainInterface();

            static void RenderLevelSelector();

            static void SwitchLevel(const std::string& levelName);

            static void CollectLevelData();

            static void DrawModernButton(const char* label, bool* clicked, const ImVec2& size);
            static void DrawProgressBar(float progress, const ImVec2& size);
            static void PushModernStyle();
            static void PopModernStyle();
        };
    }
}