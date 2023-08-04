#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class AIState : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	IDLE UMETA(DisplayName = "IDLE"),
	MOVE UMETA(DisplayName = "MOVE"),
	PATROL UMETA(DisplayName = "PATROL"),
	RETURN UMETA(DisplayName = "RETURN"),
	ATTACK UMETA(DisplayName = "ATTACK"),
	DEATH UMETA(DisplayName = "DEATH"),
};