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
//Texture을 변경해주는 함수
void USlotWidget::SlotSetTexture(UTexture2D* tex)
{
	if (tex == nullptr) return;
	SlotImg->SetBrushFromTexture(tex);
}
//새로 바꿔줄 함수
void USlotWidget::SlotRefresh()
{
	//인스턴스를 불러온다.
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//PopolPlayerController
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//무기 데이터 번호
	WeaponData = PopolGameInstance->GetWeaponDamageData(Slotnum);
	switch (Slotnum)
	{
	case 1:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //무기 드랍 시 색 변경
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture를 이미지를 변경해준다.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text의 값을 변경해준다.
		break;
	case 2:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //무기 드랍 시 색 변경
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture를 이미지를 변경해준다.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text의 값을 변경해준다.
		break;
	case 3:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //무기 드랍 시 색 변경
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture를 이미지를 변경해준다.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text의 값을 변경해준다.
		break;
	case 4:
		if (PopolPlayerController->GetEqipWeaponNum() == Slotnum)
		{
			SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f)); //무기 드랍 시 색 변경
		}
		SlotSetTexture(WeaponData->Texture);										//2DTexture를 이미지를 변경해준다.
		SlotText->SetText(FText::FromString(FString::FromInt(Slotnum)));			//Text의 값을 변경해준다.
		break;
	}
}
