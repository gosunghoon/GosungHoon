// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CoutomWidget.h"
#include "CharacterStatWidget.generated.h"

class UTextBlock;
class UPopolGameInstance;
class APopolCharacter;
struct FCharacterStats;
struct FWeaponData;

UCLASS()
class POPOL_API UCharacterStatWidget : public UCoutomWidget
{
	GENERATED_BODY()
	
public:
	UCharacterStatWidget(const FObjectInitializer& ObjectInitializer);

	/*******   System   ******/

	//���� �� System ����
	virtual void NativeConstruct() override;

	//�ɼ��� �������ִ� �Լ�
	void CharacterStatUI();

	//������ ��ư
	UFUNCTION()
	void StatExitButtonUI();


protected:


public:
	//UI�� Level ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUILevel;
	//UI�� HP ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIHP;
	//UI�� MaxHP ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIMaxHP;
	//UI�� Stamina ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIStamina;
	//UI�� MaxStamina ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIMaxStamina;
	//UI�� AttackDamage ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIAttackDamage;
	//UI�� Defense ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIDefense;
	//UI�� Role ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIPosion;

	//���� �ν��Ͻ�
	UPopolGameInstance* PopolGameInstance;
	//ĳ���� ������ ���̺�
	FCharacterStats* CharacterStats;

	//StatExit Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* StatExitButton;


	struct FWeaponData* CharWeaponData;	//���� ���� ����


	int8 Equipnum;

	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
};
