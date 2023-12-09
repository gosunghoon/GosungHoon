// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CoutomWidget.h"
#include "DeathWidget.generated.h"


class UTextBlock;

/**
 * 
 */
UCLASS()
class POPOL_API UDeathWidget : public UCoutomWidget
{
	GENERATED_BODY()
public:
	/*******   Button   ******/

	//버튼 클릭
	UFUNCTION()
	void OnButtonClicked();
	
protected:
	/*******   System   ******/

	//시작 시 System 설정
	virtual void NativeConstruct() override;

private:
	/*******   	System  ******/
	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	/*******   Button   ******/

	//버튼 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* DeathButton;

	/*******   TextBlock   ******/

	//사망 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathText;
	//Button 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	//버튼 사운드 생성
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* ButtonSound;
};
