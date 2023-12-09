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

	//ü�� �ۼ�Ʈ ��
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	/*******   TextBlock   ******/

	//UI�� HP ��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;
	//UI�� MHP ��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHpText;
	//UI�� ���� �̸�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyName;
};
