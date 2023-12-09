// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterItemSlot/SlotInvenWidget.h"
#include "Character/PopolCharacter.h"
#include "Character/Type/CharacterType.h"
#include "Widget/CharacterItemSlot/SlotWidget.h"
#include "GameInstance/PopolGameInstance.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"

USlotInvenWidget::USlotInvenWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void USlotInvenWidget::Init()
{
	SlotWidget.Init(nullptr, 5);

	TArray<UWidget*> widgets;

	WidgetTree->GetAllWidgets(widgets);	//WidgetTree

	USlotWidget* slot = nullptr;

	for (auto widget : widgets)
	{
		slot = Cast<USlotWidget>(widget);

		if (!slot) continue;

		slot->Init();
	}
}
