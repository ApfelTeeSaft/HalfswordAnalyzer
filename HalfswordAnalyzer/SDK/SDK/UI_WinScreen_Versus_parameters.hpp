﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: UI_WinScreen_Versus

#include "Basic.hpp"

#include "SlateCore_structs.hpp"


namespace SDK::Params
{

// Function UI_WinScreen_Versus.UI_WinScreen_Versus_C.ExecuteUbergraph_UI_WinScreen_Versus
// 0x01F0 (0x01F0 - 0x0000)
struct UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_Event_IsDesignTime;                         // 0x0004(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_5[0x3];                                        // 0x0005(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	class UUMGSequencePlayer*                     CallFunc_PlayAnimation_ReturnValue;                // 0x0008(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_SwitchInteger_CmpSuccess;                   // 0x0010(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_11[0xF];                                       // 0x0011(0x000F)(Fixing Size After Last Property [ Dumper-7 ])
	struct FSlateBrush                            K2Node_MakeStruct_SlateBrush;                      // 0x0020(0x00D0)()
	struct FSlateBrush                            K2Node_MakeStruct_SlateBrush_1;                    // 0x00F0(0x00D0)()
	class UUMGSequencePlayer*                     CallFunc_PlayAnimation_ReturnValue_1;              // 0x01C0(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	class AGameModeBase*                          CallFunc_GetGameMode_ReturnValue;                  // 0x01C8(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	class UGameInstance*                          CallFunc_GetGameInstance_ReturnValue;              // 0x01D0(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	class UGI_Settings_C*                         K2Node_DynamicCast_AsGI_Settings;                  // 0x01D8(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_DynamicCast_bSuccess;                       // 0x01E0(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_1E1[0x3];                                      // 0x01E1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         CallFunc_SetGlobalTimeDilation_TimeDilation_ImplicitCast; // 0x01E4(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                         CallFunc_SetGlobalTimeDilation_TimeDilation_ImplicitCast_1; // 0x01E8(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};
static_assert(alignof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus) == 0x000010, "Wrong alignment on UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus");
static_assert(sizeof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus) == 0x0001F0, "Wrong size on UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, EntryPoint) == 0x000000, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::EntryPoint' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, K2Node_Event_IsDesignTime) == 0x000004, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::K2Node_Event_IsDesignTime' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, CallFunc_PlayAnimation_ReturnValue) == 0x000008, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::CallFunc_PlayAnimation_ReturnValue' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, K2Node_SwitchInteger_CmpSuccess) == 0x000010, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::K2Node_SwitchInteger_CmpSuccess' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, K2Node_MakeStruct_SlateBrush) == 0x000020, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::K2Node_MakeStruct_SlateBrush' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, K2Node_MakeStruct_SlateBrush_1) == 0x0000F0, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::K2Node_MakeStruct_SlateBrush_1' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, CallFunc_PlayAnimation_ReturnValue_1) == 0x0001C0, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::CallFunc_PlayAnimation_ReturnValue_1' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, CallFunc_GetGameMode_ReturnValue) == 0x0001C8, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::CallFunc_GetGameMode_ReturnValue' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, CallFunc_GetGameInstance_ReturnValue) == 0x0001D0, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::CallFunc_GetGameInstance_ReturnValue' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, K2Node_DynamicCast_AsGI_Settings) == 0x0001D8, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::K2Node_DynamicCast_AsGI_Settings' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, K2Node_DynamicCast_bSuccess) == 0x0001E0, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::K2Node_DynamicCast_bSuccess' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, CallFunc_SetGlobalTimeDilation_TimeDilation_ImplicitCast) == 0x0001E4, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::CallFunc_SetGlobalTimeDilation_TimeDilation_ImplicitCast' has a wrong offset!");
static_assert(offsetof(UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus, CallFunc_SetGlobalTimeDilation_TimeDilation_ImplicitCast_1) == 0x0001E8, "Member 'UI_WinScreen_Versus_C_ExecuteUbergraph_UI_WinScreen_Versus::CallFunc_SetGlobalTimeDilation_TimeDilation_ImplicitCast_1' has a wrong offset!");

// Function UI_WinScreen_Versus.UI_WinScreen_Versus_C.PreConstruct
// 0x0001 (0x0001 - 0x0000)
struct UI_WinScreen_Versus_C_PreConstruct final
{
public:
	bool                                          IsDesignTime;                                      // 0x0000(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};
static_assert(alignof(UI_WinScreen_Versus_C_PreConstruct) == 0x000001, "Wrong alignment on UI_WinScreen_Versus_C_PreConstruct");
static_assert(sizeof(UI_WinScreen_Versus_C_PreConstruct) == 0x000001, "Wrong size on UI_WinScreen_Versus_C_PreConstruct");
static_assert(offsetof(UI_WinScreen_Versus_C_PreConstruct, IsDesignTime) == 0x000000, "Member 'UI_WinScreen_Versus_C_PreConstruct::IsDesignTime' has a wrong offset!");

}

