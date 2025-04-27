#include "Hooks.h"
#include "Core.h"
#include "../Features/LevelAnalyzer.h"
#include "../Features/PositionTracker.h"
#include "../Utils/Logger.h"

#include "../detours.h"
#pragma comment(lib, "detours.lib")

namespace HalfswordAnalyzer {
    namespace Hooks {
        namespace {
            WNDPROC g_OriginalWndProc = nullptr;
        }

        bool Initialize() {
            HWND gameWindow = Core::GetGameWindow();
            if (!gameWindow) {
                return false;
            }

            g_OriginalWndProc = (WNDPROC)GetWindowLongPtr(gameWindow, GWLP_WNDPROC);
            if (!g_OriginalWndProc) {
                Utils::Logger::Error("Failed to get original window procedure");
                return false;
            }

            if (!SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)WndProcHook)) {
                Utils::Logger::Error("Failed to set window procedure hook");
                return false;
            }

            Utils::Logger::Info("Window procedure hook installed");
            return true;
        }

        void Shutdown() {
            HWND gameWindow = Core::GetGameWindow();
            if (gameWindow && g_OriginalWndProc) {
                SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)g_OriginalWndProc);
                Utils::Logger::Info("Window procedure hook removed");
            }
        }

        LRESULT CALLBACK WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            if (uMsg == WM_KEYDOWN && wParam == VK_F5) {
                Utils::Logger::Info("\n\n========== DUMPING GAME INFO ==========");
                Features::LevelAnalyzer::DumpWorldInfo();
                Utils::Logger::Info("========== DUMP COMPLETE ==========\n");
                return 0;
            }

            if (uMsg == WM_KEYDOWN && wParam == VK_F9) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO csbi;
                GetConsoleScreenBufferInfo(hConsole, &csbi);

                COORD topLeft = { 0, 0 };
                DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
                DWORD written;

                FillConsoleOutputCharacter(hConsole, ' ', length, topLeft, &written);
                FillConsoleOutputAttribute(hConsole, csbi.wAttributes, length, topLeft, &written);
                SetConsoleCursorPosition(hConsole, topLeft);

                Utils::Logger::Info("Console cleared");
                return 0;
            }

            if (uMsg == WM_KEYDOWN && wParam == VK_F6) {
                Utils::Logger::Info("\n\n========== RECORDING PLAYER POSITION ==========");
                Features::PositionTracker::RecordPlayerPosition();
                Features::PositionTracker::LogPositionInfo();
                Utils::Logger::Info("========== POSITION RECORDED ==========\n");
                return 0;
            }

            return CallWindowProc(g_OriginalWndProc, hWnd, uMsg, wParam, lParam);
        }

        WNDPROC GetOriginalWndProc() {
            return g_OriginalWndProc;
        }
    }
}