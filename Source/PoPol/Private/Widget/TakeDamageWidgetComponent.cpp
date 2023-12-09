// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TakeDamageWidgetComponent.h"
#include "Components/TextBlock.h"
#include "Widget/TakeDamageWidget.h"

/*******   TextBlock   ******/

//체력 텍스트 초기화
void UTakeDamageWidgetComponent::SetTakeDamageText(float TextDamage)
{
	if (TakeDamageWidget == nullptr)
	{
		TakeDamageWidget = Cast<UTakeDamageWidget>(GetUserWidgetObject());
	}
	TakeDamageWidget->TakeDamageText->SetText(FText::FromString(FString::FromInt(TextDamage)));
}