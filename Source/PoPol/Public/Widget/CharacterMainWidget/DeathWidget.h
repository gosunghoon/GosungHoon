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

	//��ư Ŭ��
	UFUNCTION()
	void OnButtonClicked();
	
protected:
	/*******   System   ******/

	//���� �� System ����
	virtual void NativeConstruct() override;

private:
	/*******   	System  ******/
	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	/*******   Button   ******/

	//��ư Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* DeathButton;

	/*******   TextBlock   ******/

	//��� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathText;
	//Button �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	//��ư ���� ����
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* ButtonSound;
};
