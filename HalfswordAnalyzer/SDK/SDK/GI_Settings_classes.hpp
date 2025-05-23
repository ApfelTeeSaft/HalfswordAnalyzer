﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: GI_Settings

#include "Basic.hpp"

#include "Menu_Garment_Enum_structs.hpp"
#include "Menu_LeftHand_Enum_structs.hpp"
#include "Engine_structs.hpp"
#include "Engine_classes.hpp"
#include "Menu_Maps_Enum_structs.hpp"
#include "Menu_Modes_Enum_structs.hpp"
#include "Menu_Head_Enum_structs.hpp"
#include "Menu_Cuirass_Enum_structs.hpp"
#include "Menu_RightHand_Enum_structs.hpp"
#include "Menu_Equip_Change_Enum_structs.hpp"
#include "ScreenResolution_Enum_structs.hpp"


namespace SDK
{

// BlueprintGeneratedClass GI_Settings.GI_Settings_C
// 0x0120 (0x02E0 - 0x01C0)
class UGI_Settings_C final : public UGameInstance
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x01C0(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	double                                        NPC_Damage_Rate;                                   // 0x01C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Player_Damage_Rate;                                // 0x01D0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Sound_Volume;                                      // 0x01D8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UAudioComponent*                        Music;                                             // 0x01E0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, NoDestructor, HasGetValueTypeHash)
	double                                        Music_Volume;                                      // 0x01E8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Maps_Enum                               Map;                                               // 0x01F0(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Modes_Enum                              Game_Mode;                                         // 0x01F1(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Head_Enum                               Player_Head;                                       // 0x01F2(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Garment_Enum                            Player_Garment;                                    // 0x01F3(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Cuirass_Enum                            Player_Cuirass;                                    // 0x01F4(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_RightHand_Enum                          Player_R_Arm;                                      // 0x01F5(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_LeftHand_Enum                           Player_L_Arm;                                      // 0x01F6(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Head_Enum                               Team_Head;                                         // 0x01F7(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Garment_Enum                            Team_Garment;                                      // 0x01F8(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Cuirass_Enum                            Team_Cuirass;                                      // 0x01F9(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_RightHand_Enum                          Team_R_Arm;                                        // 0x01FA(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_LeftHand_Enum                           Team_L_Arm;                                        // 0x01FB(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Head_Enum                               Foe_Head;                                          // 0x01FC(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Garment_Enum                            Foe_Garment;                                       // 0x01FD(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_Cuirass_Enum                            Foe_Cuirass;                                       // 0x01FE(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_RightHand_Enum                          Foe_R_Arm;                                         // 0x01FF(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EMenu_LeftHand_Enum                           Foe_L_Arm;                                         // 0x0200(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_201[0x7];                                      // 0x0201(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	TMulticastInlineDelegate<void()>              Set_Player_Dummy;                                  // 0x0208(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable, BlueprintCallable)
	TMulticastInlineDelegate<void()>              Set_Teammate_Du__y;                                // 0x0218(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable, BlueprintCallable)
	TMulticastInlineDelegate<void()>              Set_Foe_Dummy;                                     // 0x0228(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable, BlueprintCallable)
	EMenu_Equip_Change_Enum                       SlotChanging;                                      // 0x0238(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_239[0x3];                                      // 0x0239(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         NPC_Count;                                         // 0x023C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Blood_Rate;                                        // 0x0240(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Gore_Rate;                                         // 0x0248(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Bone_Snapping;                                     // 0x0250(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        FOV;                                               // 0x0258(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        HUD_Opacity;                                       // 0x0260(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EScreenResolution_Enum                        Resolution;                                        // 0x0268(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_269[0x7];                                      // 0x0269(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	double                                        Lock_On_Strength;                                  // 0x0270(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Camera_Lock_On;                                    // 0x0278(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_279[0x7];                                      // 0x0279(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class UObject*                                Discord_Ref;                                       // 0x0280(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	class FString                                 TextBef;                                           // 0x0288(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, HasGetValueTypeHash)
	bool                                          Tutorial_Completed;                                // 0x0298(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_299[0x7];                                      // 0x0299(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	double                                        Score;                                             // 0x02A0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Mouse_Sensitivity;                                 // 0x02A8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Invert_Mouse;                                      // 0x02B0(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Center_Crosshair;                                  // 0x02B1(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_2B2[0x2];                                      // 0x02B2(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         Voice_Volume;                                      // 0x02B4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          SplashScreenSkipped;                               // 0x02B8(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_2B9[0x7];                                      // 0x02B9(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class USG_Settings_C*                         SG_Settings;                                       // 0x02C0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	bool                                          Fresh_Start_Map__Temp_;                            // 0x02C8(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Tutorial;                                          // 0x02C9(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_2CA[0x6];                                      // 0x02CA(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	double                                        Time_Dilation;                                     // 0x02D0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Player_Team;                                       // 0x02D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Fog;                                               // 0x02DC(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void ExecuteUbergraph_GI_Settings(int32 EntryPoint);
	void Play_Music(class USoundBase* Sound, float VolumeMultiplier, bool bPersistAcrossLevelTransition);
	void Save_Settings();
	void Set_Foe_Equipment();
	void Set_Player_Equipment();
	void Set_Team_Equipment();
	void Set_Up_Interface();
	void Set_Up_Sound_Volume();
	void Stop_Music();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"GI_Settings_C">();
	}
	static class UGI_Settings_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UGI_Settings_C>();
	}
};
static_assert(alignof(UGI_Settings_C) == 0x000008, "Wrong alignment on UGI_Settings_C");
static_assert(sizeof(UGI_Settings_C) == 0x0002E0, "Wrong size on UGI_Settings_C");
static_assert(offsetof(UGI_Settings_C, UberGraphFrame) == 0x0001C0, "Member 'UGI_Settings_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, NPC_Damage_Rate) == 0x0001C8, "Member 'UGI_Settings_C::NPC_Damage_Rate' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Player_Damage_Rate) == 0x0001D0, "Member 'UGI_Settings_C::Player_Damage_Rate' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Sound_Volume) == 0x0001D8, "Member 'UGI_Settings_C::Sound_Volume' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Music) == 0x0001E0, "Member 'UGI_Settings_C::Music' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Music_Volume) == 0x0001E8, "Member 'UGI_Settings_C::Music_Volume' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Map) == 0x0001F0, "Member 'UGI_Settings_C::Map' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Game_Mode) == 0x0001F1, "Member 'UGI_Settings_C::Game_Mode' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Player_Head) == 0x0001F2, "Member 'UGI_Settings_C::Player_Head' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Player_Garment) == 0x0001F3, "Member 'UGI_Settings_C::Player_Garment' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Player_Cuirass) == 0x0001F4, "Member 'UGI_Settings_C::Player_Cuirass' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Player_R_Arm) == 0x0001F5, "Member 'UGI_Settings_C::Player_R_Arm' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Player_L_Arm) == 0x0001F6, "Member 'UGI_Settings_C::Player_L_Arm' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Team_Head) == 0x0001F7, "Member 'UGI_Settings_C::Team_Head' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Team_Garment) == 0x0001F8, "Member 'UGI_Settings_C::Team_Garment' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Team_Cuirass) == 0x0001F9, "Member 'UGI_Settings_C::Team_Cuirass' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Team_R_Arm) == 0x0001FA, "Member 'UGI_Settings_C::Team_R_Arm' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Team_L_Arm) == 0x0001FB, "Member 'UGI_Settings_C::Team_L_Arm' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Foe_Head) == 0x0001FC, "Member 'UGI_Settings_C::Foe_Head' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Foe_Garment) == 0x0001FD, "Member 'UGI_Settings_C::Foe_Garment' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Foe_Cuirass) == 0x0001FE, "Member 'UGI_Settings_C::Foe_Cuirass' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Foe_R_Arm) == 0x0001FF, "Member 'UGI_Settings_C::Foe_R_Arm' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Foe_L_Arm) == 0x000200, "Member 'UGI_Settings_C::Foe_L_Arm' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Set_Player_Dummy) == 0x000208, "Member 'UGI_Settings_C::Set_Player_Dummy' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Set_Teammate_Du__y) == 0x000218, "Member 'UGI_Settings_C::Set_Teammate_Du__y' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Set_Foe_Dummy) == 0x000228, "Member 'UGI_Settings_C::Set_Foe_Dummy' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, SlotChanging) == 0x000238, "Member 'UGI_Settings_C::SlotChanging' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, NPC_Count) == 0x00023C, "Member 'UGI_Settings_C::NPC_Count' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Blood_Rate) == 0x000240, "Member 'UGI_Settings_C::Blood_Rate' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Gore_Rate) == 0x000248, "Member 'UGI_Settings_C::Gore_Rate' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Bone_Snapping) == 0x000250, "Member 'UGI_Settings_C::Bone_Snapping' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, FOV) == 0x000258, "Member 'UGI_Settings_C::FOV' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, HUD_Opacity) == 0x000260, "Member 'UGI_Settings_C::HUD_Opacity' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Resolution) == 0x000268, "Member 'UGI_Settings_C::Resolution' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Lock_On_Strength) == 0x000270, "Member 'UGI_Settings_C::Lock_On_Strength' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Camera_Lock_On) == 0x000278, "Member 'UGI_Settings_C::Camera_Lock_On' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Discord_Ref) == 0x000280, "Member 'UGI_Settings_C::Discord_Ref' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, TextBef) == 0x000288, "Member 'UGI_Settings_C::TextBef' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Tutorial_Completed) == 0x000298, "Member 'UGI_Settings_C::Tutorial_Completed' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Score) == 0x0002A0, "Member 'UGI_Settings_C::Score' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Mouse_Sensitivity) == 0x0002A8, "Member 'UGI_Settings_C::Mouse_Sensitivity' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Invert_Mouse) == 0x0002B0, "Member 'UGI_Settings_C::Invert_Mouse' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Center_Crosshair) == 0x0002B1, "Member 'UGI_Settings_C::Center_Crosshair' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Voice_Volume) == 0x0002B4, "Member 'UGI_Settings_C::Voice_Volume' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, SplashScreenSkipped) == 0x0002B8, "Member 'UGI_Settings_C::SplashScreenSkipped' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, SG_Settings) == 0x0002C0, "Member 'UGI_Settings_C::SG_Settings' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Fresh_Start_Map__Temp_) == 0x0002C8, "Member 'UGI_Settings_C::Fresh_Start_Map__Temp_' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Tutorial) == 0x0002C9, "Member 'UGI_Settings_C::Tutorial' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Time_Dilation) == 0x0002D0, "Member 'UGI_Settings_C::Time_Dilation' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Player_Team) == 0x0002D8, "Member 'UGI_Settings_C::Player_Team' has a wrong offset!");
static_assert(offsetof(UGI_Settings_C, Fog) == 0x0002DC, "Member 'UGI_Settings_C::Fog' has a wrong offset!");

}

