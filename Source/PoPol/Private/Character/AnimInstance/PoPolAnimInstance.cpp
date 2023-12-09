// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AnimInstance/PoPolAnimInstance.h"
#include "Character/PopolCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Type/CharacterType.h"

/*******   System   ******/

//Animation Beginplay
void UPoPolAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//형 변환
	PoPolCharacter = Cast<APopolCharacter>(TryGetPawnOwner());
	if (PoPolCharacter)
	{
		//플레이어 이동
		PopolCharacterMovement = PoPolCharacter->GetCharacterMovement();
	}
}
//Animation Tick
void UPoPolAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PopolCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(PopolCharacterMovement->Velocity);	//속도 지정
		bIsFalling = PopolCharacterMovement->IsFalling();								//공중 여부
		CharacterMoveType = PoPolCharacter->GetCharacterMoveType();						//캐릭터 움직임 상태
		CharacterAttackType = PoPolCharacter->GetCharacterAttackType();					//캐릭터 공격 상태
		AttackingType = PoPolCharacter->GetAttackingType();								//캐릭터 공격 실행 중 상태
		AttackingEndType = PoPolCharacter->GetAttackingEndType();						//캐릭터 공격 끝 상태
	}
}
