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

//Actor ���� �� ����
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("NPC"));

	//�浹 ����
	NPCBox->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBoxOverlap);
	//�浹 �� ����
	NPCBox->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnButtonOverlapEnd);
}
/*******   OverlapSystem   ******/

//Box�浹 ����
void ANPC::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("PlayerCharacter")))
	{
		//�÷��̾� ��Ʈ�ѷ�
		PopolPlayerController = Cast<APopolPlayerController>(OtherActor->GetInstigatorController());

		//Button Widget
		NPCButtonWidget = CreateWidget<UNPCButtonWidget>(PopolPlayerController, NPCButtonWidgetClass);
		if (NPCButtonWidget && CollisionNum == 1)
		{
			//�浹 Ƚ��
			CollisionNum -= 1;
			//Widget ����
			NPCButtonWidget->AddToViewport();
		}
	}
}
//Box�浹 �� ����
void ANPC::OnButtonOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (NPCButtonWidget && CollisionNum == 0)
	{
		//Widget ����
		//NPCButtonWidget->RemoveFromParent();
		//�浹 Ƚ��
		CollisionNum += 1;
	}
}