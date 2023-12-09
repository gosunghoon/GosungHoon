// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CharacterStat/CharacterMainStatWidget.h"
#include "Widget/CharacterStat/CharacterStatWidget.h"

UCharacterMainStatWidget::UCharacterMainStatWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCharacterMainStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CharacterStatWidget)
	{
		//초기화 (인벤토리의 Player포인터를 채워넣어주고 초기화 함수를 실행)
		CharacterStatWidget->CharacterStatUI();
	}
}