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
	//�޽ø� ���� �� �ݸ��� ����
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	ShieldMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ShieldMesh;

	//��ü ������Ʈ�� ���� �� �ݸ��� ����
	ShieldBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	ShieldBox->SetupAttachment(GetRootComponent());
	ShieldBox->SetNotifyRigidBodyCollision(true);
	ShieldBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShieldBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	//��ü �ݸ��� ���� ��������
	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("SphereTraceStart"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	//��ü �ݸ��� ���� �� ����
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("SphereTraceEnd"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}


/*******   Equip   ******/

//�� ���Ͽ� ��� ����
void APlayerShield::AttackMeshToSocket(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	//�÷��̾��� ��Ʈ�ѷ��� PopolPlayerController�� �������ش�.
	ItemState = EItemState::EIS_Equipped;
	PopolPlayerController = Cast<APopolPlayerController>(NewInstigator->GetController());
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ShieldMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}


/*******   System   ******/

//Actor ���� �� ����
void APlayerShield::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("PlayerShield"));

	ShieldBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerShield::OnBoxOverlap);
}


/*******   OverlapSystem   ******/

//�ڽ��� ����� ��� �����ϴ� �Լ�
void APlayerShield::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	// ���� ���� �̸�

	if (OtherActor->ActorHasTag(FName("EnemyWeapon")))
	{
		FHitResult ShieldBoxHit;
		BoxTrace(ShieldBoxHit);
		//��ƼŬ ����
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
//�ڽ� ����
void APlayerShield::BoxTrace(FHitResult& BoxHit)
{
	//�� �߰� ���� ����
	const FVector Start = BoxTraceStart->GetComponentLocation();
	//�� �߰� �� ����
	const FVector End = BoxTraceEnd->GetComponentLocation();

	//Actor�� �����ؼ� �����ϴ� ��
	TArray<AActor*> ActorsTognore;

	ActorsTognore.Add(this); // ����
	ActorsTognore.Add(GetOwner()); // �÷��̾�

	//��� �迭 �Լ��� ���� Actord�� ��� ActorsTognore�� Ÿ�� ���� ���ͷ� ����
	for (AActor* Actor : IgnoreActors)
	{
		//����� �ߺ� üũ���� �ʰ� �ѹ��� üũ
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
	//�ߺ� �Ұ�
	IgnoreActors.AddUnique(BoxHit.GetActor());
}