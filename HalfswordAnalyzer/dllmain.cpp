#include <Windows.h>
#include "Core/Core.h"
#include "Utils/Logger.h"

bool g_Initialized = false;

DWORD WINAPI InitThread(LPVOID lpParam) {
    if (!HalfswordAnalyzer::Utils::Logger::Initialize()) {
        MessageBoxA(NULL, "Failed to initialize logger", "Halfsword Analyzer Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    HalfswordAnalyzer::Utils::Logger::Info("HalfswordAnalyzer v1.0");
    HalfswordAnalyzer::Utils::Logger::Info("Initializing...");

    if (!HalfswordAnalyzer::Core::Initialize()) {
        HalfswordAnalyzer::Utils::Logger::Error("Failed to initialize core");
        return 1;
    }

    g_Initialized = true;
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        if (g_Initialized) {
            HalfswordAnalyzer::Core::Shutdown();
            HalfswordAnalyzer::Utils::Logger::Info("Shutting down HalfswordAnalyzer");
            HalfswordAnalyzer::Utils::Logger::Shutdown();
        }
        break;
    }

    return TRUE;
}