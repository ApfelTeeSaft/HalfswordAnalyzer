﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: UI_FadeToLife

#include "Basic.hpp"


namespace SDK::Params
{

// Function UI_FadeToLife.UI_FadeToLife_C.ExecuteUbergraph_UI_FadeToLife
// 0x0028 (0x0028 - 0x0000)
struct UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_4[0x4];                                        // 0x0004(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class AGameModeBase*                          CallFunc_GetGameMode_ReturnValue;                  // 0x0008(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	class ABP_HalfSwordGameMode_C*                K2Node_DynamicCast_AsBP_Half_Sword_Game_Mode;      // 0x0010(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess;                       // 0x0018(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_19[0x7];                                       // 0x0019(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class UUMGSequencePlayer*                     CallFunc_PlayAnimation_ReturnValue;                // 0x0020(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
};
static_assert(alignof(UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife) == 0x000008, "Wrong alignment on UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife");
static_assert(sizeof(UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife) == 0x000028, "Wrong size on UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife");
static_assert(offsetof(UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife, EntryPoint) == 0x000000, "Member 'UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife::EntryPoint' has a wrong offset!");
static_assert(offsetof(UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife, CallFunc_GetGameMode_ReturnValue) == 0x000008, "Member 'UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife::CallFunc_GetGameMode_ReturnValue' has a wrong offset!");
static_assert(offsetof(UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife, K2Node_DynamicCast_AsBP_Half_Sword_Game_Mode) == 0x000010, "Member 'UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife::K2Node_DynamicCast_AsBP_Half_Sword_Game_Mode' has a wrong offset!");
static_assert(offsetof(UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife, K2Node_DynamicCast_bSuccess) == 0x000018, "Member 'UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife::K2Node_DynamicCast_bSuccess' has a wrong offset!");
static_assert(offsetof(UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife, CallFunc_PlayAnimation_ReturnValue) == 0x000020, "Member 'UI_FadeToLife_C_ExecuteUbergraph_UI_FadeToLife::CallFunc_PlayAnimation_ReturnValue' has a wrong offset!");

}

