﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: S_PhotosData

#include "Basic.hpp"


namespace SDK
{

// UserDefinedStruct S_PhotosData.S_PhotosData
// 0x0030 (0x0030 - 0x0000)
struct FS_PhotosData final
{
public:
	class FString                                 Title_2_2D8B969A4B9F4838432A0CA7236BC274;          // 0x0000(0x0010)(Edit, BlueprintVisible, ZeroConstructor, HasGetValueTypeHash)
	class FString                                 PhotoFullPath_4_77D77A244A7F8CA3B0922AA74BC2C698;  // 0x0010(0x0010)(Edit, BlueprintVisible, ZeroConstructor, HasGetValueTypeHash)
	class FString                                 ThumbnailFullPath_6_C9990D23483EE3E87BC72CBB65536E09; // 0x0020(0x0010)(Edit, BlueprintVisible, ZeroConstructor, HasGetValueTypeHash)
};
static_assert(alignof(FS_PhotosData) == 0x000008, "Wrong alignment on FS_PhotosData");
static_assert(sizeof(FS_PhotosData) == 0x000030, "Wrong size on FS_PhotosData");
static_assert(offsetof(FS_PhotosData, Title_2_2D8B969A4B9F4838432A0CA7236BC274) == 0x000000, "Member 'FS_PhotosData::Title_2_2D8B969A4B9F4838432A0CA7236BC274' has a wrong offset!");
static_assert(offsetof(FS_PhotosData, PhotoFullPath_4_77D77A244A7F8CA3B0922AA74BC2C698) == 0x000010, "Member 'FS_PhotosData::PhotoFullPath_4_77D77A244A7F8CA3B0922AA74BC2C698' has a wrong offset!");
static_assert(offsetof(FS_PhotosData, ThumbnailFullPath_6_C9990D23483EE3E87BC72CBB65536E09) == 0x000020, "Member 'FS_PhotosData::ThumbnailFullPath_6_C9990D23483EE3E87BC72CBB65536E09' has a wrong offset!");

}

