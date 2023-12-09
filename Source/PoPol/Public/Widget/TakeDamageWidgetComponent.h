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

	//ü�� �ؽ�Ʈ, EnemyName �ʱ�ȭ
	void SetTakeDamageText(float TextDamage);

private:

	/*******   ProgressBar   ******/

	//Enemy ü�� Widget
	UPROPERTY()
	class UTakeDamageWidget* TakeDamageWidget;
};
