﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SG_PlayerProgression

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "Engine_classes.hpp"
#include "Str_Loadout_Equipment_structs.hpp"
#include "PlayerCharacter_Settings_Struct_structs.hpp"
#include "Gauntlet_Progress_Struct_structs.hpp"


namespace SDK
{

// BlueprintGeneratedClass SG_PlayerProgression.SG_PlayerProgression_C
// 0x5678 (0x56A0 - 0x0028)
class USG_PlayerProgression_C final : public USaveGame
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0028(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	struct FPlayerCharacter_Settings_Struct       PlayerCharacter_Settings;                          // 0x0030(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Rank;                                              // 0x0040(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Team;                                              // 0x0044(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FGauntlet_Progress_Struct              Equipment_Progression_Struct;                      // 0x0048(0x4DA0)(Edit, BlueprintVisible, DisableEditOnInstance, HasGetValueTypeHash)
	struct FStr_Loadout_Equipment                 Saved_Equipment;                                   // 0x4DE8(0x08A0)(Edit, BlueprintVisible, DisableEditOnInstance, HasGetValueTypeHash)
	bool                                          Faction_Chosen;                                    // 0x5688(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Baron_Rank_Opened;                                 // 0x5689(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Level_Up_Available;                                // 0x568A(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Free_Armor;                                        // 0x568B(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Available_Rank;                                    // 0x568C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Current_Points;                                    // 0x5690(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Body_Chosen;                                       // 0x5694(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_5695[0x3];                                     // 0x5695(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         Ranks_Unlocked;                                    // 0x5698(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Abyss;                                             // 0x569C(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_SG_PlayerProgression(int32 EntryPoint);
	void Save_Rank_Equipment_Event(const struct FStr_Loadout_Equipment& Saved_Equipment_Struct);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"SG_PlayerProgression_C">();
	}
	static class USG_PlayerProgression_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<USG_PlayerProgression_C>();
	}
};
static_assert(alignof(USG_PlayerProgression_C) == 0x000008, "Wrong alignment on USG_PlayerProgression_C");
static_assert(sizeof(USG_PlayerProgression_C) == 0x0056A0, "Wrong size on USG_PlayerProgression_C");
static_assert(offsetof(USG_PlayerProgression_C, UberGraphFrame) == 0x000028, "Member 'USG_PlayerProgression_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, PlayerCharacter_Settings) == 0x000030, "Member 'USG_PlayerProgression_C::PlayerCharacter_Settings' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Rank) == 0x000040, "Member 'USG_PlayerProgression_C::Rank' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Team) == 0x000044, "Member 'USG_PlayerProgression_C::Team' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Equipment_Progression_Struct) == 0x000048, "Member 'USG_PlayerProgression_C::Equipment_Progression_Struct' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Saved_Equipment) == 0x004DE8, "Member 'USG_PlayerProgression_C::Saved_Equipment' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Faction_Chosen) == 0x005688, "Member 'USG_PlayerProgression_C::Faction_Chosen' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Baron_Rank_Opened) == 0x005689, "Member 'USG_PlayerProgression_C::Baron_Rank_Opened' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Level_Up_Available) == 0x00568A, "Member 'USG_PlayerProgression_C::Level_Up_Available' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Free_Armor) == 0x00568B, "Member 'USG_PlayerProgression_C::Free_Armor' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Available_Rank) == 0x00568C, "Member 'USG_PlayerProgression_C::Available_Rank' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Current_Points) == 0x005690, "Member 'USG_PlayerProgression_C::Current_Points' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Body_Chosen) == 0x005694, "Member 'USG_PlayerProgression_C::Body_Chosen' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Ranks_Unlocked) == 0x005698, "Member 'USG_PlayerProgression_C::Ranks_Unlocked' has a wrong offset!");
static_assert(offsetof(USG_PlayerProgression_C, Abyss) == 0x00569C, "Member 'USG_PlayerProgression_C::Abyss' has a wrong offset!");

}

