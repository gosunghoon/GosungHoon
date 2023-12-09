// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:

	/*******   ProgressBar   ******/

	//ü�� �ۼ�Ʈ �� �ʱ�ȭ
	void SetHealthPercent(float PercentP);


	/*******   TextBlock   ******/

	//ü�� �ؽ�Ʈ, EnemyName �ʱ�ȭ
	void SetHealthText(float TextHP, float TextMaxHP, FName Name);

private:

	/*******   ProgressBar   ******/

	//Enemy ü�� Widget
	UPROPERTY()
	class UHealthBar* HealthBarWidget;
};
