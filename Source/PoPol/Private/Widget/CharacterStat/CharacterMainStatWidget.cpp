// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterStat/CharacterMainStatWidget.h"
#include "Widget/CharacterStat/CharacterStatWidget.h"

UCharacterMainStatWidget::UCharacterMainStatWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCharacterMainStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CharacterStatWidget)
	{
		//�ʱ�ȭ (�κ��丮�� Player�����͸� ä���־��ְ� �ʱ�ȭ �Լ��� ����)
		CharacterStatWidget->CharacterStatUI();
	}
}