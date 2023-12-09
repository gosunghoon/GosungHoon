// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameExitWidget.generated.h"

class UGameStartWidget;

/**
 * 
 */
UCLASS()
class POPOL_API UGameExitWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/*******   System   ******/

	//시작 시 System 설정
	virtual void NativeConstruct() override;

	//게임 돌아가기 버튼
	UFUNCTION()
	virtual void OnGameRerollButtonClick();
	//메인 메뉴 돌아가기
	UFUNCTION()
	virtual void OnGameMainMenuButtonClick();
	//게임 종료
	UFUNCTION()
	virtual void OnGameExitButtonClick();

private:
	/*******   	System  ******/

	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//StatExit Button 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* GameReStartButton;
	//StatExit Button 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* GameStartWidgetButton;
	//StatExit Button 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* GameExitButton;


	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<UGameStartWidget> GameStartWidgetclass;
	UGameStartWidget* GameStartWidget;

	//버튼 사운드 생성
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* ButtonSound;
};
