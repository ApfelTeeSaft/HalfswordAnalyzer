#include "Memory.h"
#include "Logger.h"

#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")

namespace HalfswordAnalyzer {
    namespace Utils {
        uintptr_t Memory::FindPattern(uintptr_t moduleBase, const char* pattern, const char* mask) {
            if (!moduleBase) {
                return 0;
            }

            MODULEINFO moduleInfo;
            if (!GetModuleInformation(GetCurrentProcess(), (HMODULE)moduleBase, &moduleInfo, sizeof(MODULEINFO))) {
                Logger::Error("Failed to get module information");
                return 0;
            }

            size_t patternLength = strlen(mask);

            for (size_t i = 0; i < moduleInfo.SizeOfImage - patternLength; i++) {
                bool found = true;
                for (size_t j = 0; j < patternLength; j++) {
                    if (mask[j] != '?' && pattern[j] != *(char*)(moduleBase + i + j)) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    return moduleBase + i;
                }
            }

            return 0;
        }

        uintptr_t Memory::FindPattern(const char* moduleName, const char* pattern, const char* mask) {
            uintptr_t moduleBase = GetModuleBaseAddress(moduleName);
            if (!moduleBase) {
                return 0;
            }

            return FindPattern(moduleBase, pattern, mask);
        }

        uintptr_t Memory::GetModuleBaseAddress(const char* moduleName) {
            HMODULE hModule = GetModuleHandleA(moduleName);
            if (!hModule) {
                Logger::Error("Failed to get module handle for %s", moduleName);
                return 0;
            }

            return (uintptr_t)hModule;
        }
    }
}