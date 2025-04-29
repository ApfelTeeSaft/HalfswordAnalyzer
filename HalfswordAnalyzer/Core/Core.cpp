#include "Core.h"
#include "Hooks.h"
#include "../Features/ConsoleManager.h"
#include "../Features/PositionTracker.h"
#include "../Utils/Logger.h"
#include "../Utils/Memory.h"

namespace HalfswordAnalyzer {
    namespace Core {
        namespace {
            HMODULE g_GameModule = nullptr;
            HWND g_GameWindow = nullptr;
            bool g_HotkeyActive = false;
            bool g_Running = true;
            HANDLE g_UpdateThread = nullptr;

            DWORD WINAPI UpdateThreadProc(LPVOID lpParam) {
                while (g_Running) {
                    Features::PositionTracker::Update();

                    Sleep(1000);
                }
                return 0;
            }
        }

        bool Initialize() {
            g_GameModule = GetModuleHandle(NULL);
            if (!g_GameModule) {
                Utils::Logger::Error("Failed to get game module handle");
                return false;
            }

            char dllPath[MAX_PATH];
            GetModuleFileNameA(GetModuleHandleA("GFSDK_Aftermath_Lib.x64.dll"), dllPath, MAX_PATH);
            bool isEarlyLoad = (GetLastError() == 0);

            if (isEarlyLoad) {
                Utils::Logger::Info("DLL loaded as GFSDK_Aftermath_Lib.x64.dll (early load detected)");
                Utils::Logger::Info("Waiting for game to fully initialize...");

                bool gameInitialized = false;
                int waitAttempts = 0;
                const int maxWaitAttempts = 120;

                while (!gameInitialized && waitAttempts < maxWaitAttempts) {
                    SDK::UEngine* engine = SDK::UEngine::GetEngine();
                    SDK::UWorld* world = SDK::UWorld::GetWorld();

                    if (engine && world && world->PersistentLevel &&
                        SDK::UObject::GObjects && SDK::UObject::GObjects->Num() > 1000) {

                        g_GameWindow = FindWindow(NULL, L"Halfsword");
                        if (!g_GameWindow) {
                            g_GameWindow = FindWindow(L"UnrealWindow", NULL);
                        }

                        bool hasPlayerController = false;
                        if (world->OwningGameInstance &&
                            world->OwningGameInstance->LocalPlayers.Num() > 0) {
                            SDK::APlayerController* pc = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
                            hasPlayerController = (pc != nullptr);
                        }

                        if (g_GameWindow && hasPlayerController) {
                            gameInitialized = true;
                            Utils::Logger::Info("Game fully initialized");
                            Utils::Logger::Info("- Engine: 0x%p", engine);
                            Utils::Logger::Info("- World: 0x%p", world);
                            Utils::Logger::Info("- Level: 0x%p", world->PersistentLevel);
                            Utils::Logger::Info("- Window: 0x%p", g_GameWindow);
                            Utils::Logger::Info("- Objects: %d", SDK::UObject::GObjects->Num());
                            break;
                        }
                    }

                    Sleep(500);
                    waitAttempts++;

                    if (waitAttempts % 5 == 0) {
                        Utils::Logger::Info("Still waiting for game to initialize... (%d seconds)", waitAttempts / 2);

                        Utils::Logger::Info("- Engine: %s", SDK::UEngine::GetEngine() ? "Found" : "Not found");
                        Utils::Logger::Info("- World: %s", SDK::UWorld::GetWorld() ? "Found" : "Not found");
                        Utils::Logger::Info("- Level: %s", (SDK::UWorld::GetWorld() && SDK::UWorld::GetWorld()->PersistentLevel) ? "Found" : "Not found");
                        Utils::Logger::Info("- Window: %s", FindWindow(L"UnrealWindow", NULL) ? "Found" : "Not found");
                        if (SDK::UObject::GObjects) {
                            Utils::Logger::Info("- Objects: %d", SDK::UObject::GObjects->Num());
                        }
                    }
                }

                if (!gameInitialized) {
                    Utils::Logger::Error("Timed out waiting for game initialization");
                    return false;
                }
            }
            else {
                // idk why but the NVIDIA dll support broke normal injection
                Utils::Logger::Info("Game module: 0x%p", g_GameModule);

                g_GameWindow = FindWindow(NULL, L"Halfsword");
                if (!g_GameWindow) {
                    g_GameWindow = FindWindow(L"UnrealWindow", NULL);
                }

                if (!g_GameWindow) {
                    Utils::Logger::Warning("Failed to find game window. Hotkeys will not work.");
                    return false;
                }
                Utils::Logger::Info("Game window found: 0x%p", g_GameWindow);
            }


            Sleep(5000);
            if (!Hooks::Initialize()) {
                Utils::Logger::Error("Failed to initialize hooks");
                return false;
            }

            if (!Features::ConsoleManager::EnableConsole()) {
                Utils::Logger::Warning("Failed to enable in-game console");
            }

            if (!Features::PositionTracker::Initialize()) {
                Utils::Logger::Warning("Failed to initialize position tracker");
            }

            g_Running = true;
            g_UpdateThread = CreateThread(NULL, 0, UpdateThreadProc, NULL, 0, NULL);
            if (!g_UpdateThread) {
                Utils::Logger::Warning("Failed to create update thread");
            }

            g_HotkeyActive = true;
            Utils::Logger::Info("Core initialization complete");
            Utils::Logger::Info("Press F5 in-game to dump level information");
            Utils::Logger::Info("Press F6 in-game to manually record player position");
            Utils::Logger::Info("Press F9 in-game to clear console logs");
            Utils::Logger::Info("Press INSERT at any time to access the Level Selector");
            Utils::Logger::Info("Player position is automatically recorded on map changes");

            return true;
        }

        void Shutdown() {
            if (g_UpdateThread) {
                g_Running = false;
                WaitForSingleObject(g_UpdateThread, 1000);
                CloseHandle(g_UpdateThread);
                g_UpdateThread = nullptr;
            }

            Hooks::Shutdown();

            Utils::Logger::Info("Core shutdown complete");
        }

        HMODULE GetGameModule() {
            return g_GameModule;
        }

        HWND GetGameWindow() {
            return g_GameWindow;
        }

        bool IsHotkeyActive() {
            return g_HotkeyActive;
        }
    }
}