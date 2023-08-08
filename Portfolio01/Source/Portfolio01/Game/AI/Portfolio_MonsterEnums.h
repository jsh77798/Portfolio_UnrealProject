#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class AIState : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	IDLE UMETA(DisplayName = "IDLE"),
	MOVE UMETA(DisplayName = "MOVE"),
	RETURN UMETA(DisplayName = "RETURN"),
	PATROL UMETA(DisplayName = "PATROL"),
	ATTACK UMETA(DisplayName = "ATTACK"),
	DEATH UMETA(DisplayName = "DEATH"),
};
