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

	struct FWeaponData* CharWeaponData;									//���� ���� ����
	struct FShieldData* CharShieldData;									//ShieldStat
	struct FCharacterStats* CharacterStats;							//CharStats


	/*******   Weapon   ******/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AWeapon* Weapon;										//���� ���� ���� Ȯ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APlayerShield* Shield;									//���� ���� ���� Ȯ��
	/*******   Item   ******/

	//Drop Ȱ��ȭ ����
	bool SetbDrop(bool Drop);

protected:
	/*******   	System   ******/

	//���� �� �ý��� ����
	virtual void BeginPlay() override;
	//Move Ÿ��
	virtual void WalkRun();
	//�ȱ� ����
	virtual bool WalkState();
	//�޸��� ����
	virtual bool RunState();
	//���� ��
	void LevelUp();
	//���� �� ��ƼŬ ����
	UPROPERTY(EditAnywhere, Category = Palticles)
	UParticleSystem* LevelUPParticles;
	//���� ���ô� ��ƼŬ ����
	UPROPERTY(EditAnywhere, Category = Palticles)
	UParticleSystem* PotionParticles;

	/** -----MotionWarping----- */

	//Player - Warp �̵� ��� ��������
	UFUNCTION(BlueprintCallable)
	void PlayerTransformWarpTarget();

	UPROPERTY(EditAnywhere, Category = MotionWarping)
	class UPlayerMotionWarpingComponent* PlayerMotionWarpingComponent;
	UPROPERTY(EditAnywhere, Category = MotionWarping)
	float FowardDistance = 0.1f;


	/*******   	PlayerCollback   ******/


	//�� ��
	virtual void CameraZoomenlargement();
	//�� �ƿ�
	virtual void CameraZoomreduction();
	//����
	virtual void Jump();
	//����
	virtual void Attack();
	//1��Ű ���� �� ���� ����
	virtual void WeaponChange_One();
	//2��Ű ���� �� ���� ����
	virtual void WeaponChange_Two();
	//3��Ű ���� �� ���� ����
	virtual void WeaponChange_Three();
	//4��Ű ���� �� ���� ����
	virtual void WeaponChange_four();
	//���
	virtual void Block();
	//��� ����
	virtual void Blocking();
	//��� ����
	virtual void BlockExit();
	//Move Type
	virtual void MoveType();
	//Drop
	virtual void Drop();
	//��ȭ
	virtual void NPCTok();
	//Potion
	virtual void Potion();
	//��, ��
	virtual void MoveForward(float Value);
	//����, ������
	virtual void MoveRight(float Value);
	//���콺 �Ʒ�, ��
	virtual void Lookup(float Value);
	//���콺 ����, ������
	virtual void Turn(float Value);



	/*******   	Collision   ******/

	//Shere�浹 ����
	UFUNCTION()
	void OnCharOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Shere�浹 �� ����
	UFUNCTION()
	void OnCharOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	/*******   	Hit   ******/

	//�¾��� ���
	virtual void GetHit(const FVector& ImpactPoint) override;
	//�޴� ������
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	//Hit�� ����
	UFUNCTION(BlueprintCallable)
	void HitEnd();
	float PlayerLastDamage;							//�÷��̾� ���� ������


	/*******   	Death   ******/

	//����
	virtual void Death() override;
	//Player ����
	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	void RespawnTimer();			//�� Ÿ�̸�
	void RespawnTimeHasFinished();	//�� �ð� ��
	FTimerHandle RespawnHandle;		//������ Ÿ�� �ڵ�
	float RespawnTime = 3.f;		//�� Ÿ��


	/*******   	Widget   ******/

	//���� UI
	virtual void UICharacterStat();
	//ESC
	virtual void GameMenu();


	/*******   	Weapon  ******/

	//���� ����
	virtual void Weapon_Equip(int row);
	//���� �浹 ��Ȱ��ȭ
	UFUNCTION(BlueprintCallable)
	virtual void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AWeapon* EquipWeapon;									//���⸦ �����ϰ� ����


	/*******   	Shield  ******/

	//���� ���� �Լ�
	virtual void Shield_Equip();
	//���� �浹 ��Ȱ��ȭ
	UFUNCTION(BlueprintCallable)
	virtual void SetShieldCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	//���� ���� ��� ��
	UFUNCTION(BlueprintCallable)
	virtual void ShieldBlockStart();
	//���� ��� ��
	UFUNCTION(BlueprintCallable)
	virtual void ShieldBlockEnd();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class APlayerShield* PlayerShield;							//���и� �����ϰ� ����

	bool ShieldBlockingType;	//���и� ��������� ���� ����


	/*******   	AttackSystem  ******/

	//���� ��� ��
	virtual bool ATTACK_WAIT();
	//Attack_A����
	virtual bool Attack_A();
	//Attack_B����
	virtual bool Attack_B();
	//Attack_C����
	virtual bool Attack_C();
	//Attack_D����
	virtual bool Attack_D();
	//���� ��
	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();
	//���� ��Ÿ�� 1�� ���� ����
	UFUNCTION(BlueprintCallable)
	virtual void vAttacking_One_End();
	//���� ��Ÿ�� 2�� ���� ����
	UFUNCTION(BlueprintCallable)
	virtual void vAttacking_Two_End();
	//���� ��Ÿ�� 3�� ���� ����
	UFUNCTION(BlueprintCallable)
	virtual void vAttacking_Three_End();

	/*******   	JumpSystem  ******/

	//���� ��
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
	UAnimMontage* AttackMontage;									//���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* JumpMontage;										//���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ShieldMontage;									//���� �ִϸ��̼� ��Ÿ��


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
	bool ItemCollision;			//������ �浹 ����
	UPROPERTY(VisibleAnywhere)
	bool bDrop;					//Drop����



	class ANPC* NPC;	//NPC Ȯ��
	UPROPERTY(VisibleAnywhere)
	bool bNPC;			//NPC�浹 ����
	/*******   	Camera  ******/

	UPROPERTY()
	class USpringArmComponent* BoomCamera;							//ī�޶� ��ġ��
	UPROPERTY()
	class UCameraComponent* ViewCamera;									//ī�޶�
	UPROPERTY()
	float CameraZoom = 50.f;										//ī�޶� �� �ӵ�
	UPROPERTY()
	float CaceraZoomMax = 700.f;									//ī�޶� �� �ִ�ġ
	UPROPERTY()
	float CameraZoomMin = 50.f;										//ī�޶� �� �ּ�ġ


	/*******   	Move  ******/

	UPROPERTY()
	float MoveWalk = 100.f;											//�ȴ� �ӵ�
	UPROPERTY()
	float MoveRun = 500.f;											//�޸��� �ӵ�


	/*******   	Shield  ******/

	UPROPERTY(EditAnywhere, Category = "Shield Porperties")
	class USphereComponent* CharSphere;								//Sphere Collision
	UPROPERTY()
	float StaminaDown;												//���¹̳� ���ҷ�
	UPROPERTY(VisibleAnywhere)
	float GuardDownTime;											//���� ���� �ð�


	/*******   	Weapon  ******/

	UPROPERTY()
	int WeaponRow;													//���� Number


	/*******   	EnumType  ******/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAttackingType AttackingType = EAttackingType::EAK_ATTACK_WAIT;							//���� ��Ÿ�� ������ ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAttackingEndType AttackingEndType;														//���� ��Ÿ�� ���� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterMoveType CharacterMoveType = ECharacterMoveType::ECM_Run;						//������ ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterAttackType CharacterAttackType;												//���� ��Ÿ�� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EWeaponEnable WeaponType;																//���� ���� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EShieldEnable ShieldType;																//���� ���� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EBlockingType BlockingType;																//����ϴ� �� ���� ����
public:
	FORCEINLINE ECharacterMoveType GetCharacterMoveType() const { return CharacterMoveType; }
	FORCEINLINE ECharacterAttackType GetCharacterAttackType() const { return CharacterAttackType; }
	FORCEINLINE EAttackingType GetAttackingType() const { return AttackingType; }
	FORCEINLINE EAttackingEndType GetAttackingEndType() const { return AttackingEndType; }
};