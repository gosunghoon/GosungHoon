// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API UNPCButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/*******   Button   ******/

	//버튼 클릭
	UFUNCTION()
	void OnButtonClicked();
	//버튼 사운드 시작
	UFUNCTION()
	void PlayButtonSound();
protected:
	/*******   System   ******/

	//시작 시 System 설정
	virtual void NativeConstruct() override;

private:
	/*******   System   ******/

	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;	//컨트롤러

	/*******   Button   ******/

	//버튼 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* NPCButton;
	//버튼 사운드 생성
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* NPCButtonSound;
	
	/*******   WidgetSystem   ******/

	//NPC ButtonHUD
	UPROPERTY(EditDefaultsOnly, Category = PlayerButton)
	TSubclassOf<class UNPCWidget> NPCWidgettClass;
	//NPC ButtonWidget
	class UNPCWidget* NPCWidget;
};
