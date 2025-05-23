﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BPI_Living_Thing

#include "Basic.hpp"

#include "CoreUObject_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass BPI_Living_Thing.BPI_Living_Thing_C
// 0x0000 (0x0000 - 0x0000)
class IBPI_Living_Thing_C final
{
public:
	void Attach_Decal(class UDecalComponent* Decal, const struct FAttached_Transform_Str& Attach_Param, bool* Nul);
	void Get_Damage(const struct FVector& Impulse, const struct FVector& Velocity, const struct FVector& Location, const struct FVector& Normal, class FName bone, double Raw_Damage, double Cutting_Power, bool Inside, class UPrimitiveComponent* Damaged_Mesh, int32 Dism_Blunt, bool Lower_Threshold, bool Shockwave, class UPrimitiveComponent* Hit_By_Component, bool Stab_, class UBoxComponent* Hit_Box, bool Ignore_Invincibility, double* Damage_Out);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BPI_Living_Thing_C">();
	}
	static class IBPI_Living_Thing_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<IBPI_Living_Thing_C>();
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
static_assert(alignof(IBPI_Living_Thing_C) == 0x000001, "Wrong alignment on IBPI_Living_Thing_C");
static_assert(sizeof(IBPI_Living_Thing_C) == 0x000001, "Wrong size on IBPI_Living_Thing_C");

}

