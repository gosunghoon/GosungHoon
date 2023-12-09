// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CoutomWidget.h"
#include "ItemDropWidget.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API UItemDropWidget : public UCoutomWidget
{
	GENERATED_BODY()
public:

	/*******   SlotWeaponNum   ******/

	//슬롯에 들어갈 무기 번호
	int SetSlotWeaponNum(int WeaponNum, AActor* Target);

	/*******   Button   ******/

	//버튼 클릭
	UFUNCTION()
	void OnButtonClicked();
	//버튼 사운드 시작
	UFUNCTION()
	void PlayButtonSound();
	//아이템 드랍 여부
	bool bDrop;


protected:
	/*******   System   ******/

	//시작 시 System 설정
	virtual void NativeConstruct() override;

private:
	/*******   Button   ******/

	//버튼 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* DtopButton;
	//버튼 사운드 생성
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* ButtonSound;


	/*******   SlotWeaponNum   ******/

	//슬롯 클래스
	class USlotWidget* SlotWidget;
	//무기 번호
	int SlotWeaponNum;


	/*******   System   ******/

	//플레이어 컨트롤러
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//플레이어
	class APopolCharacter* PopolCharacter;
};
