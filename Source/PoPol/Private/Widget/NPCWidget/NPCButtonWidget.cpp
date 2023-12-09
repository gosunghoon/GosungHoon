// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPCWidget/NPCButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Widget/NPCWidget/NPCWidget.h"
#include "Character/Controller/PopolPlayerController.h"

//버튼 클릭
void UNPCButtonWidget::OnButtonClicked()
{
	PlayButtonSound();
	//Widget 삭제
	RemoveFromParent();

	//플레이어의 컨트롤러
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//Button Widget
	NPCWidget = CreateWidget<UNPCWidget>(PopolPlayerController, NPCWidgettClass);
	if (NPCWidget)
	{
		//Widget 생성
		NPCWidget->AddToViewport();
	}
}
//버튼 사운드 시작
void UNPCButtonWidget::PlayButtonSound()
{
	if (NPCButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, NPCButtonSound, 2.5f);
	}
}
/*******   System   ******/

//시작 시 System 설정
void UNPCButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//버튼
	NPCButton->OnClicked.AddDynamic(this, &UNPCButtonWidget::OnButtonClicked);
}
