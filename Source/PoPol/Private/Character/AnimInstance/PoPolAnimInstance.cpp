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

	//�� ��ȯ
	PoPolCharacter = Cast<APopolCharacter>(TryGetPawnOwner());
	if (PoPolCharacter)
	{
		//�÷��̾� �̵�
		PopolCharacterMovement = PoPolCharacter->GetCharacterMovement();
	}
}
//Animation Tick
void UPoPolAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PopolCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(PopolCharacterMovement->Velocity);	//�ӵ� ����
		bIsFalling = PopolCharacterMovement->IsFalling();								//���� ����
		CharacterMoveType = PoPolCharacter->GetCharacterMoveType();						//ĳ���� ������ ����
		CharacterAttackType = PoPolCharacter->GetCharacterAttackType();					//ĳ���� ���� ����
		AttackingType = PoPolCharacter->GetAttackingType();								//ĳ���� ���� ���� �� ����
		AttackingEndType = PoPolCharacter->GetAttackingEndType();						//ĳ���� ���� �� ����
	}
}
