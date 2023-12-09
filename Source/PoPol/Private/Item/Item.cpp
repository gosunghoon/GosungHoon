// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Components/SphereComponent.h"
#include "Widget/CharacterMainWidget/ItemDropWidget.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Character/PopolCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"



/*******   System   ******/

//Main
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	//Item Mesh
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMesh;

	//Sphere Collision
	ItemSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ItemSphere"));
	ItemSphere->SetupAttachment(RootComponent);

	//�浹 Ƚ��
	CollisionNum = 1;

	//������ ����
	ItemState = EItemState::EIS_Hovering;

	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	EmbersEffect->SetupAttachment(GetRootComponent());
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
}
/*******   System   ******/

//���� �� System ����
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Item"));
	//�浹 ����
	ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnButtonOverlap);
	//�浹 �� ����
	ItemSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnButtonOverlapEnd);
}
//Sin�� �̵�
float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

/*******   OverlapSystem   ******/

//Shere�浹 ����
void AItem::OnButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	//�÷��̾� ��Ʈ�ѷ�
	PopolPlayerController = Cast<APopolPlayerController>(OtherActor->GetInstigatorController());
	if (OtherActor->ActorHasTag(FName("PlayerCharacter")))
	{
		//Button Widget
		ItemDropWidget = CreateWidget<UItemDropWidget>(PopolPlayerController, PlayerItemDropClass);
		if (ItemDropWidget && CollisionNum == 1)
		{
			//�浹 Ƚ��
			CollisionNum -= 1;
			//�����ȣ
			ItemDropWidget->SetSlotWeaponNum(WeaponNum, OtherActor);
			//Widget ����
			ItemDropWidget->AddToViewport();
		}
	}
}
//Shere�浹 �� ����
void AItem::OnButtonOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ItemDropWidget && CollisionNum == 0)
	{
		//ItemDropWidget->RemoveFromParent();
		//�浹 Ƚ��
		CollisionNum += 1;
	}
}
