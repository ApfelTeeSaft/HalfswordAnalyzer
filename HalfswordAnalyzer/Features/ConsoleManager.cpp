#include "ConsoleManager.h"
#include "../Utils/Logger.h"

namespace HalfswordAnalyzer {
    namespace Features {
        bool ConsoleManager::s_ConsoleEnabled = false;

        bool ConsoleManager::EnableConsole() {
            if (s_ConsoleEnabled) {
                return true;
            }

            SDK::UEngine* Engine = SDK::UEngine::GetEngine();
            if (!Engine) {
                Utils::Logger::Error("Failed to get Engine instance");
                return false;
            }

            Utils::Logger::Info("Found Engine instance: 0x%p", Engine);

            if (!Engine->GameViewport) {
                Utils::Logger::Error("GameViewport is null");
                return false;
            }

            if (Engine->GameViewport->ViewportConsole) {
                Utils::Logger::Info("Console already exists");
                s_ConsoleEnabled = true;
                return true;
            }

            SDK::UObject* NewConsoleObj = SDK::UGameplayStatics::SpawnObject(
                Engine->ConsoleClass,
                Engine->GameViewport
            );

            if (!NewConsoleObj) {
                Utils::Logger::Error("Failed to create console object");
                return false;
            }

            Engine->GameViewport->ViewportConsole = static_cast<SDK::UConsole*>(NewConsoleObj);

            SDK::UInputSettings::GetDefaultObj()->ConsoleKeys[0].KeyName = SDK::UKismetStringLibrary::Conv_StringToName(L"F8");

            s_ConsoleEnabled = true;
            Utils::Logger::Info("In-game console enabled successfully");
            Utils::Logger::Info("You can now use F8 key to open the console");
            return true;
        }

        bool ConsoleManager::IsConsoleEnabled() {
            return s_ConsoleEnabled;
        }
    }
}