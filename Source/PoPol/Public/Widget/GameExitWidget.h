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

	//���� �� System ����
	virtual void NativeConstruct() override;

	//���� ���ư��� ��ư
	UFUNCTION()
	virtual void OnGameRerollButtonClick();
	//���� �޴� ���ư���
	UFUNCTION()
	virtual void OnGameMainMenuButtonClick();
	//���� ����
	UFUNCTION()
	virtual void OnGameExitButtonClick();

private:
	/*******   	System  ******/

	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//StatExit Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* GameReStartButton;
	//StatExit Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* GameStartWidgetButton;
	//StatExit Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* GameExitButton;


	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<UGameStartWidget> GameStartWidgetclass;
	UGameStartWidget* GameStartWidget;

	//��ư ���� ����
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* ButtonSound;
};
