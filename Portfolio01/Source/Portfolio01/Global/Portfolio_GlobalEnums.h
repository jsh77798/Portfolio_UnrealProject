#pragma once

#include "CoreMinimal.h"

// ENUM����-> Item����
UENUM(BlueprintType)
enum class ItemType : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	GUN UMETA(DisplayName = "GUN"),
	SHOTGUN UMETA(DisplayName = "SHOTGUN"),
	POSTION UMETA(DisplayName = "POSTION"),
};
