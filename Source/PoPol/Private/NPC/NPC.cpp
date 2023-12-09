// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC.h"
#include "Components/BoxComponent.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Widget/NPCWidget/NPCButtonWidget.h"


/*******   MainSystem   ******/

//Main
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	NPCBox = CreateDefaultSubobject<UBoxComponent>(TEXT("NPCBox"));
	NPCBox->SetupAttachment(GetRootComponent());

	CollisionNum = 1;
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/*******   System   ******/

//Actor 생성 시 설정
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("NPC"));

	//충돌 반응
	NPCBox->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBoxOverlap);
	//충돌 끝 반응
	NPCBox->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnButtonOverlapEnd);
}
/*******   OverlapSystem   ******/

//Box충돌 반응
void ANPC::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("PlayerCharacter")))
	{
		//플레이어 컨트롤러
		PopolPlayerController = Cast<APopolPlayerController>(OtherActor->GetInstigatorController());

		//Button Widget
		NPCButtonWidget = CreateWidget<UNPCButtonWidget>(PopolPlayerController, NPCButtonWidgetClass);
		if (NPCButtonWidget && CollisionNum == 1)
		{
			//충돌 횟수
			CollisionNum -= 1;
			//Widget 생성
			NPCButtonWidget->AddToViewport();
		}
	}
}
//Box충돌 끝 반응
void ANPC::OnButtonOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (NPCButtonWidget && CollisionNum == 0)
	{
		//Widget 삭제
		//NPCButtonWidget->RemoveFromParent();
		//충돌 횟수
		CollisionNum += 1;
	}
}