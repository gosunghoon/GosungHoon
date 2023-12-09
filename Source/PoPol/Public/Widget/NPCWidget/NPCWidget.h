// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCWidget.generated.h"



class UButton;
/*

*
* 
 * 
 */
UCLASS()
class POPOL_API UNPCWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*******   Button   ******/

	//Story??? ???
	UFUNCTION()
	void OnStoryButtonClicked();
	//Story??? ???
	UFUNCTION()
	void OnStorySkipButtonClicked();
	//Shop??? ???
	UFUNCTION()
	void OnShopButtonClicked();
	//Exit??? ???
	UFUNCTION()
	void OnEixtButtonClicked();
	//??? ???? ????
	UFUNCTION()
	void PlayButtonSound();

	/*******   Text   ******/

	//??? ???? Text?? ????
	void SetNPCText(FString NPCText);


protected:
	/*******   System   ******/

	//???? ?? System ????
	virtual void NativeConstruct() override;


private:
	/*******   System   ******/

	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;	//??????


	/*******   Button   ******/

	//Story??? ?????
	UPROPERTY(meta = (BindWidget))
	UButton* StoryButton;
	//Story??? ?????
	UPROPERTY(meta = (BindWidget))
	UButton* StorySkipButton;
	//Shop??? ?????
	UPROPERTY(meta = (BindWidget))
	UButton* ShopButton;
	//Exit??? ?????
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;
	//??? ???? ????
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* ButtonSound;


	/*******   Text   ******/

	//??? ????
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCConversation;
	//??? ????
	int TextNum;

	FString TextNum1;
	FString TextNum2;
	FString TextNum3;
	FString TextNum4;
	FString TextNum5;
	FString TextNum6;
	FString TextNum7;


	/*******   WidgetSystem   ******/

	//NPC ButtonHUD
	UPROPERTY(EditDefaultsOnly, Category = PlayerButton)
	TSubclassOf<class UNPCShopSlotWidget> NPCShopSlotWidgetClass;
	//NPC ButtonWidget
	class UNPCShopSlotWidget* NPCShopSlotWidget;
};
