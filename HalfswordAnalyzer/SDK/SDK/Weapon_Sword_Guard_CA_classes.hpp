﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: Weapon_Sword_Guard_CA

#include "Basic.hpp"

#include "Modular_Sword_Guard_Master_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass Weapon_Sword_Guard_CA.Weapon_Sword_Guard_CA_C
// 0x0000 (0x0528 - 0x0528)
class AWeapon_Sword_Guard_CA_C final : public AModular_Sword_Guard_Master_C
{
public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"Weapon_Sword_Guard_CA_C">();
	}
	static class AWeapon_Sword_Guard_CA_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AWeapon_Sword_Guard_CA_C>();
	}
};
static_assert(alignof(AWeapon_Sword_Guard_CA_C) == 0x000008, "Wrong alignment on AWeapon_Sword_Guard_CA_C");
static_assert(sizeof(AWeapon_Sword_Guard_CA_C) == 0x000528, "Wrong size on AWeapon_Sword_Guard_CA_C");

}

