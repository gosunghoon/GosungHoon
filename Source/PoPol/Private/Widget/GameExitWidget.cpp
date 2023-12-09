// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameExitWidget.h"
#include "Components/Button.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/GameStartWidget.h"

void UGameExitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어의 컨트롤러를 PopolPlayerController로 변경해준다.
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());

	GameStartWidget = CreateWidget<UGameStartWidget>(PopolPlayerController, GameStartWidgetclass);

	PopolPlayerController->bShowMouseCursor = true;

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	GameReStartButton->OnClicked.AddDynamic(this, &UGameExitWidget::OnGameRerollButtonClick);
	GameStartWidgetButton->OnClicked.AddDynamic(this, &UGameExitWidget::OnGameMainMenuButtonClick);
	GameExitButton->OnClicked.AddDynamic(this, &UGameExitWidget::OnGameExitButtonClick);
}
//게임 돌아가기 버튼
void UGameExitWidget::OnGameRerollButtonClick()
{
	if (ButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	PopolPlayerController->bShowMouseCursor = false;
	PopolPlayerController->SetPause(false);			//게임 일시정지
	RemoveFromParent();
}
//메인 메뉴 돌아가기
void UGameExitWidget::OnGameMainMenuButtonClick()
{
	if (ButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	RemoveFromParent();
	if (GameStartWidget)
	{	// 레벨 변경
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartMap"));
		GameStartWidget->AddToViewport();
	}
}
//게임 종료
void UGameExitWidget::OnGameExitButtonClick()
{
	if (ButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	// 게임 종료
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
