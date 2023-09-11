#pragma once

#include "CoreMinimal.h"

// ENUM정보-> Monster행동(애니메이션)
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
	STUN UMETA(DisplayName = "STUN")
};
