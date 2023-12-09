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
	//Enemy 번호
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemyNum;
	//Enemy Spawn 번호
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemySpawnNum;

	class APoPolGameMode* gameMode;

	/*******   PlayerSystem   ******/

	//EXP획득
	float GetEXP();
	//Gold획득
	int32 GetGold();

protected:
	/*******   System   ******/

	//시작 시 System설정
	virtual void BeginPlay() override;
	//타겟 이동
	virtual void MoveToTarget(AActor* Target);
	//Target 범위
	virtual bool InTargetRange(AActor* Target, double Radius);
	//적 체력비율
	float GetEnemyHealthpercent();
	//적 생존여부
	bool EnemyIsAlive();


	//AI컨트롤러
	UPROPERTY()
	class AAIController* EnemyAIController;
	//플레이어 컨트롤러
	class APopolPlayerController* PopolPlayerController;
	//적 스탯 정보
	struct FEnemyStats* EnemyStats;

	/** -----MotionWarping----- */

	//Enemy - Warp 이동 대상 가져오기
	UFUNCTION(BlueprintCallable)
	void EnemyTransformWarpTarget();


	/*******   Widget   ******/

	//체력 Widget
	UFUNCTION()
	virtual void HealthBar();
	//체력 Widget 업데이트
	virtual void InitHealthBar();
	//받는 데미지 상태 초기화
	virtual void InitTakeDamageText();


	/*******   Hit   ******/

	//Hit
	virtual void GetHit(const FVector& ImpactPoint) override;
	//받는 데미지
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	void EnemyPlayerRotator();
	//피격후 체력
	void EnemyReceiveDamage(float Damage);
	//최종 데미지
	virtual float LastDamage(float DamageAmount);
	//받는 데미지
	float EnemyTakeDamage;
	//Hit 끝
	UFUNCTION(BlueprintCallable)
	virtual void HitEnd();


	/*******   Death   ******/

	//사망
	virtual void Death() override;
	//시체 제거
	UFUNCTION(BlueprintCallable)
	virtual void DeathEnd();
	//적 죽음알림
	bool EnemyIsDead();

	/*******   EnemyWeapon   ******/

	//Weapon
	//무기 생성
	virtual void SpawnDefaultWeapon();
	//무기 충돌 여부
	UFUNCTION(BlueprintCallable)
	virtual void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);


	/*******   EnemyPatrol   ******/

	//순찰 시작
	virtual void StartPatrolling();
	//PatrolTime
	UPROPERTY(EditAnywhere, Category = Patrol)
	float PatrolTime;
	//Enemy상태
	UPROPERTY(VisibleAnywhere, Category = Type)
	EEnemyAttackState EnemyAttackState;
	//Enemy상태
	UPROPERTY(VisibleAnywhere, Category = Type)
	EEnemyState EnemyState;


	/*******   EnemyChase   ******/

	//센서 반응 추격
	UFUNCTION()
	virtual void PawnSeen(APawn* SeenPawn);
	//추격 시작
	virtual void ChaseTarget();

	/*******   Combat   ******/

	//전투 대상 확인
	virtual void CheckCombatTarget();


	/*******   EnemyAttack   ******/

	//공격
	virtual void Attack();
	//공격 끝
	virtual void ClearAttackTimer();
	//공격 끝 이후 상태
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	//공격 대기
	virtual void StartAttackTimer();

	class APopolCharacter* PopolCharacter;

private:
	/*******   System   ******/

	//게임 인스턴스 파일을 불러옴
	class UPopolGameInstance* PopolGameInstance;
	//무기의 스탯을 불러옴
	struct FEnemyWeaponData* EnemyWeaponData;
	//모션 워핑
	UPROPERTY(EditAnywhere,Category = MotionWarping)
	class UEnemyMotionWarpingComponent* EnemyMotionWarpingComponent;

	FRotator EnemyRotation;

	/*******   EnemyWeapon   ******/

	//Enemy무기
	UPROPERTY(VisibleAnywhere, Category = EnemyWeapon)
	class AEnemyWeapon* DefaultWeapon;
	//무기 두개 사용 여부
	UPROPERTY(EditAnywhere, Category = EnemyWeapon)
	bool DoubleWeapon;
	//Enemy무기(쌍검)
	UPROPERTY(VisibleAnywhere, Category = EnemyWeapon)
	class AEnemyWeapon* DefaultWeapon_Two;


	/*******   Death   ******/

	//사망 시간
	UPROPERTY(EditAnywhere, Category = Death)
	float DeathTime;


	/*******   Chase   ******/

	//센서 감지
	UPROPERTY(VisibleAnywhere, Category = Chase)
	class UPawnSensingComponent* Sensing;
	//추격 대상 범위
	UPROPERTY(EditAnywhere, Category = Chase)
	double AcceptanceRadius = 20.f;


	/*******   Combat   ******/

	//전투 타겟 범위
	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 1000.f;


	/*******   Widget   ******/

	//적의 체력바 및 체력 텍스트
	UPROPERTY(EditAnywhere, Category = Widget)
	class UHealthBarComponent* HealthBarComponent;

	//Damage Text 화면 표시
	UPROPERTY(EditAnywhere, Category = Widget)
	class UTakeDamageWidgetComponent* TakeDamageWidgetComponent;

	//데미지 사라지는 시간
	FTimerHandle TakeDamageHandle;

	/*******   Attack   ******/

	//공격 범위
	UPROPERTY(EditAnywhere, Category = "Attack")
	double AttackRadius = 200.f;
	//공격 대기 시간
	FTimerHandle AttackTimer;
	//공격 애니메이션 섹션
	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray<FName> TArraySection;
	//최종 데미지
	float EnemyLastDamage;
	//Hit 데미지
	UPROPERTY(EditAnywhere, Category = "Attack")
	float HitDamage;


	/*******   Montage   ******/

	//공격 애니메이션 몽타주
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* AttackMontage;


public:
	FORCEINLINE EEnemyState GetEnemyState() const { return EnemyState; }

};

