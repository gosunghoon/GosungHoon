// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TakeDamageWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API UTakeDamageWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	/*******   TextBlock   ******/

	//체력 텍스트, EnemyName 초기화
	void SetTakeDamageText(float TextDamage);

private:

	/*******   ProgressBar   ******/

	//Enemy 체력 Widget
	UPROPERTY()
	class UTakeDamageWidget* TakeDamageWidget;
};
