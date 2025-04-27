#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

namespace HalfswordAnalyzer {
    namespace Utils {
        class Memory {
        public:
            /**
             * Finds a pattern in memory
             * @param moduleBase Base address of the module to search in
             * @param pattern Byte pattern to search for
             * @param mask Mask for the pattern (x for byte to check, ? for wildcard)
             * @return Address of the pattern, 0 if not found
             */
            static uintptr_t FindPattern(uintptr_t moduleBase, const char* pattern, const char* mask);

            /**
             * Finds a pattern in a specific module
             * @param moduleName Name of the module
             * @param pattern Byte pattern to search for
             * @param mask Mask for the pattern (x for byte to check, ? for wildcard)
             * @return Address of the pattern, 0 if not found
             */
            static uintptr_t FindPattern(const char* moduleName, const char* pattern, const char* mask);

            /**
             * Gets the base address of a module
             * @param moduleName Name of the module
             * @return Base address of the module, 0 if not found
             */
            static uintptr_t GetModuleBaseAddress(const char* moduleName);
        };
    }
}