#include "Logger.h"
#include <Windows.h>
#include <iostream>
#include <cstdarg>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace HalfswordAnalyzer {
    namespace Utils {
        bool Logger::s_Initialized = false;
        bool Logger::Initialize() {
            if (s_Initialized) {
                return true;
            }

            int retryCount = 0;
            const int maxRetries = 5;

            while (retryCount < maxRetries) {
                if (AllocConsole()) {
                    break;
                }

                DWORD errorCode = GetLastError();

                if (errorCode == ERROR_ACCESS_DENIED) {
                    Sleep(1000);
                    retryCount++;
                    continue;
                }

                if (errorCode == 0x1F) {
                    break;
                }

                Sleep(1000);
                retryCount++;
            }

            FILE* dummy;
            freopen_s(&dummy, "CONOUT$", "w", stdout);
            freopen_s(&dummy, "CONOUT$", "w", stderr);

            SetConsoleTitle(L"Halfsword Analyzer Console");

            char dllPath[MAX_PATH];
            GetModuleFileNameA(GetModuleHandleA("GFSDK_Aftermath_Lib.x64.dll"), dllPath, MAX_PATH);
            bool isEarlyLoad = (GetLastError() == 0);

            s_Initialized = true;

            if (isEarlyLoad) {
                Info("Halfsword Analyzer - Early Load Mode");
                Info("Loaded as GFSDK_Aftermath_Lib.x64.dll");
            }
            else {
                Info("Halfsword Analyzer - Standard Injection Mode");
            }

            return true;
        }
        void Logger::Shutdown() {
            if (s_Initialized) {
                FreeConsole();
                s_Initialized = false;
            }
        }
        static std::string GetTimestamp() {
            auto now = std::time(nullptr);

            std::tm tm_buf;
            localtime_s(&tm_buf, &now);

            std::ostringstream oss;
            oss << std::put_time(&tm_buf, "%H:%M:%S");
            return oss.str();
        }
        void Logger::Info(const char* fmt, ...) {
            if (!s_Initialized) {
                return;
            }
            char buffer[4096];
            va_list args;
            va_start(args, fmt);
            vsnprintf(buffer, sizeof(buffer), fmt, args);
            va_end(args);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("[%s] [INFO] %s\n", GetTimestamp().c_str(), buffer);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        void Logger::Warning(const char* fmt, ...) {
            if (!s_Initialized) {
                return;
            }
            char buffer[4096];
            va_list args;
            va_start(args, fmt);
            vsnprintf(buffer, sizeof(buffer), fmt, args);
            va_end(args);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("[%s] [WARN] %s\n", GetTimestamp().c_str(), buffer);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        void Logger::Error(const char* fmt, ...) {
            if (!s_Initialized) {
                return;
            }
            char buffer[4096];
            va_list args;
            va_start(args, fmt);
            vsnprintf(buffer, sizeof(buffer), fmt, args);
            va_end(args);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("[%s] [ERROR] %s\n", GetTimestamp().c_str(), buffer);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }
}