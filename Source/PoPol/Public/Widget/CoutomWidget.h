// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoutomWidget.generated.h"


class APopolCharacter;

/**
 * 
 */
UCLASS()
class POPOL_API UCoutomWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCoutomWidget(const FObjectInitializer& ObjectInitializer);

	//�ʱ�ȭ
	virtual void Init() {};
	
public:
	//�÷��̾ �ҷ����� ���� �÷��̾�Ÿ���� ����
	APopolCharacter* PopolCharacter;
};
