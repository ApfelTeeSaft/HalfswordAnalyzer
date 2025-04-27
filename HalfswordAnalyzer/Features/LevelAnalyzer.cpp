#include "LevelAnalyzer.h"
#include "../Utils/Logger.h"
#include "../Utils/StringUtils.h"

#include <map>

namespace HalfswordAnalyzer {
    namespace Features {
        void LevelAnalyzer::DumpWorldInfo() {
            SDK::UWorld* World = SDK::UWorld::GetWorld();
            if (!World) {
                Utils::Logger::Error("Failed to get UWorld instance");
                return;
            }

            Utils::Logger::Info("=== WORLD INFORMATION ===");
            Utils::Logger::Info("World: %s (Class: %s)",
                Utils::StringUtils::GetObjectName(World).c_str(),
                Utils::StringUtils::GetClassName(World).c_str());

            SDK::ULevel* CurrentLevel = World->PersistentLevel;
            if (CurrentLevel) {
                Utils::Logger::Info("\n=== LEVEL INFORMATION ===");
                DumpLevelInfo(CurrentLevel);
            }

            if (World->OwningGameInstance) {
                Utils::Logger::Info("\n=== GAME INSTANCE ===");
                Utils::Logger::Info("Game Instance: %s",
                    Utils::StringUtils::GetObjectName(World->OwningGameInstance).c_str());
            }

            SDK::AGameModeBase* GameMode = World->AuthorityGameMode;
            if (GameMode) {
                Utils::Logger::Info("");
                DumpGameModeInfo(GameMode);
            }

            SDK::APlayerController* PC = nullptr;
            if (World->OwningGameInstance && World->OwningGameInstance->LocalPlayers.Num() > 0) {
                PC = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
            }

            if (PC) {
                Utils::Logger::Info("\n=== PLAYER CONTROLLER INFORMATION ===");
                DumpPlayerControllerInfo(PC);

                if (PC->AcknowledgedPawn) {
                    Utils::Logger::Info("\n=== PLAYER PAWN INFORMATION ===");
                    DumpPawnInfo(static_cast<SDK::APawn*>(PC->AcknowledgedPawn));
                }
                else {
                    Utils::Logger::Info("\n=== PLAYER PAWN INFORMATION ===");
                    Utils::Logger::Info("No player pawn found");
                }
            }
        }

        void LevelAnalyzer::DumpLevelInfo(SDK::ULevel* Level) {
            if (!Level) {
                Utils::Logger::Warning("Invalid level pointer");
                return;
            }

            Utils::Logger::Info("- Level: %s (Class: %s)",
                Utils::StringUtils::GetObjectName(Level).c_str(),
                Utils::StringUtils::GetClassName(Level).c_str());

            int actorCount = Level->Actors.Num();
            Utils::Logger::Info("  Actors Count: %d\n", actorCount);

            Utils::Logger::Info("  --- Key Actors ---");
            int maxActorsToShow = 20;
            int shownActors = 0;

            for (int i = 0; i < actorCount && shownActors < maxActorsToShow; i++) {
                SDK::AActor* Actor = Level->Actors[i];
                if (!Actor) continue;

                if (Actor->IsA(SDK::AGameModeBase::StaticClass()) ||
                    Actor->IsA(SDK::APlayerStart::StaticClass()) ||
                    Actor->IsA(SDK::AGameState::StaticClass()) ||
                    Actor->IsA(SDK::APlayerController::StaticClass()) ||
                    Actor->IsA(SDK::APawn::StaticClass())) {

                    DumpActorInfo(Actor, 1);
                    shownActors++;
                }
            }

            Utils::Logger::Info("\n  --- Actor Type Counts ---");
            std::map<std::string, int> actorTypeCounts;

            for (int i = 0; i < actorCount; i++) {
                SDK::AActor* Actor = Level->Actors[i];
                if (!Actor) continue;

                std::string className = Utils::StringUtils::GetClassName(Actor);
                actorTypeCounts[className]++;
            }

            for (const auto& pair : actorTypeCounts) {
                Utils::Logger::Info("  %s: %d", pair.first.c_str(), pair.second);
            }
        }

        void LevelAnalyzer::DumpGameModeInfo(SDK::AGameModeBase* GameMode) {
            if (!GameMode) {
                Utils::Logger::Warning("Invalid GameMode pointer");
                return;
            }

            Utils::Logger::Info("=== GAME MODE INFORMATION ===");
            Utils::Logger::Info("GameMode: %s (Class: %s)",
                Utils::StringUtils::GetObjectName(GameMode).c_str(),
                Utils::StringUtils::GetClassName(GameMode).c_str());

            if (GameMode->DefaultPawnClass) {
                Utils::Logger::Info("Default Pawn Class: %s",
                    Utils::StringUtils::GetObjectName(GameMode->DefaultPawnClass).c_str());
            }

            if (GameMode->HUDClass) {
                Utils::Logger::Info("HUD Class: %s",
                    Utils::StringUtils::GetObjectName(GameMode->HUDClass).c_str());
            }

            if (GameMode->PlayerControllerClass) {
                Utils::Logger::Info("PlayerController Class: %s",
                    Utils::StringUtils::GetObjectName(GameMode->PlayerControllerClass).c_str());
            }

            if (GameMode->GameStateClass) {
                Utils::Logger::Info("GameState Class: %s",
                    Utils::StringUtils::GetObjectName(GameMode->GameStateClass).c_str());
            }
        }

        void LevelAnalyzer::DumpPlayerControllerInfo(SDK::APlayerController* PC) {
            if (!PC) {
                Utils::Logger::Warning("Invalid PlayerController pointer");
                return;
            }

            Utils::Logger::Info("- PlayerController: %s (Class: %s)",
                Utils::StringUtils::GetObjectName(PC).c_str(),
                Utils::StringUtils::GetClassName(PC).c_str());

            if (PC->AcknowledgedPawn) {
                Utils::Logger::Info("  Controlled Pawn: %s",
                    Utils::StringUtils::GetObjectName(PC->AcknowledgedPawn).c_str());
            }

            if (PC->PlayerState) {
                Utils::Logger::Info("  Player State: %s",
                    Utils::StringUtils::GetObjectName(PC->PlayerState).c_str());
            }

            if (PC->PlayerCameraManager) {
                Utils::Logger::Info("  Camera Manager: %s",
                    Utils::StringUtils::GetObjectName(PC->PlayerCameraManager).c_str());
            }

            if (PC->MyHUD) {
                Utils::Logger::Info("  HUD: %s",
                    Utils::StringUtils::GetObjectName(PC->MyHUD).c_str());
            }
        }

        void LevelAnalyzer::DumpPawnInfo(SDK::APawn* Pawn) {
            if (!Pawn) {
                Utils::Logger::Warning("Invalid Pawn pointer");
                return;
            }

            Utils::Logger::Info("- Pawn: %s (Class: %s)",
                Utils::StringUtils::GetObjectName(Pawn).c_str(),
                Utils::StringUtils::GetClassName(Pawn).c_str());

            if (Pawn->Controller) {
                Utils::Logger::Info("  Controller: %s",
                    Utils::StringUtils::GetObjectName(Pawn->Controller).c_str());
            }

            SDK::FVector Location = Pawn->K2_GetActorLocation();
            SDK::FRotator Rotation = Pawn->K2_GetActorRotation();

            Utils::Logger::Info("  Location: (%.2f, %.2f, %.2f)", Location.X, Location.Y, Location.Z);
            Utils::Logger::Info("  Rotation: (%.2f, %.2f, %.2f)", Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

            Utils::Logger::Info("  Base EyeHeight: %.2f", Pawn->BaseEyeHeight);

            SDK::ACharacter* Character = static_cast<SDK::ACharacter*>(Pawn);
            if (Character && Character->IsA(SDK::ACharacter::StaticClass())) {
                Utils::Logger::Info("  Character Mesh: %s",
                    Character->Mesh ? Utils::StringUtils::GetObjectName(Character->Mesh).c_str() : "None");
                Utils::Logger::Info("  Character Movement: %s",
                    Character->CharacterMovement ? Utils::StringUtils::GetObjectName(Character->CharacterMovement).c_str() : "None");
            }
        }

        void LevelAnalyzer::DumpActorInfo(SDK::AActor* Actor, int indent) {
            if (!Actor) {
                return;
            }

            std::string indentStr(indent * 4, ' ');
            Utils::Logger::Info("%s- Actor: %s (Class: %s)",
                indentStr.c_str(),
                Utils::StringUtils::GetObjectName(Actor).c_str(),
                Utils::StringUtils::GetClassName(Actor).c_str());

            SDK::FVector Location = Actor->K2_GetActorLocation();
            SDK::FRotator Rotation = Actor->K2_GetActorRotation();

            Utils::Logger::Info("%s  Location: (%.2f, %.2f, %.2f)",
                indentStr.c_str(), Location.X, Location.Y, Location.Z);
            Utils::Logger::Info("%s  Rotation: (%.2f, %.2f, %.2f)",
                indentStr.c_str(), Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

            if (Actor->Tags.Num() > 0) {
                std::string tagsStr = "";
                for (int i = 0; i < Actor->Tags.Num(); i++) {
                    std::string TagName = Actor->Tags[i].ToString();

                    if (i > 0) tagsStr += ", ";
                    tagsStr += TagName;
                }
                Utils::Logger::Info("%s  Tags: %s", indentStr.c_str(), tagsStr.c_str());
            }
        }
    }
}