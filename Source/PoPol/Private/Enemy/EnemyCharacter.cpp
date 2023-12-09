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

	//콜리전 상태
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	//컨트롤러
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//체력 바
	HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarComponent->SetupAttachment(GetRootComponent());

	TakeDamageWidgetComponent = CreateDefaultSubobject<UTakeDamageWidgetComponent>(TEXT("TakeDamage"));
	TakeDamageWidgetComponent->SetupAttachment(GetRootComponent());

	//센서 설정
	Sensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing"));
	Sensing->SightRadius = 1500.f;
	Sensing->SetPeripheralVisionAngle(35.f);

	EnemyMotionWarpingComponent = CreateDefaultSubobject<UEnemyMotionWarpingComponent>(TEXT("EnemyMotionWarping"));

	//기본 상태
	EnemyState = EEnemyState::EES_PATROLLING;
	EnemyAttackState = EEnemyAttackState::EEAS_NOATTACKING;
	//듀얼 웨폰 사용 여부
	DoubleWeapon = false;

	PatrolTime = 6.f;
}
//Tick
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//추격, 순찰 상태
	if (EnemyState != EEnemyState::EES_PATROLLING)
	{
		//공격 정지
		if (EnemyState == EEnemyState::EES_DEATH) return;
		CheckCombatTarget();
	}
}


/*******   PlayerSystem   ******/

//경험치
float AEnemyCharacter::GetEXP()
{
	return EnemyStats->EXP;
	UE_LOG(LogTemp, Log, TEXT("GetEXP"));
}
//골드
int32 AEnemyCharacter::GetGold()
{
	return EnemyStats->Gold;
	UE_LOG(LogTemp, Log, TEXT("GetGold"));
}


/*******   System   ******/


//시작 시 System설정
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//태그
	Tags.Add(FName("Enemy"));
	//애니메이션
	AnimInstance = GetMesh()->GetAnimInstance();
	//AI컨트롤러
	EnemyAIController = Cast<AAIController>(GetController());
	//게임 모드
	gameMode = Cast<APoPolGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//게임 인스턴스
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//Enemy 스탯
	EnemyStats = PopolGameInstance->GetEnemyStatsData(EnemyNum);
	//Enemy Start HP
	EnemyStats->HP = EnemyStats->MaxHP;
	//무기 장착
	SpawnDefaultWeapon();
	//센서 반응
	if (Sensing) Sensing->OnSeePawn.AddDynamic(this, &AEnemyCharacter::PawnSeen);

	//체력 표시
	HealthBar();

	HealthBarComponent->SetVisibility(false);
	TakeDamageWidgetComponent->SetVisibility(false);

	//시작 시 순찰
	StartPatrolling();
}
//타겟 이동
void AEnemyCharacter::MoveToTarget(AActor* Target)
{
	//AI이동 변수
	FAIMoveRequest MoveRequest;
	//대상
	MoveRequest.SetGoalActor(Target);
	//추격 대상 범위
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	//대상 추격
	EnemyAIController->MoveTo(MoveRequest);
}
//Target 범위
bool AEnemyCharacter::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;

	//Target거리 계산
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	//Target 범위
	return DistanceToTarget <= Radius;
}
//적 체력비율
float AEnemyCharacter::GetEnemyHealthpercent()
{
	return EnemyStats->HP / EnemyStats->MaxHP;
}
//적 생존여부
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

//체력 Widget
void AEnemyCharacter::HealthBar()
{
	if (HealthBarComponent)
	{
		//HP 퍼센트
		HealthBarComponent->SetHealthPercent(EnemyStats->HP / EnemyStats->MaxHP);
		//HP 텍스트
		HealthBarComponent->SetHealthText(EnemyStats->HP, EnemyStats->MaxHP, EnemyStats->Name);
	}
}
//HP 감소 업데이트
void AEnemyCharacter::InitHealthBar()
{
	//체력 감소
	EnemyReceiveDamage(EnemyLastDamage);
	//체력 퍼센트 및 텍스트 재설정
	HealthBar();
}
//받는 데미지 상태 초기화
void AEnemyCharacter::InitTakeDamageText()
{
	TakeDamageWidgetComponent->SetVisibility(false);
}


/*******   Hit   ******/

//맞았을 경우
void AEnemyCharacter::GetHit(const FVector& ImpactPoint)
{
	Super::GetHit(ImpactPoint);

	if (EnemyState == EEnemyState::EES_DEATH) return;

	//Hit 시 체력 바 여부
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(true);
	}

	//데미지가 XX이상일 경우 타격 몽타주
	if (EnemyLastDamage >= HitDamage)
	{

		if (EnemyIsAlive()) //체력 0이상이면 피격
		{
			//피격 방향에 따른 피격 몽타주 실행
			DirectionalHitReact(ImpactPoint);
		}
	}
}
//받는 데미지
float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,AActor* DamageCauser)
{
	EnemyTakeDamage = LastDamage(DamageAmount);	//받는 데미지
	CombatTarget = EventInstigator->GetPawn();			
	if (CombatTarget) CheckCombatTarget();				//타격 시 대상 추격	
	InitHealthBar();									//체력 바 재설정
	EnemyPlayerRotator();
	//TakeDamageWidget
	TakeDamageWidgetComponent->SetTakeDamageText(EnemyTakeDamage);
	TakeDamageWidgetComponent->SetVisibility(true);
	GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &AEnemyCharacter::InitTakeDamageText, 1.0f, true);
	PopolPlayerController = Cast<APopolPlayerController>(EventInstigator);	//타격 대상 컨트롤러
	if (EnemyIsDead())
	{
		Death();	//사망
	}
	return EnemyTakeDamage;
}
void AEnemyCharacter::EnemyPlayerRotator()
{
	FVector ToTarget = CombatTarget->GetActorLocation() - GetActorLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	SetActorRotation(LookAtRotation);
}
//피격후 적 체력
void AEnemyCharacter::EnemyReceiveDamage(float Damage)
{
	EnemyStats->HP = FMath::Clamp(EnemyStats->HP - Damage, 0.f, EnemyStats->MaxHP);
}
//데미지 계산
float AEnemyCharacter::LastDamage(float DamageAmount)
{
	return EnemyLastDamage = Damage(DamageAmount, EnemyStats->defense);
}
//Hit 끝
void AEnemyCharacter::HitEnd()
{
	EnemyAttackState = EEnemyAttackState::EEAS_NOATTACKING;
	EnemyState = EEnemyState::EES_PATROLLING;
}


/*******   Death   ******/

//사망
void AEnemyCharacter::Death()
{
	Super::Death();

	//사망 상태
	EnemyState = EEnemyState::EES_DEATH;
	if (HealthBarComponent)
	{	//체력바 숨김
		HealthBarComponent->SetVisibility(false);
	}
	if (PopolPlayerController)
	{
		PopolPlayerController->EnemyKillEXP(this);
		PopolPlayerController->EnemyKillGold(this);
	}
	//듀얼 웨폰 여부
	if (DoubleWeapon == true)
	{
		DefaultWeapon_Two->Destroy();
	}
	if (EnemyWeaponData)
	{
		DefaultWeapon->Destroy();
	}
}
//시체 제거
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
//무기 생성
void AEnemyCharacter::SpawnDefaultWeapon()
{
	//무기 데이터 행 = 몬스터 데이터 행
	EnemyWeaponData = PopolGameInstance->GetEnemyWeaponData(EnemyNum);
	//해당 적이 소속된 월드를 불러와준다.
	UWorld* World = GetWorld();
	if (World && EnemyWeaponData)
	{
		//듀얼 웨폰 여부
		if (DoubleWeapon == true)
		{
			//듀얼 무기 장착
			EnemyWeaponData = PopolGameInstance->GetEnemyWeaponData(EnemyNum * 11);
			DefaultWeapon_Two = World->SpawnActor<AEnemyWeapon>(EnemyWeaponData->WeaponClass);
			DefaultWeapon_Two->AttackMeshToSocket(GetMesh(), FName("WeaponSocketTwo"), this, this);
		}
		//무기 장착
		DefaultWeapon = World->SpawnActor<AEnemyWeapon>(EnemyWeaponData->WeaponClass);
		DefaultWeapon->AttackMeshToSocket(GetMesh(), FName("WeaponSocket"), this, this);
	}
}
//무기 충돌 활성화
void AEnemyCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	//무기 장착 상태 확인
	if (DefaultWeapon && DefaultWeapon->GetWeaponBox())
	{
		//듀얼 무기 장착 상태 확인
		if (DefaultWeapon_Two && DefaultWeapon_Two->GetWeaponBox())
		{
			//Coliision 상태 재 설정
			DefaultWeapon_Two->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
			DefaultWeapon_Two->IgnoreActors.Empty();
		}
		//Coliision 상태 재 설정
		DefaultWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		DefaultWeapon->IgnoreActors.Empty();
	}
}


/*******   EnemyPatrol   ******/

//순찰 시작
void AEnemyCharacter::StartPatrolling()
{
	if (EnemyAttackState == EEnemyAttackState::EEAS_ATTACKING) return;

	//체력 바 여부
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(false);
	}
	EnemyState = EEnemyState::EES_PATROLLING;	//상태
	MoveSpeed(EnemyStats->WalkSpeed);			//속도
}


/*******   EnemyChase   ******/

//센서 반응 추격
void AEnemyCharacter::PawnSeen(APawn* SeenPawn)
{
	//대상의 태그가 PlayerCharacter일 경우 추격
	if (SeenPawn->ActorHasTag(FName("PlayerCharacter")))
	{
		CombatTarget = SeenPawn;	//타겟 지정
		EnemyPlayerRotator();
		ChaseTarget();				//추격
	}
}
//추격 시작
void AEnemyCharacter::ChaseTarget()
{
	//공격 시 추격 정지
	if (EnemyAttackState != EEnemyAttackState::EEAS_ATTACKING)
	{
		if (HealthBarComponent)
		{
			HealthBarComponent->SetVisibility(true);
		}
		EnemyState = EEnemyState::EES_CHASING;	//추격 상태
		MoveSpeed(EnemyStats->RunSpeed);		//속도
		MoveToTarget(CombatTarget);				//대상
	}
}


/*******   Combat   ******/

//전투 대상 확인
void AEnemyCharacter::CheckCombatTarget()
{
	//죽었을 경우 확인 불필요
	if (EnemyState == EEnemyState::EES_DEATH) return;

	if (!InTargetRange(CombatTarget, CombatRadius)) //전투 대상이 범위 안에 없다면
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
	else if (!(InTargetRange(CombatTarget, AttackRadius)) && EnemyState != EEnemyState::EES_CHASING) //전투 대상이 공격 반경에 없다면
	{
		EnemyState = EEnemyState::EES_CHASING;
		if (EnemyAttackState == EEnemyAttackState::EEAS_ATTACKING) return;
		ClearAttackTimer();
		ChaseTarget();
	}
	else if (InTargetRange(CombatTarget, AttackRadius) && EnemyAttackState != EEnemyAttackState::EEAS_ATTACKING) //전투 대상이 공격 반경에 있다면
	{
		EnemyAttackState = EEnemyAttackState::EEAS_ATTACKING;
		StartAttackTimer();
	}
}



/*******   EnemyAttack   ******/

//공격
void AEnemyCharacter::Attack()
{
	Super::Attack();
	//공격 정지
	if (EnemyState == EEnemyState::EES_DEATH || CombatTarget == nullptr) return;
	ClearAttackTimer();
	//공격 모션 3개중 랜덤 지정 하여 실행
	const int SectionMax = TArraySection.Num() - 1; //
	const int SectionName = FMath::RandRange(0, SectionMax);
	PlayMontage(AttackMontage, TArraySection[SectionName]);

}
//공격 시간 끝
void AEnemyCharacter::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
}
//공격 끝
void AEnemyCharacter::AttackEnd()
{
	EnemyAttackState = EEnemyAttackState::EEAS_NOATTACKING;
	//EnemyState = EEnemyState::EES_CHASING;
}
//공격 대기 시간
void AEnemyCharacter::StartAttackTimer()
{
	//공격 정지
	if (EnemyState == EEnemyState::EES_DEATH) return;

	//다시 공격
	EnemyAttackState = EEnemyAttackState::EEAS_ATTACKING;
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyCharacter::Attack, EnemyStats->AttackSpped);
}