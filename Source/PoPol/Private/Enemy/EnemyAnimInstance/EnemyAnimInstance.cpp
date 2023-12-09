// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAnimInstance/EnemyAnimInstance.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());
	if (EnemyCharacter)
	{
		//GetCharacterMovement : ĳ���� �̵� ������Ҹ� ��ȯ�Ѵ�.
		//�� �̰��� ����Ϸ��� #include ������ �ʿ��ϴ�.
		EnemyCharacterMovement = EnemyCharacter->GetCharacterMovement();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (EnemyCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(EnemyCharacterMovement->Velocity);
		EnemyState = EnemyCharacter->GetEnemyState();

	}
}
