// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterMainWidget/DeathWidget.h"
#include "Components/Button.h"
#include "Character/Controller/PopolPlayerController.h"
#include "GameFramework/GameModeBase.h"

//���� �� System ����
void UDeathWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// PopolPlayerController
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());

	//��ư
	DeathButton->OnClicked.AddDynamic(this, &UDeathWidget::OnButtonClicked);

	PopolPlayerController->bShowMouseCursor = true;
}

//��ư Ŭ��
void UDeathWidget::OnButtonClicked()
{
	if (ButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	PopolPlayerController->HealthInit();
	GetWorld()->GetAuthGameMode()->RestartPlayer(PopolPlayerController);
	PopolPlayerController->bShowMouseCursor = false;
	RemoveFromParent();
}
