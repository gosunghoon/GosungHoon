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

//속도 제어
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

//최종 데미지
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
//맞았을 경우
void AMainCharacter::GetHit(const FVector& ImpactPoint)
{
	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
}


//** ----- AttackSystem ----- */

// 타격 사운드
void AMainCharacter::PlayHitSound(const FVector& ImpactPoint)
{
	if (HitSound)
	{
		//타격 지점에 사운드 출력
		UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			ImpactPoint
		);
	}
}
//타격 파티클
void AMainCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{
	//타격 지점에 피 튀는 파티클 생성
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

//몽타주 애니메이션 섹션 사용
void AMainCharacter::PlayMontage(UAnimMontage* Montage, const FName& SectionName)
{
	AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName, Montage);
	}
}
//몽타주 애니메이션 사용
void AMainCharacter::PlayMontage(UAnimMontage* Montage)
{
	AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
	}
}
//맞았을 경우 반응하는 몽타주
void AMainCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	//전방 위치 값
	const FVector Forward = GetActorForwardVector();

	//타격 위치 값
	const FVector ImpactLowerd(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);

	//타격 위치 값을 노말라이즈해준다.
	const FVector ToHit = (ImpactLowerd - GetActorLocation()).GetSafeNormal();

	//Dot Product의 값은 스칼라 값이다.
	const double CosTheta = FVector::DotProduct(Forward, ToHit);

	//cos(세타)의 역코사인(아크-코사인)을 취하여 세타를 구합니다.
	double Theta = FMath::Acos(CosTheta);

	Theta = FMath::RadiansToDegrees(Theta);

	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);

	if (CrossProduct.Z < 0)
	{
		Theta = Theta * -1.f;
	}

	//기본 방향
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
//죽음 몽타주
void AMainCharacter::Death()
{
	//죽음 애니메이션 실행
	PlayMontage(DeathMontage);
	Tags.Add(FName("Dead"));
	//캡슐 콜리전 상태를 No로 변경
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
