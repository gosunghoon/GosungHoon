// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EnemyHealthBar/HealthBarComponent.h"
#include "Widget/EnemyHealthBar/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

/*******   ProgressBar   ******/

//체력 퍼센트 바 초기화
void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{
		//SetPercent : float을 사용하고 진행률 표시줄의 현재 값을 설정한다.
		HealthBarWidget->HealthBar->SetPercent(Percent);

	}
}


/*******   TextBlock   ******/

//체력 텍스트 초기화
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