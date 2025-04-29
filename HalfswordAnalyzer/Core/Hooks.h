#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>

namespace HalfswordAnalyzer {
    namespace Hooks {
        /**
         * Initializes all hooks
         * @return True if initialization was successful
         */
        bool Initialize();

        /**
         * Shuts down and restores all hooks
         */
        void Shutdown();

        /**
         * Window procedure hook callback
         */
        LRESULT CALLBACK WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        /**
         * Gets the original window procedure
         * @return Pointer to the original WndProc
         */
        WNDPROC GetOriginalWndProc();

        /**
         * Gets the D3D12CreateDevice Hook status
         * @return True if the D3D12CreateDevice hook is installed
         */
        bool IsD3D12CreateDeviceHooked();

        /**
         * Gets the Present Hook status
         * @return True if the Present hook is installed
         */
        bool IsPresentHooked();

        /**
         * Gets the ExecuteCommandLists Hook status
         * @return True if the ExecuteCommandLists hook is installed
         */
        bool IsExecuteCommandListsHooked();

        /**
         * Sets up hooks for D3D12 functions
         * Should be called after window hooks are installed
         * @return True if hooks were installed successfully
         */
        bool SetupD3D12Hooks();

        /**
         * Removes all D3D12 hooks
         */
        void RemoveD3D12Hooks();
    }
}