// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameExitWidget.h"
#include "Components/Button.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/GameStartWidget.h"

void UGameExitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//�÷��̾��� ��Ʈ�ѷ��� PopolPlayerController�� �������ش�.
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());

	GameStartWidget = CreateWidget<UGameStartWidget>(PopolPlayerController, GameStartWidgetclass);

	PopolPlayerController->bShowMouseCursor = true;

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	GameReStartButton->OnClicked.AddDynamic(this, &UGameExitWidget::OnGameRerollButtonClick);
	GameStartWidgetButton->OnClicked.AddDynamic(this, &UGameExitWidget::OnGameMainMenuButtonClick);
	GameExitButton->OnClicked.AddDynamic(this, &UGameExitWidget::OnGameExitButtonClick);
}
//���� ���ư��� ��ư
void UGameExitWidget::OnGameRerollButtonClick()
{
	if (ButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	PopolPlayerController->bShowMouseCursor = false;
	PopolPlayerController->SetPause(false);			//���� �Ͻ�����
	RemoveFromParent();
}
//���� �޴� ���ư���
void UGameExitWidget::OnGameMainMenuButtonClick()
{
	if (ButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	RemoveFromParent();
	if (GameStartWidget)
	{	// ���� ����
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartMap"));
		GameStartWidget->AddToViewport();
	}
}
//���� ����
void UGameExitWidget::OnGameExitButtonClick()
{
	if (ButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	// ���� ����
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
