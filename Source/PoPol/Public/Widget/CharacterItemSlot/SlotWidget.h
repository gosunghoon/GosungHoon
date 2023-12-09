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

	////CustomWidget에서 Override한 초기화 함수
	virtual void Init() override;
	//Texture을 변경해주는 함수
	void SlotSetTexture(UTexture2D* tex);
	//옵션을 변경해주는 함수
	void SlotRefresh();

public:
	//슬롯 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMax = 4, UIMin = 0))
	int Slotnum;

	//슬롯에 들어가는 대상 이미지 meta = (BindWidget)를 통해 Widget과 연동 가능
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotImg;

	//UserCharacterStat에 들어가는 대상 텍스트박스 meta = (BindWidget)를 통해 Widget과 연동 가능
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SlotText;

private:
	class UPopolGameInstance* PopolGameInstance;
	//무기 데이터 테이블
	struct FWeaponData* WeaponData;
	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;

	//이미지 번호
	int ImageNum;

	FLinearColor Color;
};
