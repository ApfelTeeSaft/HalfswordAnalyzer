﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: ModularWeaponBP_WarStaff_B

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "ModularWeaponBP_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass ModularWeaponBP_WarStaff_B.ModularWeaponBP_WarStaff_B_C
// 0x00A8 (0x0BF0 - 0x0B48)
class AModularWeaponBP_WarStaff_B_C final : public AModularWeaponBP_C
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame_ModularWeaponBP_WarStaff_B_C;       // 0x0B48(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class USceneComponent*                        Tip14;                                             // 0x0B50(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip13;                                             // 0x0B58(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip12;                                             // 0x0B60(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip11;                                             // 0x0B68(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip10;                                             // 0x0B70(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip9;                                              // 0x0B78(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip8;                                              // 0x0B80(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip7;                                              // 0x0B88(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip6;                                              // 0x0B90(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip5;                                              // 0x0B98(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip4;                                              // 0x0BA0(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip3;                                              // 0x0BA8(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip2;                                              // 0x0BB0(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Base1_1;                                           // 0x0BB8(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UBoxComponent*                          Box;                                               // 0x0BC0(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Base1_0;                                           // 0x0BC8(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        Tip1;                                              // 0x0BD0(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UArrowComponent*                        Arrow3;                                            // 0x0BD8(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UStaticMeshComponent*                   Blade;                                             // 0x0BE0(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UStaticMeshComponent*                   Grip_0;                                            // 0x0BE8(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)

public:
	void BndEvt__ModularWeaponBP_Axe_Blade_K2Node_ComponentBoundEvent_0_ComponentHitSignature__DelegateSignature(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, const struct FVector& NormalImpulse, const struct FHitResult& Hit);
	void BndEvt__ModularWeaponBP_Axe_Grip_K2Node_ComponentBoundEvent_1_ComponentHitSignature__DelegateSignature(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, const struct FVector& NormalImpulse, const struct FHitResult& Hit);
	void ExecuteUbergraph_ModularWeaponBP_WarStaff_B(int32 EntryPoint);
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"ModularWeaponBP_WarStaff_B_C">();
	}
	static class AModularWeaponBP_WarStaff_B_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<AModularWeaponBP_WarStaff_B_C>();
	}
};
static_assert(alignof(AModularWeaponBP_WarStaff_B_C) == 0x000008, "Wrong alignment on AModularWeaponBP_WarStaff_B_C");
static_assert(sizeof(AModularWeaponBP_WarStaff_B_C) == 0x000BF0, "Wrong size on AModularWeaponBP_WarStaff_B_C");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, UberGraphFrame_ModularWeaponBP_WarStaff_B_C) == 0x000B48, "Member 'AModularWeaponBP_WarStaff_B_C::UberGraphFrame_ModularWeaponBP_WarStaff_B_C' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip14) == 0x000B50, "Member 'AModularWeaponBP_WarStaff_B_C::Tip14' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip13) == 0x000B58, "Member 'AModularWeaponBP_WarStaff_B_C::Tip13' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip12) == 0x000B60, "Member 'AModularWeaponBP_WarStaff_B_C::Tip12' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip11) == 0x000B68, "Member 'AModularWeaponBP_WarStaff_B_C::Tip11' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip10) == 0x000B70, "Member 'AModularWeaponBP_WarStaff_B_C::Tip10' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip9) == 0x000B78, "Member 'AModularWeaponBP_WarStaff_B_C::Tip9' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip8) == 0x000B80, "Member 'AModularWeaponBP_WarStaff_B_C::Tip8' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip7) == 0x000B88, "Member 'AModularWeaponBP_WarStaff_B_C::Tip7' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip6) == 0x000B90, "Member 'AModularWeaponBP_WarStaff_B_C::Tip6' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip5) == 0x000B98, "Member 'AModularWeaponBP_WarStaff_B_C::Tip5' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip4) == 0x000BA0, "Member 'AModularWeaponBP_WarStaff_B_C::Tip4' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip3) == 0x000BA8, "Member 'AModularWeaponBP_WarStaff_B_C::Tip3' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip2) == 0x000BB0, "Member 'AModularWeaponBP_WarStaff_B_C::Tip2' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Base1_1) == 0x000BB8, "Member 'AModularWeaponBP_WarStaff_B_C::Base1_1' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Box) == 0x000BC0, "Member 'AModularWeaponBP_WarStaff_B_C::Box' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Base1_0) == 0x000BC8, "Member 'AModularWeaponBP_WarStaff_B_C::Base1_0' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Tip1) == 0x000BD0, "Member 'AModularWeaponBP_WarStaff_B_C::Tip1' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Arrow3) == 0x000BD8, "Member 'AModularWeaponBP_WarStaff_B_C::Arrow3' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Blade) == 0x000BE0, "Member 'AModularWeaponBP_WarStaff_B_C::Blade' has a wrong offset!");
static_assert(offsetof(AModularWeaponBP_WarStaff_B_C, Grip_0) == 0x000BE8, "Member 'AModularWeaponBP_WarStaff_B_C::Grip_0' has a wrong offset!");

}

