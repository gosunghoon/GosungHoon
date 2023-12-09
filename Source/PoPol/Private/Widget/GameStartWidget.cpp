// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameStartWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Controller/PopolPlayerController.h"

//���� �� System ����
void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//�÷��̾��� ��Ʈ�ѷ��� PopolPlayerController�� �������ش�.
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	GameStartButton->OnClicked.AddDynamic(this, &UGameStartWidget::OnGameStartButtonClick);
	GameExitButton->OnClicked.AddDynamic(this, &UGameStartWidget::OnGameExitButtonClick);

	//PopolPlayerController->bShowMouseCursor = true;
}
//���� ���� ��ư
void UGameStartWidget::OnGameStartButtonClick()
{
	if (ButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	// ���� ����
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Test"));
}
//���� ���� ��ư
void UGameStartWidget::OnGameExitButtonClick()
{
	if (ButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	// ���� ����
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
