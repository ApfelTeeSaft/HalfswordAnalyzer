#pragma once

#include <string>

namespace HalfswordAnalyzer {
    namespace Utils {
        class Logger {
        public:
            /**
             * Initializes the logger
             * @return True if initialization was successful
             */
            static bool Initialize();

            /**
             * Shuts down the logger
             */
            static void Shutdown();

            /**
             * Logs an info message
             * @param fmt Format string
             * @param ... Format arguments
             */
            static void Info(const char* fmt, ...);

            /**
             * Logs a warning message
             * @param fmt Format string
             * @param ... Format arguments
             */
            static void Warning(const char* fmt, ...);

            /**
             * Logs an error message
             * @param fmt Format string
             * @param ... Format arguments
             */
            static void Error(const char* fmt, ...);

        private:
            static bool s_Initialized;
        };
    }
}