﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Modular_PA_Head_Center_Mid_Tier_004

#include "Basic.hpp"

#include "Modular_PA_Head_Center_Master_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass Modular_PA_Head_Center_Mid_Tier_004.Modular_PA_Head_Center_Mid_Tier_004_C
// 0x0010 (0x0518 - 0x0508)
class AModular_PA_Head_Center_Mid_Tier_004_C final : public AModular_PA_Head_Center_Master_C
{
public:
	class USceneComponent*                        Tip1;                                              // 0x0508(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip2;                                              // 0x0510(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"Modular_PA_Head_Center_Mid_Tier_004_C">();
	}
	static class AModular_PA_Head_Center_Mid_Tier_004_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AModular_PA_Head_Center_Mid_Tier_004_C>();
	}
};
static_assert(alignof(AModular_PA_Head_Center_Mid_Tier_004_C) == 0x000008, "Wrong alignment on AModular_PA_Head_Center_Mid_Tier_004_C");
static_assert(sizeof(AModular_PA_Head_Center_Mid_Tier_004_C) == 0x000518, "Wrong size on AModular_PA_Head_Center_Mid_Tier_004_C");
static_assert(offsetof(AModular_PA_Head_Center_Mid_Tier_004_C, Tip1) == 0x000508, "Member 'AModular_PA_Head_Center_Mid_Tier_004_C::Tip1' has a wrong offset!");
static_assert(offsetof(AModular_PA_Head_Center_Mid_Tier_004_C, Tip2) == 0x000510, "Member 'AModular_PA_Head_Center_Mid_Tier_004_C::Tip2' has a wrong offset!");

}

