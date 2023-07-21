#pragma once

#include "CoreMinimal.h"

// 애니메이션에 집중할거냐
// 캐릭터에 집중할 거냐?

// UMETA는 각 옵션마다 설정을 다르게 해줄수 있습니다.

UENUM(BlueprintType)
enum class EAniState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	LeftMove UMETA(DisplayName = "LeftMove"),
	RightMove UMETA(DisplayName = "RightMove"),
	ForwardMove UMETA(DisplayName = "ForwardMove"),
	BackwardMove UMETA(DisplayName = "BackwardMove"),
};

	/*
	Run UMETA(DisplayName = "Run"),
	Crouch UMETA(DisplayName = "Crouch"),
	CrouchUP UMETA(DisplayName = "CrouchUP"),


	W_Idle UMETA(DisplayName = "W_Idle"),
	W_LeftMove UMETA(DisplayName = "W_LeftMove"),
	W_RightMove UMETA(DisplayName = "W_RightMove"),
	W_ForwardMove UMETA(DisplayName = "W_ForwardMove"),
	W_BackwardMove UMETA(DisplayName = "W_BackwardMove"),
	W_Run UMETA(DisplayName = "W_Run"),
	W_Crouch UMETA(DisplayName = "W_Crouch"),
	W_CrouchUP UMETA(DisplayName = "W_CrouchUP"),
	W_Aiming UMETA(DisplayName = "W_Aiming"),
	W_Attack UMETA(DisplayName = "W_Attack"),
	*/




UENUM(BlueprintType)
enum class AIState : uint8
{
	IDLE UMETA(DisplayName = "IDLE"),

	MOVE UMETA(DisplayName = "MOVE"),
	LeftMove UMETA(DisplayName = "LeftMove"),
	RightMove UMETA(DisplayName = "RightMove"),
	ForwardMove UMETA(DisplayName = "ForwardMove"),
	BackwardMove UMETA(DisplayName = "BackwardMove"),

	PATROL UMETA(DisplayName = "PATROL"),

	RETURN UMETA(DisplayName = "RETURN"),

	ATTACK UMETA(DisplayName = "ATTACK"),

	DEATH UMETA(DisplayName = "DEATH"),
};