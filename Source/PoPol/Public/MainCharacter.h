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

	//���� ������
	virtual float Damage(float Damage, float defense);
	//�¾��� ���
	virtual void GetHit(const FVector& ImpactPoint);
	//����
	void PlayHitSound(const FVector& ImpactPoint);
	//��ƼŬ
	void SpawnHitParticles(const FVector& ImpactPoint);
	//���� ������
	float DMG;
	//Ÿ�� ���� ����
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;
	//Ÿ�� ��ƼŬ ����
	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

	//** ----- PROPERTY ----- */

	//���� Ÿ��
	UPROPERTY(VisibleAnywhere, Category = "Target")
	AActor* CombatTarget;

	//** ----- PROPERTY ----- */

	//** ----- Montage ----- */

	//��Ÿ�� ����(����)
	virtual void PlayMontage(UAnimMontage* Montage, const FName& SectionName);
	//��Ÿ�� ����
	virtual void PlayMontage(UAnimMontage* Montage);
	//���⿡ ���� �¾��� ����� ��Ÿ�� �Լ�
	virtual void DirectionalHitReact(const FVector& ImpactPoint);
	//���� ��Ÿ��
	virtual void Death();
	//�ִ� �ν��Ͻ�
	UAnimInstance* AnimInstance;
	//�¾��� ��� �����ϴ� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* HitReactMontage;
	//�׾��� ��� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* DeathMontage;
public:

};
