﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: UI_AdvGraphics

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "UMG_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass UI_AdvGraphics.UI_AdvGraphics_C
// 0x01C0 (0x04A0 - 0x02E0)
class UUI_AdvGraphics_C final : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x02E0(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UWidgetAnimation*                       HoverAudio;                                        // 0x02E8(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       HoverControls;                                     // 0x02F0(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       HoverGame;                                         // 0x02F8(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       HoverDisplay;                                      // 0x0300(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       HoverSave;                                         // 0x0308(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UWidgetAnimation*                       HoverBack;                                         // 0x0310(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UButton*                                AntiAliaDown;                                      // 0x0318(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                AntiAliaUp;                                        // 0x0320(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                BackButton;                                        // 0x0328(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                Button;                                            // 0x0330(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                Button_1;                                          // 0x0338(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                Button_2;                                          // 0x0340(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                Button_4;                                          // 0x0348(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                Button_27;                                         // 0x0350(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                DLSSDOWN;                                          // 0x0358(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                DLSSUP;                                            // 0x0360(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                FoliageDown;                                       // 0x0368(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                FoliageDown_1;                                     // 0x0370(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                FoliageUp;                                         // 0x0378(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                FoliageUp_1;                                       // 0x0380(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image;                                             // 0x0388(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_0;                                           // 0x0390(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_1;                                           // 0x0398(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_2;                                           // 0x03A0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_3;                                           // 0x03A8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_4;                                           // 0x03B0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_5;                                           // 0x03B8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_6;                                           // 0x03C0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_7;                                           // 0x03C8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_8;                                           // 0x03D0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_9;                                           // 0x03D8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_10;                                          // 0x03E0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_11;                                          // 0x03E8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_12;                                          // 0x03F0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_13;                                          // 0x03F8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_14;                                          // 0x0400(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_15;                                          // 0x0408(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_16;                                          // 0x0410(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_17;                                          // 0x0418(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 Image_18;                                          // 0x0420(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                 OptionsPaper;                                      // 0x0428(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                PostProcessDown;                                   // 0x0430(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                PostProcessUp;                                     // 0x0438(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                SaveButton;                                        // 0x0440(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                ShadowDown;                                        // 0x0448(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                ShadowUp;                                          // 0x0450(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                TextureDown;                                       // 0x0458(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                TextureUp;                                         // 0x0460(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                ViewDisDown;                                       // 0x0468(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UButton*                                ViewDisUp;                                         // 0x0470(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UClass*                                 Go_Back_To;                                        // 0x0478(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, ExposeOnSpawn, HasGetValueTypeHash)
	int32                                         FoliageQ;                                          // 0x0480(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         ShadowQ;                                           // 0x0484(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         TextureQ;                                          // 0x0488(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         PostProcessQ;                                      // 0x048C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         AntiAliasing;                                      // 0x0490(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         ViewDistance;                                      // 0x0494(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Global_illum;                                      // 0x0498(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         VisualEffect;                                      // 0x049C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

public:
	void BndEvt__UI_AdvGraphics_AntiAliaUp_K2Node_ComponentBoundEvent_23_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_BackButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_BackButton_K2Node_ComponentBoundEvent_15_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_BackButton_K2Node_ComponentBoundEvent_16_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_1_K2Node_ComponentBoundEvent_11_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_1_K2Node_ComponentBoundEvent_12_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_1_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_27_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_27_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_27_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_2_K2Node_ComponentBoundEvent_13_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_2_K2Node_ComponentBoundEvent_14_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_2_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_4_K2Node_ComponentBoundEvent_24_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_K2Node_ComponentBoundEvent_10_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_Button_K2Node_ComponentBoundEvent_9_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_FoliageDown_K2Node_ComponentBoundEvent_21_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_FoliageUp_K2Node_ComponentBoundEvent_22_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_GraphicsDown_1_K2Node_ComponentBoundEvent_20_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_GraphicsDown_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_GraphicsUp_K2Node_ComponentBoundEvent_19_OnButtonClickedEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_SaveButton_K2Node_ComponentBoundEvent_17_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_SaveButton_K2Node_ComponentBoundEvent_18_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__UI_AdvGraphics_SaveButton_K2Node_ComponentBoundEvent_6_OnButtonClickedEvent__DelegateSignature();
	void ExecuteUbergraph_UI_AdvGraphics(int32 EntryPoint);
	void Tick(const struct FGeometry& MyGeometry, float InDeltaTime);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"UI_AdvGraphics_C">();
	}
	static class UUI_AdvGraphics_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UUI_AdvGraphics_C>();
	}
};
static_assert(alignof(UUI_AdvGraphics_C) == 0x000008, "Wrong alignment on UUI_AdvGraphics_C");
static_assert(sizeof(UUI_AdvGraphics_C) == 0x0004A0, "Wrong size on UUI_AdvGraphics_C");
static_assert(offsetof(UUI_AdvGraphics_C, UberGraphFrame) == 0x0002E0, "Member 'UUI_AdvGraphics_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, HoverAudio) == 0x0002E8, "Member 'UUI_AdvGraphics_C::HoverAudio' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, HoverControls) == 0x0002F0, "Member 'UUI_AdvGraphics_C::HoverControls' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, HoverGame) == 0x0002F8, "Member 'UUI_AdvGraphics_C::HoverGame' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, HoverDisplay) == 0x000300, "Member 'UUI_AdvGraphics_C::HoverDisplay' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, HoverSave) == 0x000308, "Member 'UUI_AdvGraphics_C::HoverSave' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, HoverBack) == 0x000310, "Member 'UUI_AdvGraphics_C::HoverBack' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, AntiAliaDown) == 0x000318, "Member 'UUI_AdvGraphics_C::AntiAliaDown' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, AntiAliaUp) == 0x000320, "Member 'UUI_AdvGraphics_C::AntiAliaUp' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, BackButton) == 0x000328, "Member 'UUI_AdvGraphics_C::BackButton' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Button) == 0x000330, "Member 'UUI_AdvGraphics_C::Button' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Button_1) == 0x000338, "Member 'UUI_AdvGraphics_C::Button_1' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Button_2) == 0x000340, "Member 'UUI_AdvGraphics_C::Button_2' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Button_4) == 0x000348, "Member 'UUI_AdvGraphics_C::Button_4' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Button_27) == 0x000350, "Member 'UUI_AdvGraphics_C::Button_27' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, DLSSDOWN) == 0x000358, "Member 'UUI_AdvGraphics_C::DLSSDOWN' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, DLSSUP) == 0x000360, "Member 'UUI_AdvGraphics_C::DLSSUP' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, FoliageDown) == 0x000368, "Member 'UUI_AdvGraphics_C::FoliageDown' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, FoliageDown_1) == 0x000370, "Member 'UUI_AdvGraphics_C::FoliageDown_1' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, FoliageUp) == 0x000378, "Member 'UUI_AdvGraphics_C::FoliageUp' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, FoliageUp_1) == 0x000380, "Member 'UUI_AdvGraphics_C::FoliageUp_1' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image) == 0x000388, "Member 'UUI_AdvGraphics_C::Image' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_0) == 0x000390, "Member 'UUI_AdvGraphics_C::Image_0' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_1) == 0x000398, "Member 'UUI_AdvGraphics_C::Image_1' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_2) == 0x0003A0, "Member 'UUI_AdvGraphics_C::Image_2' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_3) == 0x0003A8, "Member 'UUI_AdvGraphics_C::Image_3' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_4) == 0x0003B0, "Member 'UUI_AdvGraphics_C::Image_4' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_5) == 0x0003B8, "Member 'UUI_AdvGraphics_C::Image_5' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_6) == 0x0003C0, "Member 'UUI_AdvGraphics_C::Image_6' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_7) == 0x0003C8, "Member 'UUI_AdvGraphics_C::Image_7' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_8) == 0x0003D0, "Member 'UUI_AdvGraphics_C::Image_8' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_9) == 0x0003D8, "Member 'UUI_AdvGraphics_C::Image_9' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_10) == 0x0003E0, "Member 'UUI_AdvGraphics_C::Image_10' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_11) == 0x0003E8, "Member 'UUI_AdvGraphics_C::Image_11' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_12) == 0x0003F0, "Member 'UUI_AdvGraphics_C::Image_12' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_13) == 0x0003F8, "Member 'UUI_AdvGraphics_C::Image_13' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_14) == 0x000400, "Member 'UUI_AdvGraphics_C::Image_14' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_15) == 0x000408, "Member 'UUI_AdvGraphics_C::Image_15' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_16) == 0x000410, "Member 'UUI_AdvGraphics_C::Image_16' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_17) == 0x000418, "Member 'UUI_AdvGraphics_C::Image_17' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Image_18) == 0x000420, "Member 'UUI_AdvGraphics_C::Image_18' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, OptionsPaper) == 0x000428, "Member 'UUI_AdvGraphics_C::OptionsPaper' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, PostProcessDown) == 0x000430, "Member 'UUI_AdvGraphics_C::PostProcessDown' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, PostProcessUp) == 0x000438, "Member 'UUI_AdvGraphics_C::PostProcessUp' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, SaveButton) == 0x000440, "Member 'UUI_AdvGraphics_C::SaveButton' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, ShadowDown) == 0x000448, "Member 'UUI_AdvGraphics_C::ShadowDown' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, ShadowUp) == 0x000450, "Member 'UUI_AdvGraphics_C::ShadowUp' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, TextureDown) == 0x000458, "Member 'UUI_AdvGraphics_C::TextureDown' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, TextureUp) == 0x000460, "Member 'UUI_AdvGraphics_C::TextureUp' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, ViewDisDown) == 0x000468, "Member 'UUI_AdvGraphics_C::ViewDisDown' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, ViewDisUp) == 0x000470, "Member 'UUI_AdvGraphics_C::ViewDisUp' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Go_Back_To) == 0x000478, "Member 'UUI_AdvGraphics_C::Go_Back_To' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, FoliageQ) == 0x000480, "Member 'UUI_AdvGraphics_C::FoliageQ' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, ShadowQ) == 0x000484, "Member 'UUI_AdvGraphics_C::ShadowQ' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, TextureQ) == 0x000488, "Member 'UUI_AdvGraphics_C::TextureQ' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, PostProcessQ) == 0x00048C, "Member 'UUI_AdvGraphics_C::PostProcessQ' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, AntiAliasing) == 0x000490, "Member 'UUI_AdvGraphics_C::AntiAliasing' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, ViewDistance) == 0x000494, "Member 'UUI_AdvGraphics_C::ViewDistance' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, Global_illum) == 0x000498, "Member 'UUI_AdvGraphics_C::Global_illum' has a wrong offset!");
static_assert(offsetof(UUI_AdvGraphics_C, VisualEffect) == 0x00049C, "Member 'UUI_AdvGraphics_C::VisualEffect' has a wrong offset!");

}

