// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CoutomWidget.h"
#include "Character/Type/CharacterType.h"
#include "SlotInvenWidget.generated.h"

class USlotWidget;
class UDataTable;
struct FWeaponData;

/**
 * 
 */
UCLASS()
class POPOL_API USlotInvenWidget : public UCoutomWidget
{
	GENERATED_BODY()

public:
	USlotInvenWidget(const FObjectInitializer& ObjectInitializer);

	//CustomWidget에서 Override한 초기화 함수
	virtual void Init() override;

public:
	//비어 있을 경우 넣어줄 텍스트 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* DefTex;

private:
	//InvenWidget의 Slot에 하나하나 들어갈 옵션
	TArray<USlotWidget*> SlotWidget;

	int WeaponDataRow;

	UDataTable* DTWeapon;

	FWeaponData* WeaponDataTable;
};
