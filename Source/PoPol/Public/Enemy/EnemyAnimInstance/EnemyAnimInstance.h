// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Type/CharacterType.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	//Event Blueprint Initialize Animation�� ���� ����̴�.
	virtual void NativeInitializeAnimation() override;

	////Event Blueprint Update Animation�� ���� ����̴�.
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AEnemyCharacter* EnemyCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* EnemyCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	//�߰� ����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EEnemyState EnemyState;
};
