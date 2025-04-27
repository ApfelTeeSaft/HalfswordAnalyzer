#include "StringUtils.h"

namespace HalfswordAnalyzer {
    namespace Utils {
        std::string StringUtils::FStringToStdString(const SDK::FString& FStr) {
            return FStr.ToString();
        }

        std::string StringUtils::GetObjectName(SDK::UObject* Object) {
            if (!Object) {
                return "None";
            }

            return Object->GetFullName();
        }

        std::string StringUtils::GetClassName(SDK::UObject* Object) {
            if (!Object) {
                return "None";
            }

            SDK::UClass* Class = Object->Class;
            if (!Class) {
                return "Unknown";
            }

            return Class->GetFullName();
        }
    }
}