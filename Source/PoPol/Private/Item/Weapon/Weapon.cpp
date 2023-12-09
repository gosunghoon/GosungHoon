// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Weapon.h"
#include "Item/Item.h"
#include "GameInstance/PopolGameInstance.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/HitInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "Character/PopolCharacter.h"
#include "Widget/CharacterMainWidget/ItemDropWidget.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Character/State/PopolPlayerState.h"


/*******   MainSystem   ******/

//Main
AWeapon::AWeapon()
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

/*******   Equip   ******/

//�� ���Ͽ� ��� ����
void AWeapon::AttackMeshToSocket(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator)
{

	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	ItemState = EItemState::EIS_Equipped;
	//�÷��̾��� ��Ʈ�ѷ��� PopolPlayerController�� �������ش�.
	PopolPlayerController = Cast<APopolPlayerController>(NewInstigator->GetController());
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	WeaponMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}


/*******   System   ******/

//Actor ���� �� ����
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("PlayerWeapon"));

	//�÷��̾��� ��Ʈ�ѷ��� PopolPlayerController�� �������ش�.
	PopolPlayerController = Cast<APopolPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}


/*******   OverlapSystem   ******/

//�ڽ��� ����� ��� �����ϴ� �Լ�
void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//����� ���̶��
	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		// ���� ���� �̸�
		FHitResult CharacterBoxHit;
		//�ڽ� ����
		BoxTrace(CharacterBoxHit);

		//�ν��Ͻ��� �ҷ��´�.
		UPopolGameInstance* PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		//���� ������
		WeaponData = PopolGameInstance->GetWeaponDamageData(PopolPlayerController->GetEqipWeaponNum());
		////ĳ���� ����
		//CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerController->GetStatePlayerLevel());


		//���ݷ� ���  �� ����
		PlayerAttackDamage = WeaponData->Damage + PopolPlayerController->GetPlayerAttackControll(); //�÷��̾� ���ݷ� ���
		UGameplayStatics::ApplyDamage(CharacterBoxHit.GetActor(), PlayerAttackDamage, GetInstigator()->GetController(), this, UDamageType::StaticClass());


		//��Ʈ �������̽�
		IHitInterface* HitInterpace = Cast<IHitInterface>(CharacterBoxHit.GetActor());
		if (HitInterpace)
		{
			//��Ʈ ����Ʈ
			HitInterpace->GetHit(CharacterBoxHit.ImpactPoint);
		}
		//�ߺ� �Ұ�
		IgnoreActors.AddUnique(CharacterBoxHit.GetActor());
	}
}
//�ڽ� ����
void AWeapon::BoxTrace(FHitResult& BoxHit)
{
	//�� �߰� ���� ����
	const FVector Start = BoxTraceStart->GetComponentLocation();
	//�� �߰� �� ����
	const FVector End = BoxTraceEnd->GetComponentLocation();

	//��� ����
	TArray<AActor*> ActorsTognore;

	ActorsTognore.Add(this); // ����
	ActorsTognore.Add(GetOwner()); // �÷��̾�

	//Ÿ�� ���� ���ͷ� ����
	for (AActor* Actor : IgnoreActors)
	{
		//����� �ߺ� üũ���� �ʰ� �ѹ��� üũ
		ActorsTognore.AddUnique(Actor);
	}
	//�̱� �ڽ� Ʈ���̽�
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		TarceHalfSize,
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsTognore,
		EDrawDebugTrace::None,
		BoxHit,
		true
	);
	//�ߺ� �Ұ�
	IgnoreActors.AddUnique(BoxHit.GetActor());
}