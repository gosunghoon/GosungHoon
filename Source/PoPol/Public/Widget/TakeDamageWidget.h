// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TakeDamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API UTakeDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//���� ��ġ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TakeDamageText;
};
