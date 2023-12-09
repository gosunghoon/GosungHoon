// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterMainWidget/DeathWidget.h"
#include "Components/Button.h"
#include "Character/Controller/PopolPlayerController.h"
#include "GameFramework/GameModeBase.h"

//시작 시 System 설정
void UDeathWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// PopolPlayerController
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());

	//버튼
	DeathButton->OnClicked.AddDynamic(this, &UDeathWidget::OnButtonClicked);

	PopolPlayerController->bShowMouseCursor = true;
}

//버튼 클릭
void UDeathWidget::OnButtonClicked()
{
	if (ButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	PopolPlayerController->HealthInit();
	GetWorld()->GetAuthGameMode()->RestartPlayer(PopolPlayerController);
	PopolPlayerController->bShowMouseCursor = false;
	RemoveFromParent();
}
