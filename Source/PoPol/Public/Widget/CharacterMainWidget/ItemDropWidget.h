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

	//���Կ� �� ���� ��ȣ
	int SetSlotWeaponNum(int WeaponNum, AActor* Target);

	/*******   Button   ******/

	//��ư Ŭ��
	UFUNCTION()
	void OnButtonClicked();
	//��ư ���� ����
	UFUNCTION()
	void PlayButtonSound();
	//������ ��� ����
	bool bDrop;


protected:
	/*******   System   ******/

	//���� �� System ����
	virtual void NativeConstruct() override;

private:
	/*******   Button   ******/

	//��ư Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* DtopButton;
	//��ư ���� ����
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* ButtonSound;


	/*******   SlotWeaponNum   ******/

	//���� Ŭ����
	class USlotWidget* SlotWidget;
	//���� ��ȣ
	int SlotWeaponNum;


	/*******   System   ******/

	//�÷��̾� ��Ʈ�ѷ�
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//�÷��̾�
	class APopolCharacter* PopolCharacter;
};
