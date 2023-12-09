// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EnemyWeapon/EnemyWeapon.h"
#include "GameInstance/PopolGameInstance.h"
#include "Components/BoxComponent.h"
#include "GameInstance/HitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Character/Controller/PopolPlayerController.h"


/*******   MainSystem   ******/

//Main
AEnemyWeapon::AEnemyWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());

	WeaponBox->SetNotifyRigidBodyCollision(true);
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());

}
//빈 소켓에 장비 장착
void AEnemyWeapon::AttackMeshToSocket(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	EnemyCharacter = Cast<AEnemyCharacter>(NewInstigator);
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	WeaponMesh->AttachToComponent(InParent, TransformRules, InSocketName);
	EnemyCharacter = Cast<AEnemyCharacter>(GetOwner());
}


/*******   System   ******/

//Actor 생성 시 설정
void AEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();


	Tags.Add(FName("EnemyWeapon"));

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyWeapon::OnBoxOverlap);
}


/*******   OverlapSystem   ******/

//박스에 닿았을 경우 반응하는 함수
void AEnemyWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	// 적중 변수 이름
	FHitResult EnemyBoxHit;

	if (OtherActor->ActorHasTag(FName("PlayerCharacter")))
	{
		BoxTrace(EnemyBoxHit);

		UPopolGameInstance* PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		//적의 무기 데이터의 행을 불러오는 것
		EnemyWeaponData = PopolGameInstance->GetEnemyWeaponData(EnemyCharacter->EnemyNum);
		//Enemy 스탯
		EnemyStats = PopolGameInstance->GetEnemyStatsData(EnemyCharacter->EnemyNum);


		float EnemyWeaponDamage = EnemyWeaponData->Damage + EnemyStats->AttackDamage;
		UGameplayStatics::ApplyDamage(EnemyBoxHit.GetActor(), EnemyWeaponDamage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
	}

	IHitInterface* HitInterpace = Cast<IHitInterface>(EnemyBoxHit.GetActor());
	if (HitInterpace)
	{
		HitInterpace->GetHit(EnemyBoxHit.ImpactPoint);
	}
	//중복 불가
	IgnoreActors.AddUnique(EnemyBoxHit.GetActor());
}
//박스 추적
void AEnemyWeapon::BoxTrace(FHitResult& BoxHit)
{
	//선 추격 시작 지점
	const FVector Start = BoxTraceStart->GetComponentLocation();
	//선 추격 끝 지점
	const FVector End = BoxTraceEnd->GetComponentLocation();

	//Actor을 추적해서 무시하는 것
	TArray<AActor*> ActorsTognore;

	ActorsTognore.Add(this); // 무기
	ActorsTognore.Add(GetOwner()); // 플레이어

	//대상 배열 함수의 값을 Actord에 담아 ActorsTognore의 타격 무시 액터로 설정
	for (auto Actor : IgnoreActors)
	{
		//대상을 중복 체크하지 않고 한번만 체크
		ActorsTognore.AddUnique(Actor);
	}
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		TarceHalfSize,
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery2,
		false,
		ActorsTognore,
		EDrawDebugTrace::None,
		BoxHit,
		true
	);
	//중복 불가
	IgnoreActors.AddUnique(BoxHit.GetActor());
}