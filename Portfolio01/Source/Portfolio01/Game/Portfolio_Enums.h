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