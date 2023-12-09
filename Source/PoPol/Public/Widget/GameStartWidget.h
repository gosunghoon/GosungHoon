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

	//���� �� System ����
	virtual void NativeConstruct() override;

	//���� ���� ��ư
	UFUNCTION()
	virtual void OnGameStartButtonClick();
	//���� ���� ��ư
	UFUNCTION()
	virtual void OnGameExitButtonClick();
private:
	/*******   	System  ******/

	//PlayerController
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//�ð� ������ �ɼǵ� ������ ��
	////StatExit Button Ŭ����
	//UPROPERTY(meta = (BindWidget))
	//class UButton* GameStartButton;
	//StatExit Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* GameStartButton;
	//StatExit Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* GameExitButton;

	//��ư ���� ����
	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* ButtonSound;
};
