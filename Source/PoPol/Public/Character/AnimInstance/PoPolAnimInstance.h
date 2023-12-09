// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Type/CharacterType.h"
#include "PoPolAnimInstance.generated.h"


class APopolCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class POPOL_API UPoPolAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/*******   System   ******/

	//Animation Beginplay
	virtual void NativeInitializeAnimation() override;
	//Animation Tick
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	/*******   PROPERTY   ******/

	UPROPERTY(BlueprintReadOnly)
	APopolCharacter* PoPolCharacter;	//플레이어
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* PopolCharacterMovement;	//플레이어 이동
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;										//플레이어 속도 지정
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsFalling;										//공중 여부



	/*******   Type   ******/

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECharacterMoveType CharacterMoveType;					//캐릭터 움직임 상태
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECharacterAttackType CharacterAttackType;				//캐릭터 공격 상태
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EAttackingType AttackingType;							//캐릭터 공격 실행 중 상태
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EAttackingEndType AttackingEndType;						//캐릭터 공격 끝 상태
};
