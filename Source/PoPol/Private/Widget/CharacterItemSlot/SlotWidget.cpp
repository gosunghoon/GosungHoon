// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterItemSlot/SlotWidget.h"
#include "Character/PopolCharacter.h"
#include "Character/Type/CharacterType.h"
#include "Item/Weapon/Weapon.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/SceneComponent.h"
#include "Character/Controller/PopolPlayerController.h"
#include "GameInstance/PopolGameInstance.h"

USlotWidget::USlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
void USlotWidget::Init()
{
	SlotRefresh();
}
//Texture�� �������ִ� �Լ�
void USlotWidget::SlotSetTexture(UTexture2D* tex)
{
	if (tex == nullptr) return;
	SlotImg->SetBrushFromTexture(tex);
}
//���� �ٲ��� �Լ�
void USlotWidget::SlotRefresh()
{
	//�ν��Ͻ��� �ҷ��´�.
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//PopolPlayerController
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//���� ������ ��ȣ
	WeaponData = PopolGameInstance->GetWeaponDamageData(Slotnum);
	switch (Slotnum)
	{
	case 1:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //���� ��� �� �� ����
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture�� �̹����� �������ش�.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text�� ���� �������ش�.
		break;
	case 2:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //���� ��� �� �� ����
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture�� �̹����� �������ش�.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text�� ���� �������ش�.
		break;
	case 3:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //���� ��� �� �� ����
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture�� �̹����� �������ش�.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text�� ���� �������ش�.
		break;
	case 4:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //���� ��� �� �� ����
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture�� �̹����� �������ش�.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text�� ���� �������ش�.
		break;
	}
}
