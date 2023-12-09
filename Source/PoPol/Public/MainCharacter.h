// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameInstance/HitInterface.h"
#include "MainCharacter.generated.h"

UCLASS()
class POPOL_API AMainCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;

protected:

	/** -----MoveType----- */

	void MoveSpeed(float Speed);

	//** ----- AttackSystem ----- */

	void Attack();

	//최종 데미지
	virtual float Damage(float Damage, float defense);
	//맞았을 경우
	virtual void GetHit(const FVector& ImpactPoint);
	//사운드
	void PlayHitSound(const FVector& ImpactPoint);
	//파티클
	void SpawnHitParticles(const FVector& ImpactPoint);
	//최종 데미지
	float DMG;
	//타격 사운드 생성
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;
	//타격 파티클 생성
	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

	//** ----- PROPERTY ----- */

	//전투 타겟
	UPROPERTY(VisibleAnywhere, Category = "Target")
	AActor* CombatTarget;

	//** ----- PROPERTY ----- */

	//** ----- Montage ----- */

	//몽타주 시작(섹션)
	virtual void PlayMontage(UAnimMontage* Montage, const FName& SectionName);
	//몽타주 시작
	virtual void PlayMontage(UAnimMontage* Montage);
	//방향에 따른 맞았을 경우의 몽타주 함수
	virtual void DirectionalHitReact(const FVector& ImpactPoint);
	//죽음 몽타주
	virtual void Death();
	//애님 인스턴스
	UAnimInstance* AnimInstance;
	//맞았을 경우 반응하는 몽타주
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* HitReactMontage;
	//죽었을 경우 몽타주
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* DeathMontage;
public:

};
