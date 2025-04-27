#pragma once

#include "../SDK/SDK.hpp"

namespace HalfswordAnalyzer {
    namespace Features {
        class LevelAnalyzer {
        public:
            /**
             * Dumps information about the current world
             */
            static void DumpWorldInfo();

            /**
             * Dumps information about a specific level
             * @param Level The level to analyze
             */
            static void DumpLevelInfo(SDK::ULevel* Level);

            /**
             * Dumps information about a game mode
             * @param GameMode The game mode to analyze
             */
            static void DumpGameModeInfo(SDK::AGameModeBase* GameMode);

            /**
             * Dumps information about a player controller
             * @param PC The player controller to analyze
             */
            static void DumpPlayerControllerInfo(SDK::APlayerController* PC);

            /**
             * Dumps information about a pawn
             * @param Pawn The pawn to analyze
             */
            static void DumpPawnInfo(SDK::APawn* Pawn);

            /**
             * Dumps information about an actor
             * @param Actor The actor to analyze
             * @param indent Indentation level for formatting
             */
            static void DumpActorInfo(SDK::AActor* Actor, int indent = 0);
        };
    }
}