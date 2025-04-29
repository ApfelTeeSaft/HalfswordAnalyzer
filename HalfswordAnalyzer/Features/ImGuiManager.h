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
        static void CreateRenderTarget();
        static void CleanupRenderTarget();
        static bool CreateDeviceD3D(HWND hWnd);
        static void CleanupDeviceD3D();

        class ImGuiManager {
        public:
            /**
             * Initializes the ImGui system with a separate window
             * @return True if initialization was successful
             */
            static bool Initialize();

            /**
             * Shuts down the ImGui system
             */
            static void Shutdown();

            /**
             * Shows or hides the ImGui window
             * @param visible Whether the window should be visible
             */
            static void SetVisible(bool visible);

            /**
             * Toggles the window visibility
             */
            static void ToggleVisibility();

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
            static bool s_Visible;
            static bool s_Running;
            static bool s_ShowDemo;
            static bool s_CoreInitialized;
            static bool s_GameInitialized;
            static bool s_LevelDataCollected;
            static bool s_InitScreenClosed;
            static bool s_ShowLevelSelector;
            static HWND s_GameWindow;
            static HWND s_ImGuiWindow;
            static WNDPROC s_OriginalWndProc;
            static ImGuiContext* s_ImGuiContext;
            static HANDLE s_RenderThread;

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

            /**
             * Creates the external ImGui window
             * @return True if creation was successful
             */
            static bool CreateExternalWindow();

            /**
             * Thread procedure for rendering the window
             * @param lpParam Thread parameter
             * @return Thread result
             */
            static DWORD WINAPI RenderThreadProc(LPVOID lpParam);

            /**
             * Window procedure for the ImGui window
             */
            static LRESULT CALLBACK WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

            /**
             * Window procedure for the game window (to capture INSERT key)
             */
            static LRESULT CALLBACK GameWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

            /**
             * Renders the main interface
             */
            static void RenderMainInterface();

            /**
             * Renders the level selector tab
             */
            static void RenderLevelSelector();

            /**
             * Renders the position tracker tab
             */
            static void RenderPositionTab();

            /**
             * Renders the settings tab
             */
            static void RenderSettingsTab();

            /**
             * Collect level data from the game
             */
            static void CollectLevelData();

            /**
             * Switch to a specific level in the game
             * @param levelName The name of the level to switch to
             */
            static void SwitchLevel(const std::string& levelName);

            /**
             * Style helpers for ImGui
             */
            static void PushModernStyle();
            static void DrawModernButton(const char* label, bool* clicked, const ImVec2& size);
        };
    }
}