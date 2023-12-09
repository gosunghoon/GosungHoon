// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PlayerShield/PlayerShield.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/PopolGameInstance.h"
#include "Character/PopolCharacter.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Components/BoxComponent.h"


/*******   MainSystem   ******/

//Main
APlayerShield::APlayerShield()
{
	//메시를 생성 후 콜리전 설정
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	ShieldMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ShieldMesh;

	//구체 콤포넌트을 생성 후 콜리전 설정
	ShieldBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	ShieldBox->SetupAttachment(GetRootComponent());
	ShieldBox->SetNotifyRigidBodyCollision(true);
	ShieldBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShieldBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	//구체 콜리전 반응 시작지점
	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("SphereTraceStart"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	//구체 콜리전 반응 끝 지점
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("SphereTraceEnd"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}


/*******   Equip   ******/

//빈 소켓에 장비 장착
void APlayerShield::AttackMeshToSocket(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	//플레이어의 컨트롤러를 PopolPlayerController로 변경해준다.
	ItemState = EItemState::EIS_Equipped;
	PopolPlayerController = Cast<APopolPlayerController>(NewInstigator->GetController());
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ShieldMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}


/*******   System   ******/

//Actor 생성 시 설정
void APlayerShield::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("PlayerShield"));

	ShieldBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerShield::OnBoxOverlap);
}


/*******   OverlapSystem   ******/

//박스에 닿았을 경우 반응하는 함수
void APlayerShield::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	// 적중 변수 이름

	if (OtherActor->ActorHasTag(FName("EnemyWeapon")))
	{
		FHitResult ShieldBoxHit;
		BoxTrace(ShieldBoxHit);
		//파티클 생성
		if (ShieldParticles && GetWorld())
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				ShieldParticles,
				GetActorLocation()
			);
		}
	}

}
//박스 추적
void APlayerShield::BoxTrace(FHitResult& BoxHit)
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
	for (AActor* Actor : IgnoreActors)
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
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsTognore,
		EDrawDebugTrace::ForDuration,
		BoxHit,
		true
	);
	//중복 불가
	IgnoreActors.AddUnique(BoxHit.GetActor());
}