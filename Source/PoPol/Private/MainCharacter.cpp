// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInstance/HitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

///** -----MoveType----- */

//�ӵ� ����
void AMainCharacter::MoveSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AMainCharacter::Attack()
{
	if (CombatTarget->ActorHasTag(FName("Dead")))
	{
		CombatTarget = nullptr;
	}
}

//���� ������
float AMainCharacter::Damage(float Damage, float defense)
{
	if (defense >= Damage)
	{
		DMG = 0;
	}
	else
	{
		DMG = Damage - defense;
	}
	return DMG;
}
//�¾��� ���
void AMainCharacter::GetHit(const FVector& ImpactPoint)
{
	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
}


//** ----- AttackSystem ----- */

// Ÿ�� ����
void AMainCharacter::PlayHitSound(const FVector& ImpactPoint)
{
	if (HitSound)
	{
		//Ÿ�� ������ ���� ���
		UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			ImpactPoint
		);
	}
}
//Ÿ�� ��ƼŬ
void AMainCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{
	//Ÿ�� ������ �� Ƣ�� ��ƼŬ ����
	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			ImpactPoint
		);
	}
}


//** ----- Montage ----- */

//��Ÿ�� �ִϸ��̼� ���� ���
void AMainCharacter::PlayMontage(UAnimMontage* Montage, const FName& SectionName)
{
	AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName, Montage);
	}
}
//��Ÿ�� �ִϸ��̼� ���
void AMainCharacter::PlayMontage(UAnimMontage* Montage)
{
	AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
	}
}
//�¾��� ��� �����ϴ� ��Ÿ��
void AMainCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	//���� ��ġ ��
	const FVector Forward = GetActorForwardVector();

	//Ÿ�� ��ġ ��
	const FVector ImpactLowerd(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);

	//Ÿ�� ��ġ ���� �븻���������ش�.
	const FVector ToHit = (ImpactLowerd - GetActorLocation()).GetSafeNormal();

	//Dot Product�� ���� ��Į�� ���̴�.
	const double CosTheta = FVector::DotProduct(Forward, ToHit);

	//cos(��Ÿ)�� ���ڻ���(��ũ-�ڻ���)�� ���Ͽ� ��Ÿ�� ���մϴ�.
	double Theta = FMath::Acos(CosTheta);

	Theta = FMath::RadiansToDegrees(Theta);

	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);

	if (CrossProduct.Z < 0)
	{
		Theta = Theta * -1.f;
	}

	//�⺻ ����
	FName Section("FromBack");

	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = FName("FromFront");
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName("FromRight");
	}

	PlayMontage(HitReactMontage, Section);
}
//���� ��Ÿ��
void AMainCharacter::Death()
{
	//���� �ִϸ��̼� ����
	PlayMontage(DeathMontage);
	Tags.Add(FName("Dead"));
	//ĸ�� �ݸ��� ���¸� No�� ����
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
