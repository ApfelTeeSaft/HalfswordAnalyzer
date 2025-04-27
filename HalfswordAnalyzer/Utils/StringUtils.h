#pragma once

#include <string>
#include "../SDK/SDK.hpp"

namespace HalfswordAnalyzer {
    namespace Utils {
        class StringUtils {
        public:
            /**
             * Converts an FString to a std::string
             * @param FStr The FString to convert
             * @return std::string representation
             */
            static std::string FStringToStdString(const SDK::FString& FStr);

            /**
             * Gets the full name of an object
             * @param Object The UObject to get the name for
             * @return The full name as a string
             */
            static std::string GetObjectName(SDK::UObject* Object);

            /**
             * Gets the class name of an object
             * @param Object The UObject to get the class name for
             * @return The class name as a string
             */
            static std::string GetClassName(SDK::UObject* Object);
        };
    }
}