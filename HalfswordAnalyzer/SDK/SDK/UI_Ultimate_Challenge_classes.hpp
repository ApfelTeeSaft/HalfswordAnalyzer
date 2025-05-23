﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: UI_Ultimate_Challenge

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "Enum_PlayCards_structs.hpp"
#include "UMG_structs.hpp"
#include "UMG_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass UI_Ultimate_Challenge.UI_Ultimate_Challenge_C
// 0x0070 (0x0350 - 0x02E0)
class UUI_Ultimate_Challenge_C final : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x02E0(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UWidgetAnimation*                       FadeIn;                                            // 0x02E8(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       FadeToBlack;                                       // 0x02F0(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UImage*                                 Image;                                             // 0x02F8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_2;                                           // 0x0300(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWidgetAnimation*                       WinAnim_0;                                         // 0x0308(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	double                                        Hold_Meter;                                        // 0x0310(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class AWillie_BP_C*                           My_Master__Willie_;                                // 0x0318(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	TArray<Enum_PlayCards>                        Cards_Array;                                       // 0x0320(0x0010)(Edit, BlueprintVisible, DisableEditOnInstance)
	class ABP_HalfSwordGameMode_C*                As_BP_Half_Sword_Game_Mode;                        // 0x0330(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	int32                                         Player_Rank;                                       // 0x0338(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	Enum_PlayCards                                Card_1_Type;                                       // 0x033C(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Destroyed;                                         // 0x033D(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_33E[0x2];                                      // 0x033E(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	class UGI_Settings_C*                         As_GI_Settings;                                    // 0x0340(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)
	int32                                         Add_Points;                                        // 0x0348(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void Construct();
	void ExecuteUbergraph_UI_Ultimate_Challenge(int32 EntryPoint);
	float GetPercent();
	class FText GetText();
	class FText GetText_0();
	ESlateVisibility GetVisibility_0();
	void PreConstruct(bool IsDesignTime);
	void Tick(const struct FGeometry& MyGeometry, float InDeltaTime);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"UI_Ultimate_Challenge_C">();
	}
	static class UUI_Ultimate_Challenge_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UUI_Ultimate_Challenge_C>();
	}
};
static_assert(alignof(UUI_Ultimate_Challenge_C) == 0x000008, "Wrong alignment on UUI_Ultimate_Challenge_C");
static_assert(sizeof(UUI_Ultimate_Challenge_C) == 0x000350, "Wrong size on UUI_Ultimate_Challenge_C");
static_assert(offsetof(UUI_Ultimate_Challenge_C, UberGraphFrame) == 0x0002E0, "Member 'UUI_Ultimate_Challenge_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, FadeIn) == 0x0002E8, "Member 'UUI_Ultimate_Challenge_C::FadeIn' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, FadeToBlack) == 0x0002F0, "Member 'UUI_Ultimate_Challenge_C::FadeToBlack' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Image) == 0x0002F8, "Member 'UUI_Ultimate_Challenge_C::Image' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Image_2) == 0x000300, "Member 'UUI_Ultimate_Challenge_C::Image_2' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, WinAnim_0) == 0x000308, "Member 'UUI_Ultimate_Challenge_C::WinAnim_0' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Hold_Meter) == 0x000310, "Member 'UUI_Ultimate_Challenge_C::Hold_Meter' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, My_Master__Willie_) == 0x000318, "Member 'UUI_Ultimate_Challenge_C::My_Master__Willie_' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Cards_Array) == 0x000320, "Member 'UUI_Ultimate_Challenge_C::Cards_Array' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, As_BP_Half_Sword_Game_Mode) == 0x000330, "Member 'UUI_Ultimate_Challenge_C::As_BP_Half_Sword_Game_Mode' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Player_Rank) == 0x000338, "Member 'UUI_Ultimate_Challenge_C::Player_Rank' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Card_1_Type) == 0x00033C, "Member 'UUI_Ultimate_Challenge_C::Card_1_Type' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Destroyed) == 0x00033D, "Member 'UUI_Ultimate_Challenge_C::Destroyed' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, As_GI_Settings) == 0x000340, "Member 'UUI_Ultimate_Challenge_C::As_GI_Settings' has a wrong offset!");
static_assert(offsetof(UUI_Ultimate_Challenge_C, Add_Points) == 0x000348, "Member 'UUI_Ultimate_Challenge_C::Add_Points' has a wrong offset!");

}

