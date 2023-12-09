// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CoutomWidget.h"
#include "PlayerWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class POPOL_API UPlayerWidget : public UCoutomWidget
{
	GENERATED_BODY()
public:

	virtual void Init() override;

	void SetLevel(int8 Level);
	//체력 퍼센트 비율 조정
	void SetHealthBarPercent(float Percent);
	//스태미나 퍼센트 비율 조정
	void SetStaminaBarPercent(float Percent);
	//경험치 퍼센트 비율 조정
	void SetEXPBarPercent(float Percent);
	//체력 텍스트 조정
	void SetTextHealth(float Text, float MaxText);
	//스태미나 텍스트 조정
	void SetTextStamina(float Text, float MaxText);
	//경험치 텍스트 조정
	void SetTextExp(float Text, float MaxText);
	//골드 량 조정
	void SetGold(int32 Gold);

protected:
	virtual void NativeConstruct() override;


private:
	//캐릭터 스탯 정보
	struct FCharacterStats* CharacterStats;
	//메인 Widget에 보여주기 위한 InvenWidget
	UPROPERTY(meta = (BindWidget))
	class USlotInvenWidget* SlotInvenWidget;
	
	//Text

	//UI의 레벨값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelText;

	//UI의 HP 값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;
	//UI의 MHP 값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHpText;

	//UI의 Stamina값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StaminaText;
	//UI의 Maxtamina값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStaminaText;

	//UI의 Exp값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EXPText;
	//UI의 MaxExp값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxEXPText;

	//UI의 Gold값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldText;




	//Bar//

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* EXPBar;
};
