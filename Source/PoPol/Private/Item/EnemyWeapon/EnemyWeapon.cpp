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
//�� ���Ͽ� ��� ����
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

//Actor ���� �� ����
void AEnemyWeapon::BeginPlay()
{
	Super::BeginPlay();


	Tags.Add(FName("EnemyWeapon"));

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyWeapon::OnBoxOverlap);
}


/*******   OverlapSystem   ******/

//�ڽ��� ����� ��� �����ϴ� �Լ�
void AEnemyWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	// ���� ���� �̸�
	FHitResult EnemyBoxHit;

	if (OtherActor->ActorHasTag(FName("PlayerCharacter")))
	{
		BoxTrace(EnemyBoxHit);

		UPopolGameInstance* PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		//���� ���� �������� ���� �ҷ����� ��
		EnemyWeaponData = PopolGameInstance->GetEnemyWeaponData(EnemyCharacter->EnemyNum);
		//Enemy ����
		EnemyStats = PopolGameInstance->GetEnemyStatsData(EnemyCharacter->EnemyNum);


		float EnemyWeaponDamage = EnemyWeaponData->Damage + EnemyStats->AttackDamage;
		UGameplayStatics::ApplyDamage(EnemyBoxHit.GetActor(), EnemyWeaponDamage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
	}

	IHitInterface* HitInterpace = Cast<IHitInterface>(EnemyBoxHit.GetActor());
	if (HitInterpace)
	{
		HitInterpace->GetHit(EnemyBoxHit.ImpactPoint);
	}
	//�ߺ� �Ұ�
	IgnoreActors.AddUnique(EnemyBoxHit.GetActor());
}
//�ڽ� ����
void AEnemyWeapon::BoxTrace(FHitResult& BoxHit)
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
	for (auto Actor : IgnoreActors)
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
		ETraceTypeQuery::TraceTypeQuery2,
		false,
		ActorsTognore,
		EDrawDebugTrace::None,
		BoxHit,
		true
	);
	//�ߺ� �Ұ�
	IgnoreActors.AddUnique(BoxHit.GetActor());
}