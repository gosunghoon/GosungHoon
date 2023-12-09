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

	//CustomWidget���� Override�� �ʱ�ȭ �Լ�
	virtual void Init() override;

public:
	//��� ���� ��� �־��� �ؽ�Ʈ �̹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* DefTex;

private:
	//InvenWidget�� Slot�� �ϳ��ϳ� �� �ɼ�
	TArray<USlotWidget*> SlotWidget;

	int WeaponDataRow;

	UDataTable* DTWeapon;

	FWeaponData* WeaponDataTable;
};
