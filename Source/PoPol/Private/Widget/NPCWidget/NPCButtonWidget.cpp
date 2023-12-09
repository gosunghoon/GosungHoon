// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPCWidget/NPCButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Widget/NPCWidget/NPCWidget.h"
#include "Character/Controller/PopolPlayerController.h"

//��ư Ŭ��
void UNPCButtonWidget::OnButtonClicked()
{
	PlayButtonSound();
	//Widget ����
	RemoveFromParent();

	//�÷��̾��� ��Ʈ�ѷ�
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//Button Widget
	NPCWidget = CreateWidget<UNPCWidget>(PopolPlayerController, NPCWidgettClass);
	if (NPCWidget)
	{
		//Widget ����
		NPCWidget->AddToViewport();
	}
}
//��ư ���� ����
void UNPCButtonWidget::PlayButtonSound()
{
	if (NPCButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, NPCButtonSound, 2.5f);
	}
}
/*******   System   ******/

//���� �� System ����
void UNPCButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//��ư
	NPCButton->OnClicked.AddDynamic(this, &UNPCButtonWidget::OnButtonClicked);
}
