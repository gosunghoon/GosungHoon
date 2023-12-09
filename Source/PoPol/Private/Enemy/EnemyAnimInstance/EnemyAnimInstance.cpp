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
		//GetCharacterMovement : 캐릭터 이동 구성요소를 반환한다.
		//즉 이것을 사용하려면 #include 유형이 필요하다.
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
