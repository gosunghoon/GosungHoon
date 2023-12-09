// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterMainWidget/PlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Character/PopolCharacter.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character/State/PopolPlayerState.h"
#include "Widget/CharacterItemSlot/SlotInvenWidget.h"
#include "Widget/CharacterItemSlot/SlotWidget.h"


//���� �ؽ�Ʈ ����
void UPlayerWidget::SetLevel(int8 Level)
{
	const FString String = FString::Printf(TEXT("%d"), Level);
	const FText Text = FText::FromString(String);
	LevelText->SetText(Text);
}
//ü�� �ۼ�Ʈ ���� ����
void UPlayerWidget::SetHealthBarPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}
//ü�� �ؽ�Ʈ ����
void UPlayerWidget::SetTextHealth(float Text, float MaxText)
{
	HPText->SetText(FText::FromString(FString::FromInt(Text)));
	MaxHpText->SetText(FText::FromString(FString::FromInt(MaxText)));
}
//���¹̳� �ۼ�Ʈ ���� ����
void UPlayerWidget::SetStaminaBarPercent(float Percent)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percent);
	}
}
//���¹̳� �ؽ�Ʈ ����
void UPlayerWidget::SetTextStamina(float Text, float MaxText)
{
	//TextStamina
	StaminaText->SetText(FText::FromString(FString::FromInt(Text)));
	//TextMaxStamina
	MaxStaminaText->SetText(FText::FromString(FString::FromInt(MaxText)));
}
//����ġ �ۼ�Ʈ ���� ����
void UPlayerWidget::SetEXPBarPercent(float Percent)
{
	if (EXPBar)
	{
		EXPBar->SetPercent(Percent);
	}
}
//����ġ �ؽ�Ʈ ����
void UPlayerWidget::SetTextExp(float Text, float MaxText)
{
	//TextStamina
	EXPText->SetText(FText::FromString(FString::SanitizeFloat(Text)));
	//TextMaxStamina
	MaxEXPText->SetText(FText::FromString(FString::SanitizeFloat(MaxText)));
}
//��� �� ����
void UPlayerWidget::SetGold(int32 Gold)
{
	if (GoldText)
	{
		const FString String = FString::Printf(TEXT("%d"), Gold);
		const FText Text = FText::FromString(String);
		GoldText->SetText(Text);
	}
}
//�ʱ�ȭ
void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerWidget::Init()
{
	if (SlotInvenWidget)
	{
		SlotInvenWidget->Init();
	}
}