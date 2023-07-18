#pragma once

#include "CoreMinimal.h"

// �ִϸ��̼ǿ� �����Ұų�
// ĳ���Ϳ� ������ �ų�?

// UMETA�� �� �ɼǸ��� ������ �ٸ��� ���ټ� �ֽ��ϴ�.

UENUM(BlueprintType)
enum class EAniState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	LeftMove UMETA(DisplayName = "LeftMove"),
	RightMove UMETA(DisplayName = "RightMove"),
	ForwardMove UMETA(DisplayName = "ForwardMove"),
	BackwardMove UMETA(DisplayName = "BackwardMove"),
	Run UMETA(DisplayName = "Run"),
	Crouch UMETA(DisplayName = "Crouch"),
	Aiming UMETA(DisplayName = "Aiming"),
	Attack UMETA(DisplayName = "Attack"),
};


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