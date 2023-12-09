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
	//ü�� �ۼ�Ʈ ���� ����
	void SetHealthBarPercent(float Percent);
	//���¹̳� �ۼ�Ʈ ���� ����
	void SetStaminaBarPercent(float Percent);
	//����ġ �ۼ�Ʈ ���� ����
	void SetEXPBarPercent(float Percent);
	//ü�� �ؽ�Ʈ ����
	void SetTextHealth(float Text, float MaxText);
	//���¹̳� �ؽ�Ʈ ����
	void SetTextStamina(float Text, float MaxText);
	//����ġ �ؽ�Ʈ ����
	void SetTextExp(float Text, float MaxText);
	//��� �� ����
	void SetGold(int32 Gold);

protected:
	virtual void NativeConstruct() override;


private:
	//ĳ���� ���� ����
	struct FCharacterStats* CharacterStats;
	//���� Widget�� �����ֱ� ���� InvenWidget
	UPROPERTY(meta = (BindWidget))
	class USlotInvenWidget* SlotInvenWidget;
	
	//Text

	//UI�� ������
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelText;

	//UI�� HP ��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;
	//UI�� MHP ��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHpText;

	//UI�� Stamina��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StaminaText;
	//UI�� Maxtamina��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStaminaText;

	//UI�� Exp��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EXPText;
	//UI�� MaxExp��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxEXPText;

	//UI�� Gold��
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
