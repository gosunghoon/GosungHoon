// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CoutomWidget.h"
#include "CharacterMainStatWidget.generated.h"

class UCharacterStatWidget;

UCLASS()
class POPOL_API UCharacterMainStatWidget : public UCoutomWidget
{
	GENERATED_BODY()

public:
	UCharacterMainStatWidget(const FObjectInitializer& ObjectInitializer);

	/*******   System   ******/

	//���� �� System ����
	virtual void NativeConstruct() override;

public:
	//���� Widget�� �����ֱ� ���� CharacterStatWidget, meta = (BindWidget)�� ���� Widget�� ���� ����
	UPROPERTY(meta = (BindWidget))
	UCharacterStatWidget* CharacterStatWidget;

};
