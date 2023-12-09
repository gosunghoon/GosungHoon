// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"


UCLASS()
class POPOL_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	/*******   System   ******/

	//시작 시 System 설정
	virtual void NativeConstruct() override;

	//게임 시작 버튼
	UFUNCTION()
	virtual void OnGameStartButtonClick();
	//게임 종료 버튼
	UFUNCTION()
	virtual void OnGameExitButtonClick();
private:
	/*******   	System  ******/

	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//시간 남으면 옵션도 설정할 것
	////StatExit Button 클래스
	//UPROPERTY(meta = (BindWidget))
	//class UButton* GameStartButton;
	//StatExit Button 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* GameStartButton;
	//StatExit Button 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* GameExitButton;

	//버튼 사운드 생성
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* ButtonSound;
};
