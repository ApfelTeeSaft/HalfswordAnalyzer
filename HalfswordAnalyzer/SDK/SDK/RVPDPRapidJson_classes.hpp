﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: RVPDPRapidJson

#include "Basic.hpp"

#include "Engine_classes.hpp"


namespace SDK
{

// Class RVPDPRapidJson.RVPDPRapidJsonFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class URVPDPRapidJsonFunctionLibrary final : public UBlueprintFunctionLibrary
{
public:
	static bool DeserializeBool_Wrapper(const class FString& JsonString);
	static void DeSerializeBoolArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<bool>* DeSerializedResult);
	static void DeSerializeColorArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<struct FColor>* DeSerializedResult);
	static struct FColor DeserializeFColor_Wrapper(const class FString& JsonString);
	static float DeserializeFloat_Wrapper(const class FString& JsonString);
	static void DeSerializeFloatArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<float>* DeSerializedResult);
	static class FName DeserializeFName_Wrapper(const class FString& JsonString);
	static struct FRotator DeserializeFRotator_Wrapper(const class FString& JsonString);
	static class FString DeserializeFString_Wrapper(const class FString& JsonString);
	static class FText DeserializeFText_Wrapper(const class FString& JsonString);
	static struct FTransform DeserializeFTransform_Wrapper(const class FString& JsonString);
	static struct FVector DeserializeFVector_Wrapper(const class FString& JsonString);
	static void DeSerializeInt32ArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<int32>* DeSerializedResult);
	static int64 DeserializeInt64_Wrapper(const class FString& JsonString);
	static void DeSerializeInt64ArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<int64>* DeSerializedResult);
	static int32 DeserializeInt_Wrapper(const class FString& JsonString);
	static void DeSerializeNameArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<class FName>* DeSerializedResult);
	static void DeSerializeRotatorArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<struct FRotator>* DeSerializedResult);
	static void DeSerializeStringArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<class FString>* DeSerializedResult);
	static TArray<bool> DeserializeTArrayBool_Wrapper(const class FString& JsonString);
	static TArray<struct FColor> DeserializeTArrayFColor_Wrapper(const class FString& JsonString);
	static TArray<float> DeserializeTArrayFloat_Wrapper(const class FString& JsonString);
	static TArray<class FName> DeserializeTArrayFName_Wrapper(const class FString& JsonString);
	static TArray<struct FRotator> DeserializeTArrayFRotator_Wrapper(const class FString& JsonString);
	static TArray<class FString> DeserializeTArrayFString_Wrapper(const class FString& JsonString);
	static TArray<class FText> DeserializeTArrayFText_Wrapper(const class FString& JsonString);
	static TArray<struct FTransform> DeserializeTArrayFTransform_Wrapper(const class FString& JsonString);
	static TArray<struct FVector> DeserializeTArrayFVector_Wrapper(const class FString& JsonString);
	static TArray<int64> DeserializeTArrayInt64_Wrapper(const class FString& JsonString);
	static TArray<int32> DeserializeTArrayInt_Wrapper(const class FString& JsonString);
	static TArray<uint8> DeserializeTArrayUInt8_Wrapper(const class FString& JsonString);
	static void DeSerializeTextArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<class FText>* DeSerializedResult);
	static void DeSerializeTransformArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<struct FTransform>* DeSerializedResult);
	static uint8 DeserializeUInt8_Wrapper(const class FString& JsonString);
	static void DeSerializeUInt8ArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<uint8>* DeSerializedResult);
	static void DeSerializeVectorArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const class FString& StringToDeSerialize, TArray<struct FVector>* DeSerializedResult);
	static class FString SerializeBool_Wrapper(bool BoolValue);
	static void SerializeBoolArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<bool>& ArrayToSerialize, class FString* SerializedString);
	static void SerializeColorArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<struct FColor>& ArrayToSerialize, class FString* SerializedString);
	static class FString SerializeFColor_Wrapper(const struct FColor& ColorValue);
	static class FString SerializeFloat_Wrapper(float FloatValue);
	static void SerializeFloatArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<float>& ArrayToSerialize, class FString* SerializedString);
	static class FString SerializeFName_Wrapper(class FName NameValue);
	static class FString SerializeFRotator_Wrapper(const struct FRotator& RotatorValue);
	static class FString SerializeFString_Wrapper(const class FString& StringValue);
	static class FString SerializeFText_Wrapper(const class FText& TextValue);
	static class FString SerializeFTransform_Wrapper(const struct FTransform& TransformValue);
	static class FString SerializeFVector_Wrapper(const struct FVector& VectorValue);
	static void SerializeInt32ArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<int32>& ArrayToSerialize, class FString* SerializedString);
	static class FString SerializeInt64_Wrapper(int64 Int64Value);
	static void SerializeInt64ArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<int64>& ArrayToSerialize, class FString* SerializedString);
	static class FString SerializeInt_Wrapper(int32 IntValue);
	static void SerializeNameArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<class FName>& ArrayToSerialize, class FString* SerializedString);
	static void SerializeRotatorArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<struct FRotator>& ArrayToSerialize, class FString* SerializedString);
	static void SerializeStringArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<class FString>& ArrayToSerialize, class FString* SerializedString);
	static class FString SerializeTArrayBool_Wrapper(const TArray<bool>& InBools);
	static class FString SerializeTArrayFColor_Wrapper(const TArray<struct FColor>& Colors);
	static class FString SerializeTArrayFloat_Wrapper(const TArray<float>& inFloats);
	static class FString SerializeTArrayFName_Wrapper(const TArray<class FName>& InNames);
	static class FString SerializeTArrayFRotator_Wrapper(const TArray<struct FRotator>& InRotator);
	static class FString SerializeTArrayFString_Wrapper(const TArray<class FString>& InStrings);
	static class FString SerializeTArrayFText_Wrapper(const TArray<class FText>& InTexts);
	static class FString SerializeTArrayFTransform_Wrapper(const TArray<struct FTransform>& InTransform);
	static class FString SerializeTArrayFVector_Wrapper(const TArray<struct FVector>& inFVector);
	static class FString SerializeTArrayInt64_Wrapper(const TArray<int64>& InInt64s);
	static class FString SerializeTArrayInt_Wrapper(const TArray<int32>& InInts);
	static class FString SerializeTArrayUInt8_Wrapper(const TArray<uint8>& InUInt8s);
	static void SerializeTextArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<class FText>& ArrayToSerialize, class FString* SerializedString);
	static void SerializeTransformArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<struct FTransform>& ArrayToSerialize, class FString* SerializedString);
	static class FString SerializeUInt8_Wrapper(uint8 UInt8Value);
	static void SerializeUint8ArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<uint8>& ArrayToSerialize, class FString* SerializedString);
	static void SerializeVectorArrayAsync(class UObject* WorldContextObject, const struct FLatentActionInfo& LatentInfo, const TArray<struct FVector>& ArrayToSerialize, class FString* SerializedString);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"RVPDPRapidJsonFunctionLibrary">();
	}
	static class URVPDPRapidJsonFunctionLibrary* GetDefaultObj()
	{
		return GetDefaultObjImpl<URVPDPRapidJsonFunctionLibrary>();
	}
};
static_assert(alignof(URVPDPRapidJsonFunctionLibrary) == 0x000008, "Wrong alignment on URVPDPRapidJsonFunctionLibrary");
static_assert(sizeof(URVPDPRapidJsonFunctionLibrary) == 0x000028, "Wrong size on URVPDPRapidJsonFunctionLibrary");

// Class RVPDPRapidJson.RVPDPRapidJsonStructExample
// 0x0030 (0x02C0 - 0x0290)
class ARVPDPRapidJsonStructExample final : public AActor
{
public:
	uint8                                         Pad_290[0x30];                                     // 0x0290(0x0030)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"RVPDPRapidJsonStructExample">();
	}
	static class ARVPDPRapidJsonStructExample* GetDefaultObj()
	{
		return GetDefaultObjImpl<ARVPDPRapidJsonStructExample>();
	}
};
static_assert(alignof(ARVPDPRapidJsonStructExample) == 0x000008, "Wrong alignment on ARVPDPRapidJsonStructExample");
static_assert(sizeof(ARVPDPRapidJsonStructExample) == 0x0002C0, "Wrong size on ARVPDPRapidJsonStructExample");

}

