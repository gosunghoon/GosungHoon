// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EnemyHealthBar/HealthBarComponent.h"
#include "Widget/EnemyHealthBar/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

/*******   ProgressBar   ******/

//ü�� �ۼ�Ʈ �� �ʱ�ȭ
void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{
		//SetPercent : float�� ����ϰ� ����� ǥ������ ���� ���� �����Ѵ�.
		HealthBarWidget->HealthBar->SetPercent(Percent);

	}
}


/*******   TextBlock   ******/

//ü�� �ؽ�Ʈ �ʱ�ȭ
void UHealthBarComponent::SetHealthText(float TextHP, float TextMaxHP, FName Name)
{
	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	HealthBarWidget->HPText->SetText(FText::FromString(FString::FromInt(TextHP)));
	HealthBarWidget->MaxHpText->SetText(FText::FromString(FString::FromInt(TextMaxHP)));
	HealthBarWidget->EnemyName->SetText(FText::FromName(Name));
}