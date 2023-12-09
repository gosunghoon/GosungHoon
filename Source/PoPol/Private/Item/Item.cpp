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

	//충돌 횟수
	CollisionNum = 1;

	//아이템 상태
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

//시작 시 System 설정
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Item"));
	//충돌 반응
	ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnButtonOverlap);
	//충돌 끝 반응
	ItemSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnButtonOverlapEnd);
}
//Sin값 이동
float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

/*******   OverlapSystem   ******/

//Shere충돌 반응
void AItem::OnButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	//플레이어 컨트롤러
	PopolPlayerController = Cast<APopolPlayerController>(OtherActor->GetInstigatorController());
	if (OtherActor->ActorHasTag(FName("PlayerCharacter")))
	{
		//Button Widget
		ItemDropWidget = CreateWidget<UItemDropWidget>(PopolPlayerController, PlayerItemDropClass);
		if (ItemDropWidget && CollisionNum == 1)
		{
			//충돌 횟수
			CollisionNum -= 1;
			//무기번호
			ItemDropWidget->SetSlotWeaponNum(WeaponNum, OtherActor);
			//Widget 생성
			ItemDropWidget->AddToViewport();
		}
	}
}
//Shere충돌 끝 반응
void AItem::OnButtonOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ItemDropWidget && CollisionNum == 0)
	{
		//ItemDropWidget->RemoveFromParent();
		//충돌 횟수
		CollisionNum += 1;
	}
}
