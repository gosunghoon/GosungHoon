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

	//시작 시 System 설정
	virtual void NativeConstruct() override;

public:
	//메인 Widget에 보여주기 위한 CharacterStatWidget, meta = (BindWidget)를 통해 Widget과 연동 가능
	UPROPERTY(meta = (BindWidget))
	UCharacterStatWidget* CharacterStatWidget;

};
