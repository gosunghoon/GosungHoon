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

	//시작 시 System 설정
	virtual void NativeConstruct() override;

	//옵션을 변경해주는 함수
	void CharacterStatUI();

	//나가기 버튼
	UFUNCTION()
	void StatExitButtonUI();


protected:


public:
	//UI의 Level 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUILevel;
	//UI의 HP 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIHP;
	//UI의 MaxHP 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIMaxHP;
	//UI의 Stamina 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIStamina;
	//UI의 MaxStamina 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIMaxStamina;
	//UI의 AttackDamage 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIAttackDamage;
	//UI의 Defense 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIDefense;
	//UI의 Role 값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StatUIPosion;

	//게임 인스턴스
	UPopolGameInstance* PopolGameInstance;
	//캐릭터 데이터 테이블
	FCharacterStats* CharacterStats;

	//StatExit Button 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* StatExitButton;


	struct FWeaponData* CharWeaponData;	//무기 스탯 정보


	int8 Equipnum;

	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
};
