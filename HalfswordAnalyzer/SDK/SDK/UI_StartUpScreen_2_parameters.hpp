﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: UI_StartUpScreen_2

#include "Basic.hpp"

#include "InputCore_structs.hpp"


namespace SDK::Params
{

// Function UI_StartUpScreen_2.UI_StartUpScreen_2_C.ExecuteUbergraph_UI_StartUpScreen_2
// 0x0048 (0x0048 - 0x0000)
struct UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2 final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_4[0x4];                                        // 0x0004(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	struct FKey                                   K2Node_InputKeyEvent_Key;                          // 0x0008(0x0018)(HasGetValueTypeHash)
	bool                                          Temp_bool_Has_Been_Initd_Variable;                 // 0x0020(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Temp_bool_IsClosed_Variable;                       // 0x0021(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_22[0x6];                                       // 0x0022(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	class APlayerController*                      CallFunc_GetPlayerController_ReturnValue;          // 0x0028(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	class APlayerController*                      CallFunc_GetPlayerController_ReturnValue_1;        // 0x0030(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
	class UUI_StartUpScreen_3_C*                  CallFunc_Create_ReturnValue;                       // 0x0038(0x0008)(ZeroConstructor, InstancedReference, NoDestructor, HasGetValueTypeHash)
	class UUMGSequencePlayer*                     CallFunc_PlayAnimation_ReturnValue;                // 0x0040(0x0008)(ZeroConstructor, NoDestructor, HasGetValueTypeHash)
};
static_assert(alignof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2) == 0x000008, "Wrong alignment on UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2");
static_assert(sizeof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2) == 0x000048, "Wrong size on UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, EntryPoint) == 0x000000, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::EntryPoint' has a wrong offset!");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, K2Node_InputKeyEvent_Key) == 0x000008, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::K2Node_InputKeyEvent_Key' has a wrong offset!");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, Temp_bool_Has_Been_Initd_Variable) == 0x000020, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::Temp_bool_Has_Been_Initd_Variable' has a wrong offset!");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, Temp_bool_IsClosed_Variable) == 0x000021, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::Temp_bool_IsClosed_Variable' has a wrong offset!");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, CallFunc_GetPlayerController_ReturnValue) == 0x000028, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::CallFunc_GetPlayerController_ReturnValue' has a wrong offset!");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, CallFunc_GetPlayerController_ReturnValue_1) == 0x000030, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::CallFunc_GetPlayerController_ReturnValue_1' has a wrong offset!");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, CallFunc_Create_ReturnValue) == 0x000038, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::CallFunc_Create_ReturnValue' has a wrong offset!");
static_assert(offsetof(UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2, CallFunc_PlayAnimation_ReturnValue) == 0x000040, "Member 'UI_StartUpScreen_2_C_ExecuteUbergraph_UI_StartUpScreen_2::CallFunc_PlayAnimation_ReturnValue' has a wrong offset!");

// Function UI_StartUpScreen_2.UI_StartUpScreen_2_C.InpActEvt_AnyKey_K2Node_InputKeyEvent_0
// 0x0018 (0x0018 - 0x0000)
struct UI_StartUpScreen_2_C_InpActEvt_AnyKey_K2Node_InputKeyEvent_0 final
{
public:
	struct FKey                                   Key;                                               // 0x0000(0x0018)(BlueprintVisible, BlueprintReadOnly, Parm, HasGetValueTypeHash)
};
static_assert(alignof(UI_StartUpScreen_2_C_InpActEvt_AnyKey_K2Node_InputKeyEvent_0) == 0x000008, "Wrong alignment on UI_StartUpScreen_2_C_InpActEvt_AnyKey_K2Node_InputKeyEvent_0");
static_assert(sizeof(UI_StartUpScreen_2_C_InpActEvt_AnyKey_K2Node_InputKeyEvent_0) == 0x000018, "Wrong size on UI_StartUpScreen_2_C_InpActEvt_AnyKey_K2Node_InputKeyEvent_0");
static_assert(offsetof(UI_StartUpScreen_2_C_InpActEvt_AnyKey_K2Node_InputKeyEvent_0, Key) == 0x000000, "Member 'UI_StartUpScreen_2_C_InpActEvt_AnyKey_K2Node_InputKeyEvent_0::Key' has a wrong offset!");

}

