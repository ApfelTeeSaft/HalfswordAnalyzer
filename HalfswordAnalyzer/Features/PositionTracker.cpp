#include "PositionTracker.h"
#include "../Utils/Logger.h"
#include "../Utils/StringUtils.h"

namespace HalfswordAnalyzer {
    namespace Features {
        std::string PositionTracker::s_CurrentLevelName = "";
        bool PositionTracker::s_FirstPositionRecorded = false;
        std::map<std::string, PositionTracker::PositionInfo> PositionTracker::s_LevelPositions;

        bool PositionTracker::Initialize() {
            Utils::Logger::Info("Position tracker initialized");
            Utils::Logger::Info("Will log player position when map changes are detected");

            Update();
            return true;
        }

        void PositionTracker::Update() {
            std::string levelName = GetCurrentLevelName();

            if (levelName != s_CurrentLevelName) {
                s_CurrentLevelName = levelName;
                s_FirstPositionRecorded = false;
                Utils::Logger::Info("Map change detected: %s", s_CurrentLevelName.c_str());
            }

            if (!s_FirstPositionRecorded) {

                if (!levelName.empty()) {
                    RecordPlayerPosition();
                    LogPositionInfo();
                    s_FirstPositionRecorded = true;
                }
            }
        }

        std::string PositionTracker::GetCurrentLevelName() {
            SDK::UWorld* World = SDK::UWorld::GetWorld();
            if (!World || !World->PersistentLevel) {
                return "";
            }

            return Utils::StringUtils::GetObjectName(World->PersistentLevel);
        }

        void PositionTracker::RecordPlayerPosition() {
            SDK::UWorld* World = SDK::UWorld::GetWorld();
            if (!World || !World->OwningGameInstance) {
                return;
            }

            SDK::APlayerController* PC = nullptr;
            if (World->OwningGameInstance->LocalPlayers.Num() > 0) {
                PC = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
            }

            if (!PC) {
                Utils::Logger::Warning("Could not get player controller to record position");
                return;
            }

            SDK::APawn* Pawn = nullptr;
            if (PC->AcknowledgedPawn) {
                Pawn = static_cast<SDK::APawn*>(PC->AcknowledgedPawn);
            }

            PositionInfo info = {};

            if (Pawn) {
                info.PlayerLocation = Pawn->K2_GetActorLocation();
                info.PlayerRotation = Pawn->K2_GetActorRotation();
            }

            if (PC->PlayerCameraManager) {
                info.CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
                info.CameraRotation = PC->PlayerCameraManager->GetCameraRotation();
                info.CameraFOV = PC->PlayerCameraManager->GetFOVAngle();
            }

            s_LevelPositions[s_CurrentLevelName] = info;
        }

        void PositionTracker::LogPositionInfo() {
            if (s_CurrentLevelName.empty() || s_LevelPositions.find(s_CurrentLevelName) == s_LevelPositions.end()) {
                return;
            }

            const PositionInfo& info = s_LevelPositions[s_CurrentLevelName];

            Utils::Logger::Info("\n=== INITIAL PLAYER POSITION IN %s ===", s_CurrentLevelName.c_str());

            Utils::Logger::Info("Player Location: (%.2f, %.2f, %.2f)",
                info.PlayerLocation.X, info.PlayerLocation.Y, info.PlayerLocation.Z);
            Utils::Logger::Info("Player Rotation: (%.2f, %.2f, %.2f)",
                info.PlayerRotation.Pitch, info.PlayerRotation.Yaw, info.PlayerRotation.Roll);

            Utils::Logger::Info("Camera Location: (%.2f, %.2f, %.2f)",
                info.CameraLocation.X, info.CameraLocation.Y, info.CameraLocation.Z);
            Utils::Logger::Info("Camera Rotation: (%.2f, %.2f, %.2f)",
                info.CameraRotation.Pitch, info.CameraRotation.Yaw, info.CameraRotation.Roll);
            Utils::Logger::Info("Camera FOV: %.2f", info.CameraFOV);

            Utils::Logger::Info("\n// Position data for %s", s_CurrentLevelName.c_str());
            Utils::Logger::Info("PlayerLocation = FVector(%.2ff, %.2ff, %.2ff);",
                info.PlayerLocation.X, info.PlayerLocation.Y, info.PlayerLocation.Z);
            Utils::Logger::Info("PlayerRotation = FRotator(%.2ff, %.2ff, %.2ff);",
                info.PlayerRotation.Pitch, info.PlayerRotation.Yaw, info.PlayerRotation.Roll);
            Utils::Logger::Info("CameraLocation = FVector(%.2ff, %.2ff, %.2ff);",
                info.CameraLocation.X, info.CameraLocation.Y, info.CameraLocation.Z);
            Utils::Logger::Info("CameraRotation = FRotator(%.2ff, %.2ff, %.2ff);",
                info.CameraRotation.Pitch, info.CameraRotation.Yaw, info.CameraRotation.Roll);
        }
    }
}