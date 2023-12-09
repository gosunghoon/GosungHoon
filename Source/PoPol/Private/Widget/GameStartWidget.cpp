// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameStartWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Controller/PopolPlayerController.h"

//시작 시 System 설정
void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어의 컨트롤러를 PopolPlayerController로 변경해준다.
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	GameStartButton->OnClicked.AddDynamic(this, &UGameStartWidget::OnGameStartButtonClick);
	GameExitButton->OnClicked.AddDynamic(this, &UGameStartWidget::OnGameExitButtonClick);

	//PopolPlayerController->bShowMouseCursor = true;
}
//게임 시작 버튼
void UGameStartWidget::OnGameStartButtonClick()
{
	if (ButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	// 레벨 변경
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Test"));
}
//게임 종료 버튼
void UGameStartWidget::OnGameExitButtonClick()
{
	if (ButtonSound)
	{
		// 전체 소리로 사운드 재생하는 함수
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
	// 게임 종료
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
