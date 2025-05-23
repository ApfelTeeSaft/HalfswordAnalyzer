﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BPI_WeaponInteraction

#include "Basic.hpp"

#include "CoreUObject_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass BPI_WeaponInteraction.BPI_WeaponInteraction_C
// 0x0000 (0x0000 - 0x0000)
class IBPI_WeaponInteraction_C final
{
public:
	void Weapon_HIt(class UPrimitiveComponent* Hit_Component, const struct FVector& Weapon_Velocity, const struct FHitResult& Hit_Result, double EdgeAllignment_Dot, bool Laser_temp_, class UClass* Weapon);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BPI_WeaponInteraction_C">();
	}
	static class IBPI_WeaponInteraction_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<IBPI_WeaponInteraction_C>();
	}

	class UObject* AsUObject()
	{
		return reinterpret_cast<UObject*>(this);
	}
	const class UObject* AsUObject() const
	{
		return reinterpret_cast<const UObject*>(this);
	}
};
static_assert(alignof(IBPI_WeaponInteraction_C) == 0x000001, "Wrong alignment on IBPI_WeaponInteraction_C");
static_assert(sizeof(IBPI_WeaponInteraction_C) == 0x000001, "Wrong size on IBPI_WeaponInteraction_C");

}

