// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UTextBlock;



UCLASS()
class POPOL_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:


	/*******   ProgressBar   ******/

	//체력 퍼센트 바
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	/*******   TextBlock   ******/

	//UI의 HP 값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;
	//UI의 MHP 값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHpText;
	//UI의 몬스터 이름
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyName;
};
