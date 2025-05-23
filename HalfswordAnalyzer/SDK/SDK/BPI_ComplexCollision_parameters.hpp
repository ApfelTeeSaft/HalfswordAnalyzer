﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BPI_ComplexCollision

#include "Basic.hpp"

#include "CoreUObject_structs.hpp"
#include "PhysicsCore_structs.hpp"


namespace SDK::Params
{

// Function BPI_ComplexCollision.BPI_ComplexCollision_C.Deal Complex Damage
// 0x00D8 (0x00D8 - 0x0000)
struct BPI_ComplexCollision_C_Deal_Complex_Damage final
{
public:
	class UPrimitiveComponent*                    Hit_Component;                                     // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, NoDestructor, HasGetValueTypeHash)
	class UPrimitiveComponent*                    Collided_Component;                                // 0x0008(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, NoDestructor, HasGetValueTypeHash)
	class FName                                   Hit_Bone;                                          // 0x0010(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                Location;                                          // 0x0018(0x0018)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                Normal;                                            // 0x0030(0x0018)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                Hit_Velocity;                                      // 0x0048(0x0018)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	struct FVector                                Hit_Impulse;                                       // 0x0060(0x0018)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Cutting_Power;                                     // 0x0078(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Stab_Rate;                                         // 0x0080(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Rigidity;                                          // 0x0088(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	int32                                         Blunt_Destruction_Int;                             // 0x0090(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Lower_Threshold_In;                                // 0x0094(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Damage_Parent_Bone_;                               // 0x0095(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_96[0x2];                                       // 0x0096(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	double                                        Kick_Power;                                        // 0x0098(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UBoxComponent*                          Hit_Box;                                           // 0x00A0(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, NoDestructor, HasGetValueTypeHash)
	bool                                          Ignore_Invincibility;                              // 0x00A8(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	EPhysicalSurface                              Hit_Surface;                                       // 0x00A9(0x0001)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_AA[0x6];                                       // 0x00AA(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	double                                        Damage_Out;                                        // 0x00B0(0x0008)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Cutting_Rate_Out;                                  // 0x00B8(0x0008)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Rigidity_Out;                                      // 0x00C0(0x0008)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                        Material_Density_Out;                              // 0x00C8(0x0008)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          Lower_Threshold_Out;                               // 0x00D0(0x0001)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};
static_assert(alignof(BPI_ComplexCollision_C_Deal_Complex_Damage) == 0x000008, "Wrong alignment on BPI_ComplexCollision_C_Deal_Complex_Damage");
static_assert(sizeof(BPI_ComplexCollision_C_Deal_Complex_Damage) == 0x0000D8, "Wrong size on BPI_ComplexCollision_C_Deal_Complex_Damage");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Hit_Component) == 0x000000, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Hit_Component' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Collided_Component) == 0x000008, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Collided_Component' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Hit_Bone) == 0x000010, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Hit_Bone' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Location) == 0x000018, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Location' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Normal) == 0x000030, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Normal' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Hit_Velocity) == 0x000048, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Hit_Velocity' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Hit_Impulse) == 0x000060, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Hit_Impulse' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Cutting_Power) == 0x000078, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Cutting_Power' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Stab_Rate) == 0x000080, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Stab_Rate' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Rigidity) == 0x000088, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Rigidity' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Blunt_Destruction_Int) == 0x000090, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Blunt_Destruction_Int' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Lower_Threshold_In) == 0x000094, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Lower_Threshold_In' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Damage_Parent_Bone_) == 0x000095, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Damage_Parent_Bone_' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Kick_Power) == 0x000098, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Kick_Power' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Hit_Box) == 0x0000A0, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Hit_Box' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Ignore_Invincibility) == 0x0000A8, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Ignore_Invincibility' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Hit_Surface) == 0x0000A9, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Hit_Surface' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Damage_Out) == 0x0000B0, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Damage_Out' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Cutting_Rate_Out) == 0x0000B8, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Cutting_Rate_Out' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Rigidity_Out) == 0x0000C0, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Rigidity_Out' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Material_Density_Out) == 0x0000C8, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Material_Density_Out' has a wrong offset!");
static_assert(offsetof(BPI_ComplexCollision_C_Deal_Complex_Damage, Lower_Threshold_Out) == 0x0000D0, "Member 'BPI_ComplexCollision_C_Deal_Complex_Damage::Lower_Threshold_Out' has a wrong offset!");

}

