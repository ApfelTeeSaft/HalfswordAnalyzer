#include "Hooks.h"
#include "Core.h"
#include "../Features/LevelAnalyzer.h"
#include "../Features/PositionTracker.h"
#include "../Features/ImGuiManager.h"
#include "../Utils/Logger.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include "../detours.h"

namespace HalfswordAnalyzer {
    namespace Hooks {
        namespace {
            WNDPROC g_OriginalWndProc = nullptr;

            typedef HRESULT(WINAPI* D3D12CreateDevice_t)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**);
            typedef HRESULT(WINAPI* Present_t)(IDXGISwapChain3*, UINT, UINT);
            typedef void(WINAPI* ExecuteCommandLists_t)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*);
            typedef HRESULT(WINAPI* CreateDXGIFactory_t)(REFIID, void**);

            D3D12CreateDevice_t g_OriginalD3D12CreateDevice = nullptr;
            Present_t g_OriginalPresent = nullptr;
            ExecuteCommandLists_t g_OriginalExecuteCommandLists = nullptr;
            CreateDXGIFactory_t g_OriginalCreateDXGIFactory = nullptr;

            void* g_PresentAddress = nullptr;
            void* g_ExecuteCommandListsAddress = nullptr;

            void WINAPI ExecuteCommandLists_Hook(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* const* ppCommandLists) {
                g_OriginalExecuteCommandLists(queue, NumCommandLists, ppCommandLists);

            }

            HRESULT WINAPI Present_Hook(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags) {
                return g_OriginalPresent(pSwapChain, SyncInterval, Flags);
            }

            HRESULT WINAPI D3D12CreateDevice_Hook(IUnknown* pAdapter, D3D_FEATURE_LEVEL MinimumFeatureLevel, REFIID riid, void** ppDevice) {
                HRESULT hr = g_OriginalD3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);

                if (SUCCEEDED(hr) && ppDevice && *ppDevice) {
                    Utils::Logger::Info("D3D12CreateDevice hook called, device created: 0x%p", *ppDevice);

                }

                return hr;
            }

            HRESULT WINAPI CreateDXGIFactory_Hook(REFIID riid, void** ppFactory) {
                HRESULT hr = g_OriginalCreateDXGIFactory(riid, ppFactory);

                if (SUCCEEDED(hr) && ppFactory && *ppFactory) {
                    Utils::Logger::Info("CreateDXGIFactory hook called, factory created: 0x%p", *ppFactory);
                }

                return hr;
            }
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

            HMODULE d3d12Module = GetModuleHandleA("d3d12.dll");
            if (d3d12Module) {
                Utils::Logger::Info("Found D3D12 module: 0x%p", d3d12Module);

                g_OriginalD3D12CreateDevice = (D3D12CreateDevice_t)GetProcAddress(d3d12Module, "D3D12CreateDevice");
                if (g_OriginalD3D12CreateDevice) {
                    Utils::Logger::Info("Found D3D12CreateDevice function at 0x%p", g_OriginalD3D12CreateDevice);

                    DetourTransactionBegin();
                    DetourUpdateThread(GetCurrentThread());
                    DetourAttach(&(PVOID&)g_OriginalD3D12CreateDevice, D3D12CreateDevice_Hook);
                    DetourTransactionCommit();

                    Utils::Logger::Info("D3D12CreateDevice hook installed");
                }
                else {
                    Utils::Logger::Error("Failed to find D3D12CreateDevice function");
                }
            }
            else {
                Utils::Logger::Error("Failed to find D3D12 module, trying to use GetSystemDirectory");

                char systemDir[MAX_PATH];
                GetSystemDirectoryA(systemDir, MAX_PATH);
                strcat_s(systemDir, "\\d3d12.dll");

                d3d12Module = LoadLibraryA(systemDir);
                if (d3d12Module) {
                    Utils::Logger::Info("Loaded D3D12 module: 0x%p", d3d12Module);

                    g_OriginalD3D12CreateDevice = (D3D12CreateDevice_t)GetProcAddress(d3d12Module, "D3D12CreateDevice");
                    if (g_OriginalD3D12CreateDevice) {
                        Utils::Logger::Info("Found D3D12CreateDevice function at 0x%p", g_OriginalD3D12CreateDevice);

                        DetourTransactionBegin();
                        DetourUpdateThread(GetCurrentThread());
                        DetourAttach(&(PVOID&)g_OriginalD3D12CreateDevice, D3D12CreateDevice_Hook);
                        DetourTransactionCommit();

                        Utils::Logger::Info("D3D12CreateDevice hook installed");
                    }
                    else {
                        Utils::Logger::Error("Failed to find D3D12CreateDevice function");
                    }
                }
                else {
                    Utils::Logger::Error("Failed to load D3D12 module");
                }
            }

            HMODULE dxgiModule = GetModuleHandleA("dxgi.dll");
            if (dxgiModule) {
                Utils::Logger::Info("Found DXGI module: 0x%p", dxgiModule);

                g_OriginalCreateDXGIFactory = (CreateDXGIFactory_t)GetProcAddress(dxgiModule, "CreateDXGIFactory");
                if (g_OriginalCreateDXGIFactory) {
                    Utils::Logger::Info("Found CreateDXGIFactory function at 0x%p", g_OriginalCreateDXGIFactory);

                    DetourTransactionBegin();
                    DetourUpdateThread(GetCurrentThread());
                    DetourAttach(&(PVOID&)g_OriginalCreateDXGIFactory, CreateDXGIFactory_Hook);
                    DetourTransactionCommit();

                    Utils::Logger::Info("CreateDXGIFactory hook installed");
                }
                else {
                    Utils::Logger::Error("Failed to find CreateDXGIFactory function");
                }
            }
            else {
                Utils::Logger::Error("Failed to find DXGI module");
            }

            return true;
        }

        void Shutdown() {
            HWND gameWindow = Core::GetGameWindow();
            if (gameWindow && g_OriginalWndProc) {
                SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)g_OriginalWndProc);
                Utils::Logger::Info("Window procedure hook removed");
            }

            if (g_OriginalD3D12CreateDevice) {
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourDetach(&(PVOID&)g_OriginalD3D12CreateDevice, D3D12CreateDevice_Hook);
                DetourTransactionCommit();
                Utils::Logger::Info("D3D12CreateDevice hook removed");
            }

            if (g_OriginalCreateDXGIFactory) {
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourDetach(&(PVOID&)g_OriginalCreateDXGIFactory, CreateDXGIFactory_Hook);
                DetourTransactionCommit();
                Utils::Logger::Info("CreateDXGIFactory hook removed");
            }

            if (g_OriginalPresent) {
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourDetach(&(PVOID&)g_OriginalPresent, Present_Hook);
                DetourTransactionCommit();
                Utils::Logger::Info("Present hook removed");
            }

            if (g_OriginalExecuteCommandLists) {
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourDetach(&(PVOID&)g_OriginalExecuteCommandLists, ExecuteCommandLists_Hook);
                DetourTransactionCommit();
                Utils::Logger::Info("ExecuteCommandLists hook removed");
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

        bool IsD3D12CreateDeviceHooked() {
            return g_OriginalD3D12CreateDevice != nullptr;
        }

        bool IsPresentHooked() {
            return g_OriginalPresent != nullptr;
        }

        bool IsExecuteCommandListsHooked() {
            return g_OriginalExecuteCommandLists != nullptr;
        }
    }
}