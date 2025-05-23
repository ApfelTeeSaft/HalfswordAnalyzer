﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SG_PlayerProgression

#include "Basic.hpp"

#include "SG_PlayerProgression_classes.hpp"
#include "SG_PlayerProgression_parameters.hpp"


namespace SDK
{

// Function SG_PlayerProgression.SG_PlayerProgression_C.ExecuteUbergraph_SG_PlayerProgression
// (Final, UbergraphFunction, HasDefaults)
// Parameters:
// int32                                   EntryPoint                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void USG_PlayerProgression_C::ExecuteUbergraph_SG_PlayerProgression(int32 EntryPoint)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("SG_PlayerProgression_C", "ExecuteUbergraph_SG_PlayerProgression");

	Params::SG_PlayerProgression_C_ExecuteUbergraph_SG_PlayerProgression Parms{};

	Parms.EntryPoint = EntryPoint;

	UObject::ProcessEvent(Func, &Parms);
}


// Function SG_PlayerProgression.SG_PlayerProgression_C.Save Rank Equipment Event
// (BlueprintCallable, BlueprintEvent)
// Parameters:
// const struct FStr_Loadout_Equipment&    Saved_Equipment_Struct                                 (BlueprintVisible, BlueprintReadOnly, Parm, HasGetValueTypeHash)

void USG_PlayerProgression_C::Save_Rank_Equipment_Event(const struct FStr_Loadout_Equipment& Saved_Equipment_Struct)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("SG_PlayerProgression_C", "Save Rank Equipment Event");

	Params::SG_PlayerProgression_C_Save_Rank_Equipment_Event Parms{};

	Parms.Saved_Equipment_Struct = std::move(Saved_Equipment_Struct);

	UObject::ProcessEvent(Func, &Parms);
}

}

