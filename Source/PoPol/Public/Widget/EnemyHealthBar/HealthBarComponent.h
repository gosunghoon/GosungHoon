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

	//체력 퍼센트 바 초기화
	void SetHealthPercent(float PercentP);


	/*******   TextBlock   ******/

	//체력 텍스트, EnemyName 초기화
	void SetHealthText(float TextHP, float TextMaxHP, FName Name);

private:

	/*******   ProgressBar   ******/

	//Enemy 체력 Widget
	UPROPERTY()
	class UHealthBar* HealthBarWidget;
};
