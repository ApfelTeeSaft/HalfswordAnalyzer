﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: UI_Checkbox

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "CoreUObject_structs.hpp"
#include "SlateCore_structs.hpp"
#include "UMG_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass UI_Checkbox.UI_Checkbox_C
// 0x00C0 (0x03A0 - 0x02E0)
class UUI_Checkbox_C final : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x02E0(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UCheckBox*                              CheckBox;                                          // 0x02E8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UTextBlock*                             CheckboxName;                                      // 0x02F0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UTextBlock*                             CheckboxValue;                                     // 0x02F8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UHorizontalBox*                         HorizontalBox_ElementsContainer;                   // 0x0300(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class FText                                   ToggleTitle;                                       // 0x0308(0x0010)(Edit, BlueprintVisible)
	class FText                                   CheckboxDefaultValueTip;                           // 0x0318(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly)
	bool                                          bDefaultValue;                                     // 0x0328(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, ExposeOnSpawn, HasGetValueTypeHash)
	bool                                          bChangeCheckboxColorWhenFocused;                   // 0x0329(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          bChangeTextColorWhenFocused;                       // 0x032A(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_32B[0x1];                                      // 0x032B(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	struct FLinearColor                           FocusedToggleAndTextColor;                         // 0x032C(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FLinearColor                           UnfocusedToggleAndTextColor;                       // 0x033C(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_34C[0x4];                                      // 0x034C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UUI_PhotoMode_C*                        PhotoModeWidget;                                   // 0x0350(0x0008)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, NoDestructor, HasGetValueTypeHash)
	class FText                                   OptionFalse;                                       // 0x0358(0x0010)(Edit, BlueprintVisible)
	class FText                                   OptionTrue;                                        // 0x0368(0x0010)(Edit, BlueprintVisible)
	TMulticastInlineDelegate<void(bool Value)>    OnCheckboxValueChanged;                            // 0x0378(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable, BlueprintCallable)
	bool                                          bShouldFocus;                                      // 0x0388(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_389[0x3];                                      // 0x0389(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	struct FMargin                                CheckboxMargin;                                    // 0x038C(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, ExposeOnSpawn)

public:
	void BndEvt__ToggleDoF_1_K2Node_ComponentBoundEvent_3_OnCheckBoxComponentStateChanged__DelegateSignature(bool bIsChecked);
	void ChangeValue(bool bValue, bool bShouldFocus_0);
	void Construct();
	void ExecuteUbergraph_UI_Checkbox(int32 EntryPoint);
	void Initialize(bool bDefaultValue_0);
	void OnMouseEnter(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent);
	void PreConstruct(bool IsDesignTime);
	void ResetCheckbox(bool bShouldFocus_0);
	void ResetToggleFocus();
	void Set_Focused_or_Unfocused_Color(bool bChangeCheckboxColorWhenFocused_0, bool bChangeTextColorWhenFocused_0, class UCheckBox* CheckBox_0, class UWidget* CheckboxTitle, class UWidget* CheckboxValue_0);
	void SetToggleFocus();
	class FText setTxtValue();
	class UWidget* ToggleUsingArrows(EUINavigation Navigation_0);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"UI_Checkbox_C">();
	}
	static class UUI_Checkbox_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UUI_Checkbox_C>();
	}
};
static_assert(alignof(UUI_Checkbox_C) == 0x000008, "Wrong alignment on UUI_Checkbox_C");
static_assert(sizeof(UUI_Checkbox_C) == 0x0003A0, "Wrong size on UUI_Checkbox_C");
static_assert(offsetof(UUI_Checkbox_C, UberGraphFrame) == 0x0002E0, "Member 'UUI_Checkbox_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, CheckBox) == 0x0002E8, "Member 'UUI_Checkbox_C::CheckBox' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, CheckboxName) == 0x0002F0, "Member 'UUI_Checkbox_C::CheckboxName' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, CheckboxValue) == 0x0002F8, "Member 'UUI_Checkbox_C::CheckboxValue' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, HorizontalBox_ElementsContainer) == 0x000300, "Member 'UUI_Checkbox_C::HorizontalBox_ElementsContainer' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, ToggleTitle) == 0x000308, "Member 'UUI_Checkbox_C::ToggleTitle' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, CheckboxDefaultValueTip) == 0x000318, "Member 'UUI_Checkbox_C::CheckboxDefaultValueTip' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, bDefaultValue) == 0x000328, "Member 'UUI_Checkbox_C::bDefaultValue' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, bChangeCheckboxColorWhenFocused) == 0x000329, "Member 'UUI_Checkbox_C::bChangeCheckboxColorWhenFocused' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, bChangeTextColorWhenFocused) == 0x00032A, "Member 'UUI_Checkbox_C::bChangeTextColorWhenFocused' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, FocusedToggleAndTextColor) == 0x00032C, "Member 'UUI_Checkbox_C::FocusedToggleAndTextColor' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, UnfocusedToggleAndTextColor) == 0x00033C, "Member 'UUI_Checkbox_C::UnfocusedToggleAndTextColor' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, PhotoModeWidget) == 0x000350, "Member 'UUI_Checkbox_C::PhotoModeWidget' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, OptionFalse) == 0x000358, "Member 'UUI_Checkbox_C::OptionFalse' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, OptionTrue) == 0x000368, "Member 'UUI_Checkbox_C::OptionTrue' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, OnCheckboxValueChanged) == 0x000378, "Member 'UUI_Checkbox_C::OnCheckboxValueChanged' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, bShouldFocus) == 0x000388, "Member 'UUI_Checkbox_C::bShouldFocus' has a wrong offset!");
static_assert(offsetof(UUI_Checkbox_C, CheckboxMargin) == 0x00038C, "Member 'UUI_Checkbox_C::CheckboxMargin' has a wrong offset!");

}

