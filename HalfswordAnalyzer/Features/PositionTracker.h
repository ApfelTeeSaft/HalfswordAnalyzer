#pragma once

#include "../SDK/SDK.hpp"
#include <string>
#include <map>

namespace HalfswordAnalyzer {
    namespace Features {
        class PositionTracker {
        public:
            /**
             * Initializes the position tracker
             * @return True if initialization was successful
             */
            static bool Initialize();

            /**
             * Checks for map changes and records initial positions
             * Call this regularly to detect level transitions
             */
            static void Update();

            /**
             * Gets the current level name
             * @return The name of the current level
             */
            static std::string GetCurrentLevelName();

            /**
             * Records the player's current position and camera info in the current level
             */
            static void RecordPlayerPosition();

            /**
             * Logs the initial position information for the current level
             */
            static void LogPositionInfo();

        private:
            static std::string s_CurrentLevelName;
            static bool s_FirstPositionRecorded;

            struct PositionInfo {
                SDK::FVector PlayerLocation;
                SDK::FRotator PlayerRotation;
                SDK::FVector CameraLocation;
                SDK::FRotator CameraRotation;
                float CameraFOV;
            };

            static std::map<std::string, PositionInfo> s_LevelPositions;
        };
    }
}