// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacter.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Character/Type/CharacterType.h"
#include "Perception/PawnSensingComponent.h"
#include "GameInstance/PopolGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Item/EnemyWeapon/EnemyWeapon.h"
#include "Widget/EnemyHealthBar/HealthBar.h"
#include "Widget/EnemyHealthBar/HealthBarComponent.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Character/PopolCharacter.h"
#include "Widget/CharacterMainWidget/PlayerWidget.h"
#include "Components/BoxComponent.h"
#include "Widget/TakeDamageWidgetComponent.h"
#include "Widget/TakeDamageWidget.h"
#include "Engine/TargetPoint.h"
#include "GameMode/PoPolGameMode.h"
#include "MotionWarping/EnemyMotionWarpingComponent.h"
#include "Enemy/Target/TargetPointActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

/*******   MainSystem   ******/

//Main
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//�ݸ��� ����
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	//��Ʈ�ѷ�
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//ü�� ��
	HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarComponent->SetupAttachment(GetRootComponent());

	TakeDamageWidgetComponent = CreateDefaultSubobject<UTakeDamageWidgetComponent>(TEXT("TakeDamage"));
	TakeDamageWidgetComponent->SetupAttachment(GetRootComponent());

	//���� ����
	Sensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing"));
	Sensing->SightRadius = 1500.f;
	Sensing->SetPeripheralVisionAngle(35.f);

	EnemyMotionWarpingComponent = CreateDefaultSubobject<UEnemyMotionWarpingComponent>(TEXT("EnemyMotionWarping"));

	//�⺻ ����
	EnemyState = EEnemyState::EES_PATROLLING;
	EnemyAttackState = EEnemyAttackState::EEAS_NOATTACKING;
	//��� ���� ��� ����
	DoubleWeapon = false;

	PatrolTime = 6.f;
}
//Tick
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�߰�, ���� ����
	if (EnemyState != EEnemyState::EES_PATROLLING)
	{
		//���� ����
		if (EnemyState == EEnemyState::EES_DEATH) return;
		CheckCombatTarget();
	}
}


/*******   PlayerSystem   ******/

//����ġ
float AEnemyCharacter::GetEXP()
{
	return EnemyStats->EXP;
	UE_LOG(LogTemp, Log, TEXT("GetEXP"));
}
//���
int32 AEnemyCharacter::GetGold()
{
	return EnemyStats->Gold;
	UE_LOG(LogTemp, Log, TEXT("GetGold"));
}


/*******   System   ******/


//���� �� System����
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//�±�
	Tags.Add(FName("Enemy"));
	//�ִϸ��̼�
	AnimInstance = GetMesh()->GetAnimInstance();
	//AI��Ʈ�ѷ�
	EnemyAIController = Cast<AAIController>(GetController());
	//���� ���
	gameMode = Cast<APoPolGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//���� �ν��Ͻ�
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//Enemy ����
	EnemyStats = PopolGameInstance->GetEnemyStatsData(EnemyNum);
	//Enemy Start HP
	EnemyStats->HP = EnemyStats->MaxHP;
	//���� ����
	SpawnDefaultWeapon();
	//���� ����
	if (Sensing) Sensing->OnSeePawn.AddDynamic(this, &AEnemyCharacter::PawnSeen);

	//ü�� ǥ��
	HealthBar();

	HealthBarComponent->SetVisibility(false);
	TakeDamageWidgetComponent->SetVisibility(false);

	//���� �� ����
	StartPatrolling();
}
//Ÿ�� �̵�
void AEnemyCharacter::MoveToTarget(AActor* Target)
{
	//AI�̵� ����
	FAIMoveRequest MoveRequest;
	//���
	MoveRequest.SetGoalActor(Target);
	//�߰� ��� ����
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	//��� �߰�
	EnemyAIController->MoveTo(MoveRequest);
}
//Target ����
bool AEnemyCharacter::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;

	//Target�Ÿ� ���
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	//Target ����
	return DistanceToTarget <= Radius;
}
//�� ü�º���
float AEnemyCharacter::GetEnemyHealthpercent()
{
	return EnemyStats->HP / EnemyStats->MaxHP;
}
//�� ��������
bool AEnemyCharacter::EnemyIsAlive()
{
	return EnemyStats->HP > 0.f;
}



/*******   Widget   ******/

void AEnemyCharacter::EnemyTransformWarpTarget()
{
	UE_LOG(LogTemp, Log, TEXT("CombatTarget->GetActorLocation() : %s"), *CombatTarget->GetActorLocation().ToString());
	const FVector CombatTargetLocatoin = CombatTarget->GetActorLocation();
	const FVector Lociaton = GetActorLocation();

	FVector TargetToMe = (CombatTargetLocatoin - Lociaton).GetSafeNormal();

	const FRotator CombatTargetRocatoin = CombatTarget->GetActorRotation();

	EnemyMotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("CombatTarget"), TargetToMe, CombatTargetRocatoin);
}

//ü�� Widget
void AEnemyCharacter::HealthBar()
{
	if (HealthBarComponent)
	{
		//HP �ۼ�Ʈ
		HealthBarComponent->SetHealthPercent(EnemyStats->HP / EnemyStats->MaxHP);
		//HP �ؽ�Ʈ
		HealthBarComponent->SetHealthText(EnemyStats->HP, EnemyStats->MaxHP, EnemyStats->Name);
	}
}
//HP ���� ������Ʈ
void AEnemyCharacter::InitHealthBar()
{
	//ü�� ����
	EnemyReceiveDamage(EnemyLastDamage);
	//ü�� �ۼ�Ʈ �� �ؽ�Ʈ �缳��
	HealthBar();
}
//�޴� ������ ���� �ʱ�ȭ
void AEnemyCharacter::InitTakeDamageText()
{
	TakeDamageWidgetComponent->SetVisibility(false);
}


/*******   Hit   ******/

//�¾��� ���
void AEnemyCharacter::GetHit(const FVector& ImpactPoint)
{
	Super::GetHit(ImpactPoint);

	if (EnemyState == EEnemyState::EES_DEATH) return;

	//Hit �� ü�� �� ����
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(true);
	}

	//�������� XX�̻��� ��� Ÿ�� ��Ÿ��
	if (EnemyLastDamage >= HitDamage)
	{

		if (EnemyIsAlive()) //ü�� 0�̻��̸� �ǰ�
		{
			//�ǰ� ���⿡ ���� �ǰ� ��Ÿ�� ����
			DirectionalHitReact(ImpactPoint);
		}
	}
}
//�޴� ������
float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,AActor* DamageCauser)
{
	EnemyTakeDamage = LastDamage(DamageAmount);	//�޴� ������
	CombatTarget = EventInstigator->GetPawn();			
	if (CombatTarget) CheckCombatTarget();				//Ÿ�� �� ��� �߰�	
	InitHealthBar();									//ü�� �� �缳��
	EnemyPlayerRotator();
	//TakeDamageWidget
	TakeDamageWidgetComponent->SetTakeDamageText(EnemyTakeDamage);
	TakeDamageWidgetComponent->SetVisibility(true);
	GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &AEnemyCharacter::InitTakeDamageText, 1.0f, true);
	PopolPlayerController = Cast<APopolPlayerController>(EventInstigator);	//Ÿ�� ��� ��Ʈ�ѷ�
	if (EnemyIsDead())
	{
		Death();	//���
	}
	return EnemyTakeDamage;
}
void AEnemyCharacter::EnemyPlayerRotator()
{
	FVector ToTarget = CombatTarget->GetActorLocation() - GetActorLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	SetActorRotation(LookAtRotation);
}
//�ǰ��� �� ü��
void AEnemyCharacter::EnemyReceiveDamage(float Damage)
{
	EnemyStats->HP = FMath::Clamp(EnemyStats->HP - Damage, 0.f, EnemyStats->MaxHP);
}
//������ ���
float AEnemyCharacter::LastDamage(float DamageAmount)
{
	return EnemyLastDamage = Damage(DamageAmount, EnemyStats->defense);
}
//Hit ��
void AEnemyCharacter::HitEnd()
{
	EnemyAttackState = EEnemyAttackState::EEAS_NOATTACKING;
	EnemyState = EEnemyState::EES_PATROLLING;
}


/*******   Death   ******/

//���
void AEnemyCharacter::Death()
{
	Super::Death();

	//��� ����
	EnemyState = EEnemyState::EES_DEATH;
	if (HealthBarComponent)
	{	//ü�¹� ����
		HealthBarComponent->SetVisibility(false);
	}
	if (PopolPlayerController)
	{
		PopolPlayerController->EnemyKillEXP(this);
		PopolPlayerController->EnemyKillGold(this);
	}
	//��� ���� ����
	if (DoubleWeapon == true)
	{
		DefaultWeapon_Two->Destroy();
	}
	if (EnemyWeaponData)
	{
		DefaultWeapon->Destroy();
	}
}
//��ü ����
void AEnemyCharacter::DeathEnd()
{
	SetLifeSpan(DeathTime);
	EnemyAttackState = EEnemyAttackState::EEAS_NOATTACKING;
	EnemyState = EEnemyState::EES_PATROLLING;
} 
bool AEnemyCharacter::EnemyIsDead()
{
	return EnemyStats->HP <= 0.f;
}

/*******   EnemyWeapon   ******/

//Weapon
//���� ����
void AEnemyCharacter::SpawnDefaultWeapon()
{
	//���� ������ �� = ���� ������ ��
	EnemyWeaponData = PopolGameInstance->GetEnemyWeaponData(EnemyNum);
	//�ش� ���� �Ҽӵ� ���带 �ҷ����ش�.
	UWorld* World = GetWorld();
	if (World && EnemyWeaponData)
	{
		//��� ���� ����
		if (DoubleWeapon == true)
		{
			//��� ���� ����
			EnemyWeaponData = PopolGameInstance->GetEnemyWeaponData(EnemyNum * 11);
			DefaultWeapon_Two = World->SpawnActor<AEnemyWeapon>(EnemyWeaponData->WeaponClass);
			DefaultWeapon_Two->AttackMeshToSocket(GetMesh(), FName("WeaponSocketTwo"), this, this);
		}
		//���� ����
		DefaultWeapon = World->SpawnActor<AEnemyWeapon>(EnemyWeaponData->WeaponClass);
		DefaultWeapon->AttackMeshToSocket(GetMesh(), FName("WeaponSocket"), this, this);
	}
}
//���� �浹 Ȱ��ȭ
void AEnemyCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	//���� ���� ���� Ȯ��
	if (DefaultWeapon && DefaultWeapon->GetWeaponBox())
	{
		//��� ���� ���� ���� Ȯ��
		if (DefaultWeapon_Two && DefaultWeapon_Two->GetWeaponBox())
		{
			//Coliision ���� �� ����
			DefaultWeapon_Two->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
			DefaultWeapon_Two->IgnoreActors.Empty();
		}
		//Coliision ���� �� ����
		DefaultWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		DefaultWeapon->IgnoreActors.Empty();
	}
}


/*******   EnemyPatrol   ******/

//���� ����
void AEnemyCharacter::StartPatrolling()
{
	if (EnemyAttackState == EEnemyAttackState::EEAS_ATTACKING) return;

	//ü�� �� ����
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(false);
	}
	EnemyState = EEnemyState::EES_PATROLLING;	//����
	MoveSpeed(EnemyStats->WalkSpeed);			//�ӵ�
}


/*******   EnemyChase   ******/

//���� ���� �߰�
void AEnemyCharacter::PawnSeen(APawn* SeenPawn)
{
	//����� �±װ� PlayerCharacter�� ��� �߰�
	if (SeenPawn->ActorHasTag(FName("PlayerCharacter")))
	{
		CombatTarget = SeenPawn;	//Ÿ�� ����
		EnemyPlayerRotator();
		ChaseTarget();				//�߰�
	}
}
//�߰� ����
void AEnemyCharacter::ChaseTarget()
{
	//���� �� �߰� ����
	if (EnemyAttackState != EEnemyAttackState::EEAS_ATTACKING)
	{
		if (HealthBarComponent)
		{
			HealthBarComponent->SetVisibility(true);
		}
		EnemyState = EEnemyState::EES_CHASING;	//�߰� ����
		MoveSpeed(EnemyStats->RunSpeed);		//�ӵ�
		MoveToTarget(CombatTarget);				//���
	}
}


/*******   Combat   ******/

//���� ��� Ȯ��
void AEnemyCharacter::CheckCombatTarget()
{
	//�׾��� ��� Ȯ�� ���ʿ�
	if (EnemyState == EEnemyState::EES_DEATH) return;

	if (!InTargetRange(CombatTarget, CombatRadius)) //���� ����� ���� �ȿ� ���ٸ�
	{
		if (HealthBarComponent)
		{
			HealthBarComponent->SetVisibility(false);
		}
		EnemyState = EEnemyState::EES_PATROLLING;
		ClearAttackTimer();
		CombatTarget = nullptr;
		StartPatrolling();
	}
	else if (!(InTargetRange(CombatTarget, AttackRadius)) && EnemyState != EEnemyState::EES_CHASING) //���� ����� ���� �ݰ濡 ���ٸ�
	{
		EnemyState = EEnemyState::EES_CHASING;
		if (EnemyAttackState == EEnemyAttackState::EEAS_ATTACKING) return;
		ClearAttackTimer();
		ChaseTarget();
	}
	else if (InTargetRange(CombatTarget, AttackRadius) && EnemyAttackState != EEnemyAttackState::EEAS_ATTACKING) //���� ����� ���� �ݰ濡 �ִٸ�
	{
		EnemyAttackState = EEnemyAttackState::EEAS_ATTACKING;
		StartAttackTimer();
	}
}



/*******   EnemyAttack   ******/

//����
void AEnemyCharacter::Attack()
{
	Super::Attack();
	//���� ����
	if (EnemyState == EEnemyState::EES_DEATH || CombatTarget == nullptr) return;
	ClearAttackTimer();
	//���� ��� 3���� ���� ���� �Ͽ� ����
	const int SectionMax = TArraySection.Num() - 1; //
	const int SectionName = FMath::RandRange(0, SectionMax);
	PlayMontage(AttackMontage, TArraySection[SectionName]);

}
//���� �ð� ��
void AEnemyCharacter::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
}
//���� ��
void AEnemyCharacter::AttackEnd()
{
	EnemyAttackState = EEnemyAttackState::EEAS_NOATTACKING;
	//EnemyState = EEnemyState::EES_CHASING;
}
//���� ��� �ð�
void AEnemyCharacter::StartAttackTimer()
{
	//���� ����
	if (EnemyState == EEnemyState::EES_DEATH) return;

	//�ٽ� ����
	EnemyAttackState = EEnemyAttackState::EEAS_ATTACKING;
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyCharacter::Attack, EnemyStats->AttackSpped);
}