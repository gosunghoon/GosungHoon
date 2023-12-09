// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "Engine/DataTable.h"
#include "Character/Type/CharacterType.h"
#include "PopolCharacter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterStats()
		: Level(1), HP(50), MaxHP(50), Stamina(50), MaxStamina(50),
		AttackDamage(0), AttackSpped(0), Defense(20),
		EXP(0), MaxEXP(10), Potion()
	{};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxEXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Potion;
};

class UAnimMontage;
class AWeapon;
class APlayerShield;
class UCharacterMainStatWidget;
class UGameExitWidget;

UCLASS()
class POPOL_API APopolCharacter : public AMainCharacter
{
	GENERATED_BODY()

public:
	/*******   MainSystem   ******/

	//Main
	APopolCharacter();
	//PlayerCollback
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Tick
	virtual void Tick(float DeltaTime) override;


	/*******   	Stat  ******/

	struct FWeaponData* CharWeaponData;									//무기 스탯 정보
	struct FShieldData* CharShieldData;									//ShieldStat
	struct FCharacterStats* CharacterStats;							//CharStats


	/*******   Weapon   ******/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AWeapon* Weapon;										//무기 존재 여부 확인
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APlayerShield* Shield;									//방패 존재 여부 확인
	/*******   Item   ******/

	//Drop 활성화 여부
	bool SetbDrop(bool Drop);

protected:
	/*******   	System   ******/

	//시작 시 시스템 설정
	virtual void BeginPlay() override;
	//Move 타입
	virtual void WalkRun();
	//걷기 상태
	virtual bool WalkState();
	//달리기 상태
	virtual bool RunState();
	//레벨 업
	void LevelUp();
	//레벨 업 파티클 생성
	UPROPERTY(EditAnywhere, Category = Palticles)
	UParticleSystem* LevelUPParticles;
	//포션 마시는 파티클 생성
	UPROPERTY(EditAnywhere, Category = Palticles)
	UParticleSystem* PotionParticles;

	/** -----MotionWarping----- */

	//Player - Warp 이동 대상 가져오기
	UFUNCTION(BlueprintCallable)
	void PlayerTransformWarpTarget();

	UPROPERTY(EditAnywhere, Category = MotionWarping)
	class UPlayerMotionWarpingComponent* PlayerMotionWarpingComponent;
	UPROPERTY(EditAnywhere, Category = MotionWarping)
	float FowardDistance = 0.1f;


	/*******   	PlayerCollback   ******/


	//줌 인
	virtual void CameraZoomenlargement();
	//줌 아웃
	virtual void CameraZoomreduction();
	//점프
	virtual void Jump();
	//공격
	virtual void Attack();
	//1번키 누를 시 무기 장착
	virtual void WeaponChange_One();
	//2번키 누를 시 무기 장착
	virtual void WeaponChange_Two();
	//3번키 누를 시 무기 장착
	virtual void WeaponChange_Three();
	//4번키 누를 시 무기 장착
	virtual void WeaponChange_four();
	//방어
	virtual void Block();
	//방어 지속
	virtual void Blocking();
	//방어 종료
	virtual void BlockExit();
	//Move Type
	virtual void MoveType();
	//Drop
	virtual void Drop();
	//대화
	virtual void NPCTok();
	//Potion
	virtual void Potion();
	//앞, 뒤
	virtual void MoveForward(float Value);
	//왼쪽, 오른쪽
	virtual void MoveRight(float Value);
	//마우스 아래, 위
	virtual void Lookup(float Value);
	//마우스 왼쪽, 오른쪽
	virtual void Turn(float Value);



	/*******   	Collision   ******/

	//Shere충돌 반응
	UFUNCTION()
	void OnCharOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Shere충돌 끝 반응
	UFUNCTION()
	void OnCharOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	/*******   	Hit   ******/

	//맞았을 경우
	virtual void GetHit(const FVector& ImpactPoint) override;
	//받는 데미지
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	//Hit끝 변경
	UFUNCTION(BlueprintCallable)
	void HitEnd();
	float PlayerLastDamage;							//플레이어 최종 데미지


	/*******   	Death   ******/

	//죽음
	virtual void Death() override;
	//Player 제거
	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	void RespawnTimer();			//젠 타이머
	void RespawnTimeHasFinished();	//젠 시간 끝
	FTimerHandle RespawnHandle;		//리스폰 타임 핸들
	float RespawnTime = 3.f;		//젠 타임


	/*******   	Widget   ******/

	//스탯 UI
	virtual void UICharacterStat();
	//ESC
	virtual void GameMenu();


	/*******   	Weapon  ******/

	//무기 장착
	virtual void Weapon_Equip(int row);
	//무기 충돌 비활성화
	UFUNCTION(BlueprintCallable)
	virtual void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AWeapon* EquipWeapon;									//무기를 생성하고 장착


	/*******   	Shield  ******/

	//방패 장착 함수
	virtual void Shield_Equip();
	//방패 충돌 비활성화
	UFUNCTION(BlueprintCallable)
	virtual void SetShieldCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	//방패 시작 모션 끝
	UFUNCTION(BlueprintCallable)
	virtual void ShieldBlockStart();
	//방패 모션 끝
	UFUNCTION(BlueprintCallable)
	virtual void ShieldBlockEnd();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class APlayerShield* PlayerShield;							//방패를 생성하고 장착

	bool ShieldBlockingType;	//방패를 들었는지에 대한 여부


	/*******   	AttackSystem  ******/

	//공격 대기 중
	virtual bool ATTACK_WAIT();
	//Attack_A조건
	virtual bool Attack_A();
	//Attack_B조건
	virtual bool Attack_B();
	//Attack_C조건
	virtual bool Attack_C();
	//Attack_D조건
	virtual bool Attack_D();
	//공격 끝
	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();
	//공격 몽타주 1번 끝난 상태
	UFUNCTION(BlueprintCallable)
	virtual void vAttacking_One_End();
	//공격 몽타주 2번 끝난 상태
	UFUNCTION(BlueprintCallable)
	virtual void vAttacking_Two_End();
	//공격 몽타주 3번 끝난 상태
	UFUNCTION(BlueprintCallable)
	virtual void vAttacking_Three_End();

	/*******   	JumpSystem  ******/

	//점프 끝
	UFUNCTION(BlueprintCallable)
	virtual void JumpEnd();

private:


	UPROPERTY(EditAnywhere, Category = Target)
	TSubclassOf<AActor>EnemyCharacter;

	UPROPERTY(EditAnywhere, Category = Target)
	TArray<AActor*> OutActors;

	//UPROPERTY(EditAnywhere, Category = motionWarping)
	//float MotionSpeed;








	/*******   	System  ******/

	UPROPERTY()
	class UPopolGameInstance* PopolGameInstance;	//GameInstance
	UPROPERTY()
	class APopolPlayerState* PopolPlayerState;	//PlayerStats
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;	//PlayerController


	/*******   	Montage  ******/	

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* AttackMontage;									//공격 애니메이션 몽타주
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* JumpMontage;										//점프 애니메이션 몽타주
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ShieldMontage;									//방패 애니메이션 몽타주


	/*******   	Widget  ******/

	UPROPERTY(EditDefaultsOnly, Category = Death)
	TSubclassOf<class UDeathWidget> DeathWidgetClass;
	class UDeathWidget* DeathWidget;								//Death Widget

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCharacterMainStatWidget> CharacterMainStatUIClass;
	UCharacterMainStatWidget* CharacterMainStatWidget;				//Stat Widget

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UGameExitWidget> UGameExitWidgetclass;
	UGameExitWidget* GameExitWidget;								//GameMenu


	class UItemDropWidget* ItemDropWidget;			//Drop Widget
	class UNPCButtonWidget* NPCButtonWidget;		//NPCButtonWidget
	/*******   	Item  ******/

	class AItem* Item;												//Item Class
	bool ItemCollision;			//아이템 충돌 상태
	UPROPERTY(VisibleAnywhere)
	bool bDrop;					//Drop여부



	class ANPC* NPC;	//NPC 확인
	UPROPERTY(VisibleAnywhere)
	bool bNPC;			//NPC충돌 여부
	/*******   	Camera  ******/

	UPROPERTY()
	class USpringArmComponent* BoomCamera;							//카메라 거치대
	UPROPERTY()
	class UCameraComponent* ViewCamera;									//카메라
	UPROPERTY()
	float CameraZoom = 50.f;										//카메라 줌 속도
	UPROPERTY()
	float CaceraZoomMax = 700.f;									//카메라 줌 최대치
	UPROPERTY()
	float CameraZoomMin = 50.f;										//카메라 줌 최소치


	/*******   	Move  ******/

	UPROPERTY()
	float MoveWalk = 100.f;											//걷는 속도
	UPROPERTY()
	float MoveRun = 500.f;											//달리는 속도


	/*******   	Shield  ******/

	UPROPERTY(EditAnywhere, Category = "Shield Porperties")
	class USphereComponent* CharSphere;								//Sphere Collision
	UPROPERTY()
	float StaminaDown;												//스태미너 감소량
	UPROPERTY(VisibleAnywhere)
	float GuardDownTime;											//방패 내린 시간


	/*******   	Weapon  ******/

	UPROPERTY()
	int WeaponRow;													//무기 Number


	/*******   	EnumType  ******/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAttackingType AttackingType = EAttackingType::EAK_ATTACK_WAIT;							//공격 몽타주 실행중 상태 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAttackingEndType AttackingEndType;														//공격 몽타주 끝난 상태 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterMoveType CharacterMoveType = ECharacterMoveType::ECM_Run;						//움직임 상태 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterAttackType CharacterAttackType;												//공격 몽타주 상태 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EWeaponEnable WeaponType;																//무기 장착 상태 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EShieldEnable ShieldType;																//방패 장착 상태 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EBlockingType BlockingType;																//방어하는 중 상태 여부
public:
	FORCEINLINE ECharacterMoveType GetCharacterMoveType() const { return CharacterMoveType; }
	FORCEINLINE ECharacterAttackType GetCharacterAttackType() const { return CharacterAttackType; }
	FORCEINLINE EAttackingType GetAttackingType() const { return AttackingType; }
	FORCEINLINE EAttackingEndType GetAttackingEndType() const { return AttackingEndType; }
};