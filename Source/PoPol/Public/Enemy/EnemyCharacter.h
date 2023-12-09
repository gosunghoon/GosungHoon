// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "Character/Type/CharacterType.h"
#include "Engine/DataTable.h"
#include "EnemyCharacter.generated.h"

USTRUCT(BlueprintType)
struct FEnemyStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FEnemyStats()
		: Level(1), Name("AAA"), HP(50), MaxHP(50), AttackDamage(0),
		AttackSpped(0), defense(20), WalkSpeed(200.f), RunSpeed(400.f), Gold(0), EXP(5)
	{};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EXP;
};

class UAnimMontage;


UCLASS()
class POPOL_API AEnemyCharacter : public AMainCharacter
{
	GENERATED_BODY()

public:
	/*******   MainSystem   ******/

	//Main
	AEnemyCharacter();
	//Tick
	virtual void Tick(float DeltaTime) override;
	//Enemy ��ȣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemyNum;
	//Enemy Spawn ��ȣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemySpawnNum;

	class APoPolGameMode* gameMode;

	/*******   PlayerSystem   ******/

	//EXPȹ��
	float GetEXP();
	//Goldȹ��
	int32 GetGold();

protected:
	/*******   System   ******/

	//���� �� System����
	virtual void BeginPlay() override;
	//Ÿ�� �̵�
	virtual void MoveToTarget(AActor* Target);
	//Target ����
	virtual bool InTargetRange(AActor* Target, double Radius);
	//�� ü�º���
	float GetEnemyHealthpercent();
	//�� ��������
	bool EnemyIsAlive();


	//AI��Ʈ�ѷ�
	UPROPERTY()
	class AAIController* EnemyAIController;
	//�÷��̾� ��Ʈ�ѷ�
	class APopolPlayerController* PopolPlayerController;
	//�� ���� ����
	struct FEnemyStats* EnemyStats;

	/** -----MotionWarping----- */

	//Enemy - Warp �̵� ��� ��������
	UFUNCTION(BlueprintCallable)
	void EnemyTransformWarpTarget();


	/*******   Widget   ******/

	//ü�� Widget
	UFUNCTION()
	virtual void HealthBar();
	//ü�� Widget ������Ʈ
	virtual void InitHealthBar();
	//�޴� ������ ���� �ʱ�ȭ
	virtual void InitTakeDamageText();


	/*******   Hit   ******/

	//Hit
	virtual void GetHit(const FVector& ImpactPoint) override;
	//�޴� ������
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	void EnemyPlayerRotator();
	//�ǰ��� ü��
	void EnemyReceiveDamage(float Damage);
	//���� ������
	virtual float LastDamage(float DamageAmount);
	//�޴� ������
	float EnemyTakeDamage;
	//Hit ��
	UFUNCTION(BlueprintCallable)
	virtual void HitEnd();


	/*******   Death   ******/

	//���
	virtual void Death() override;
	//��ü ����
	UFUNCTION(BlueprintCallable)
	virtual void DeathEnd();
	//�� �����˸�
	bool EnemyIsDead();

	/*******   EnemyWeapon   ******/

	//Weapon
	//���� ����
	virtual void SpawnDefaultWeapon();
	//���� �浹 ����
	UFUNCTION(BlueprintCallable)
	virtual void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);


	/*******   EnemyPatrol   ******/

	//���� ����
	virtual void StartPatrolling();
	//PatrolTime
	UPROPERTY(EditAnywhere, Category = Patrol)
	float PatrolTime;
	//Enemy����
	UPROPERTY(VisibleAnywhere, Category = Type)
	EEnemyAttackState EnemyAttackState;
	//Enemy����
	UPROPERTY(VisibleAnywhere, Category = Type)
	EEnemyState EnemyState;


	/*******   EnemyChase   ******/

	//���� ���� �߰�
	UFUNCTION()
	virtual void PawnSeen(APawn* SeenPawn);
	//�߰� ����
	virtual void ChaseTarget();

	/*******   Combat   ******/

	//���� ��� Ȯ��
	virtual void CheckCombatTarget();


	/*******   EnemyAttack   ******/

	//����
	virtual void Attack();
	//���� ��
	virtual void ClearAttackTimer();
	//���� �� ���� ����
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	//���� ���
	virtual void StartAttackTimer();

	class APopolCharacter* PopolCharacter;

private:
	/*******   System   ******/

	//���� �ν��Ͻ� ������ �ҷ���
	class UPopolGameInstance* PopolGameInstance;
	//������ ������ �ҷ���
	struct FEnemyWeaponData* EnemyWeaponData;
	//��� ����
	UPROPERTY(EditAnywhere,Category = MotionWarping)
	class UEnemyMotionWarpingComponent* EnemyMotionWarpingComponent;

	FRotator EnemyRotation;

	/*******   EnemyWeapon   ******/

	//Enemy����
	UPROPERTY(VisibleAnywhere, Category = EnemyWeapon)
	class AEnemyWeapon* DefaultWeapon;
	//���� �ΰ� ��� ����
	UPROPERTY(EditAnywhere, Category = EnemyWeapon)
	bool DoubleWeapon;
	//Enemy����(�ְ�)
	UPROPERTY(VisibleAnywhere, Category = EnemyWeapon)
	class AEnemyWeapon* DefaultWeapon_Two;


	/*******   Death   ******/

	//��� �ð�
	UPROPERTY(EditAnywhere, Category = Death)
	float DeathTime;


	/*******   Chase   ******/

	//���� ����
	UPROPERTY(VisibleAnywhere, Category = Chase)
	class UPawnSensingComponent* Sensing;
	//�߰� ��� ����
	UPROPERTY(EditAnywhere, Category = Chase)
	double AcceptanceRadius = 20.f;


	/*******   Combat   ******/

	//���� Ÿ�� ����
	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 1000.f;


	/*******   Widget   ******/

	//���� ü�¹� �� ü�� �ؽ�Ʈ
	UPROPERTY(EditAnywhere, Category = Widget)
	class UHealthBarComponent* HealthBarComponent;

	//Damage Text ȭ�� ǥ��
	UPROPERTY(EditAnywhere, Category = Widget)
	class UTakeDamageWidgetComponent* TakeDamageWidgetComponent;

	//������ ������� �ð�
	FTimerHandle TakeDamageHandle;

	/*******   Attack   ******/

	//���� ����
	UPROPERTY(EditAnywhere, Category = "Attack")
	double AttackRadius = 200.f;
	//���� ��� �ð�
	FTimerHandle AttackTimer;
	//���� �ִϸ��̼� ����
	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray<FName> TArraySection;
	//���� ������
	float EnemyLastDamage;
	//Hit ������
	UPROPERTY(EditAnywhere, Category = "Attack")
	float HitDamage;


	/*******   Montage   ******/

	//���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* AttackMontage;


public:
	FORCEINLINE EEnemyState GetEnemyState() const { return EnemyState; }

};

