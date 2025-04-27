#pragma once

#include "../SDK/SDK.hpp"

namespace HalfswordAnalyzer {
    namespace Features {
        class ConsoleManager {
        public:
            /**
             * Enables the Unreal Engine console
             * @return True if the console was enabled successfully
             */
            static bool EnableConsole();

            /**
             * Checks if the console is currently enabled
             * @return True if the console is enabled
             */
            static bool IsConsoleEnabled();

        private:
            static bool s_ConsoleEnabled;
        };
    }
}