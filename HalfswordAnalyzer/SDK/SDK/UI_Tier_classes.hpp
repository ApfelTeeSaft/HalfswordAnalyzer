﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: UI_Tier

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "UMG_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass UI_Tier.UI_Tier_C
// 0x0028 (0x0308 - 0x02E0)
class UUI_Tier_C final : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x02E0(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UWidgetAnimation*                       Fade;                                              // 0x02E8(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UImage*                                 Image_0;                                           // 0x02F0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	int32                                         Level;                                             // 0x02F8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_2FC[0x4];                                      // 0x02FC(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class ABP_HalfSwordGameMode_C*                As_BP_Half_Sword_Game_Mode;                        // 0x0300(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)

public:
	void Construct();
	void ExecuteUbergraph_UI_Tier(int32 EntryPoint);
	struct FSlateBrush GetBrush();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"UI_Tier_C">();
	}
	static class UUI_Tier_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UUI_Tier_C>();
	}
};
static_assert(alignof(UUI_Tier_C) == 0x000008, "Wrong alignment on UUI_Tier_C");
static_assert(sizeof(UUI_Tier_C) == 0x000308, "Wrong size on UUI_Tier_C");
static_assert(offsetof(UUI_Tier_C, UberGraphFrame) == 0x0002E0, "Member 'UUI_Tier_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(UUI_Tier_C, Fade) == 0x0002E8, "Member 'UUI_Tier_C::Fade' has a wrong offset!");
static_assert(offsetof(UUI_Tier_C, Image_0) == 0x0002F0, "Member 'UUI_Tier_C::Image_0' has a wrong offset!");
static_assert(offsetof(UUI_Tier_C, Level) == 0x0002F8, "Member 'UUI_Tier_C::Level' has a wrong offset!");
static_assert(offsetof(UUI_Tier_C, As_BP_Half_Sword_Game_Mode) == 0x000300, "Member 'UUI_Tier_C::As_BP_Half_Sword_Game_Mode' has a wrong offset!");

}

