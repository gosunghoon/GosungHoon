// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterMainWidget/ItemDropWidget.h"
#include "Components/Button.h"
#include "Item/Weapon/Weapon.h"
#include "Widget/CharacterItemSlot/SlotWidget.h"
#include "Character/PopolCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Controller/PopolPlayerController.h"

/*******   SlotWeaponNum   ******/

//���Կ� �� ���� ��ȣ
int UItemDropWidget::SetSlotWeaponNum(int WeaponNum, AActor* Target)
{
	PopolCharacter = Cast<APopolCharacter>(Target);
	SlotWeaponNum = WeaponNum;
	return SlotWeaponNum;
}


/*******   System   ******/

//���� �� System ����
void UItemDropWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//��ư
	DtopButton->OnClicked.AddDynamic(this, &UItemDropWidget::OnButtonClicked);
}


/*******   Button   ******/

//��ư Ŭ��
void UItemDropWidget::OnButtonClicked()
{
	//�÷��̾��� ��Ʈ�ѷ�
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//��ư ���� ����
	PlayButtonSound();
	switch (SlotWeaponNum)
	{
	case 1:
		PopolPlayerController->SetEqipWeaponNum(SlotWeaponNum);
		PopolCharacter->SetbDrop(true);
		PopolPlayerController->SetOneWeaponEquipControllType(true);
		break;
	case 2:
		PopolPlayerController->SetEqipWeaponNum(SlotWeaponNum);
		PopolCharacter->SetbDrop(true);
		PopolPlayerController->SetOneWeaponEquipControllType(true);
		break;
	case 3:
		PopolPlayerController->SetEqipWeaponNum(SlotWeaponNum);
		PopolCharacter->SetbDrop(true);
		PopolPlayerController->SetOneWeaponEquipControllType(true);
		break;
	case 4:
		PopolPlayerController->SetEqipWeaponNum(SlotWeaponNum);
		PopolCharacter->SetbDrop(true);
		PopolPlayerController->SetOneWeaponEquipControllType(true);
		break;
	}
	RemoveFromParent();
}
//��ư ���� ����
void UItemDropWidget::PlayButtonSound()
{
	if (ButtonSound)
	{
		// ��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
}
