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

	//초기화
	virtual void Init() {};
	
public:
	//플레이어를 불러오기 위한 플레이어타입의 변수
	APopolCharacter* PopolCharacter;
};
