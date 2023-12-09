// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterMainWidget/ItemDropWidget.h"
#include "Components/Button.h"
#include "Item/Weapon/Weapon.h"
#include "Widget/CharacterItemSlot/SlotWidget.h"
#include "Character/PopolCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Controller/PopolPlayerController.h"

/*******   SlotWeaponNum   ******/

//슬롯에 들어갈 무기 번호
int UItemDropWidget::SetSlotWeaponNum(int WeaponNum, AActor* Target)
{
	PopolCharacter = Cast<APopolCharacter>(Target);
	SlotWeaponNum = WeaponNum;
	return SlotWeaponNum;
}


/*******   System   ******/

//시작 시 System 설정
void UItemDropWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//버튼
	DtopButton->OnClicked.AddDynamic(this, &UItemDropWidget::OnButtonClicked);
}


/*******   Button   ******/

//버튼 클릭
void UItemDropWidget::OnButtonClicked()
{
	//플레이어의 컨트롤러
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//버튼 사운드 시작
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
//버튼 사운드 시작
void UItemDropWidget::PlayButtonSound()
{
	if (ButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
}
