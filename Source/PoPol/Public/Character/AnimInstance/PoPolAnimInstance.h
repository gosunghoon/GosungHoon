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
	APopolCharacter* PoPolCharacter;	//�÷��̾�
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* PopolCharacterMovement;	//�÷��̾� �̵�
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;										//�÷��̾� �ӵ� ����
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsFalling;										//���� ����



	/*******   Type   ******/

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECharacterMoveType CharacterMoveType;					//ĳ���� ������ ����
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECharacterAttackType CharacterAttackType;				//ĳ���� ���� ����
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EAttackingType AttackingType;							//ĳ���� ���� ���� �� ����
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EAttackingEndType AttackingEndType;						//ĳ���� ���� �� ����
};
