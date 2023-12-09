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

	//��ư Ŭ��
	UFUNCTION()
	void OnButtonClicked();
	//��ư ���� ����
	UFUNCTION()
	void PlayButtonSound();
protected:
	/*******   System   ******/

	//���� �� System ����
	virtual void NativeConstruct() override;

private:
	/*******   System   ******/

	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;	//��Ʈ�ѷ�

	/*******   Button   ******/

	//��ư Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* NPCButton;
	//��ư ���� ����
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* NPCButtonSound;
	
	/*******   WidgetSystem   ******/

	//NPC ButtonHUD
	UPROPERTY(EditDefaultsOnly, Category = PlayerButton)
	TSubclassOf<class UNPCWidget> NPCWidgettClass;
	//NPC ButtonWidget
	class UNPCWidget* NPCWidget;
};
