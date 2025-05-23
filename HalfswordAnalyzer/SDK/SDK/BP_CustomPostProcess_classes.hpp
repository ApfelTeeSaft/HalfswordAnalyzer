﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_CustomPostProcess

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "Engine_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass BP_CustomPostProcess.BP_CustomPostProcess_C
// 0x0710 (0x09A0 - 0x0290)
class ABP_CustomPostProcess_C final : public AActor
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0290(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UPostProcessComponent*                  PostProcess;                                       // 0x0298(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class UBoxComponent*                          Box;                                               // 0x02A0(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	class USceneComponent*                        DefaultSceneRoot;                                  // 0x02A8(0x0008)(BlueprintVisible, ZeroConstructor, InstancedReference, NonTransactional, NoDestructor, HasGetValueTypeHash)
	struct FPostProcessSettings                   PP;                                                // 0x02B0(0x06F0)(Edit, BlueprintVisible, ExposeOnSpawn)

public:
	void ExecuteUbergraph_BP_CustomPostProcess(int32 EntryPoint);
	void getPostProcess(struct FPostProcessSettings* PostProcessSettings);
	void UpdatePostProcess(const struct FPostProcessSettings& PP_0);
	void UserConstructionScript();

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BP_CustomPostProcess_C">();
	}
	static class ABP_CustomPostProcess_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<ABP_CustomPostProcess_C>();
	}
};
static_assert(alignof(ABP_CustomPostProcess_C) == 0x000010, "Wrong alignment on ABP_CustomPostProcess_C");
static_assert(sizeof(ABP_CustomPostProcess_C) == 0x0009A0, "Wrong size on ABP_CustomPostProcess_C");
static_assert(offsetof(ABP_CustomPostProcess_C, UberGraphFrame) == 0x000290, "Member 'ABP_CustomPostProcess_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(ABP_CustomPostProcess_C, PostProcess) == 0x000298, "Member 'ABP_CustomPostProcess_C::PostProcess' has a wrong offset!");
static_assert(offsetof(ABP_CustomPostProcess_C, Box) == 0x0002A0, "Member 'ABP_CustomPostProcess_C::Box' has a wrong offset!");
static_assert(offsetof(ABP_CustomPostProcess_C, DefaultSceneRoot) == 0x0002A8, "Member 'ABP_CustomPostProcess_C::DefaultSceneRoot' has a wrong offset!");
static_assert(offsetof(ABP_CustomPostProcess_C, PP) == 0x0002B0, "Member 'ABP_CustomPostProcess_C::PP' has a wrong offset!");

}

