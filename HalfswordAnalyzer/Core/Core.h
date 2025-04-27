#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <map>

#include "../SDK/SDK.hpp"

namespace HalfswordAnalyzer {
    namespace Core {
        /**
         * Initializes the core functionality of the analyzer
         * @return True if initialization was successful
         */
        bool Initialize();

        /**
         * Shuts down and cleans up the analyzer
         */
        void Shutdown();

        /**
         * Gets the module handle of the game
         * @return HMODULE of the game executable
         */
        HMODULE GetGameModule();

        /**
         * Gets the window handle of the game
         * @return HWND of the game window
         */
        HWND GetGameWindow();

        /**
         * Returns whether the F5 hotkey was registered successfully
         * @return True if hotkey is active
         */
        bool IsHotkeyActive();
    }
}