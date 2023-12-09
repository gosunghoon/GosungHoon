// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CoutomWidget.h"
#include "Character/Type/CharacterType.h"
#include "SlotWidget.generated.h"

class UImage;
class UButton;
class AWeapon;
class UDataTable;

/**
 * 
 */
UCLASS()
class POPOL_API USlotWidget : public UCoutomWidget
{
	GENERATED_BODY()

public:
	USlotWidget(const FObjectInitializer& ObjectInitializer);

	////CustomWidget���� Override�� �ʱ�ȭ �Լ�
	virtual void Init() override;
	//Texture�� �������ִ� �Լ�
	void SlotSetTexture(UTexture2D* tex);
	//�ɼ��� �������ִ� �Լ�
	void SlotRefresh();

public:
	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMax = 4, UIMin = 0))
	int Slotnum;

	//���Կ� ���� ��� �̹��� meta = (BindWidget)�� ���� Widget�� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotImg;

	//UserCharacterStat�� ���� ��� �ؽ�Ʈ�ڽ� meta = (BindWidget)�� ���� Widget�� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SlotText;

private:
	class UPopolGameInstance* PopolGameInstance;
	//���� ������ ���̺�
	struct FWeaponData* WeaponData;
	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;

	//�̹��� ��ȣ
	int ImageNum;

	FLinearColor Color;
};
