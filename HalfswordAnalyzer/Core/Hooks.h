#pragma once

#include <Windows.h>

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
    }
}