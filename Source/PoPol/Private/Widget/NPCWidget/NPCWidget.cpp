// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPCWidget/NPCWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Widget/NPCWidget/NPCShopSlotWidget.h"

/*******   Button   ******/

//Story버튼 클릭
void UNPCWidget::OnStoryButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("PopolPlayerController->GetEnemyGruxDeath() : %d"), PopolPlayerController->GetEnemyGruxDeath());
	PlayButtonSound();
	if (PopolPlayerController->GetEnemyGruxDeath() == 1)
	{
		SetNPCText(TEXT("감사합니다. 덕분에 이제 사업을 진행할 수 있겠어요."));
		StorySkipButton->SetVisibility(ESlateVisibility::Hidden);
		StoryButton->SetVisibility(ESlateVisibility::Visible);
		ShopButton->SetVisibility(ESlateVisibility::Visible);
		ExitButton->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	else
	{
		StoryButton->SetVisibility(ESlateVisibility::Hidden);
		StorySkipButton->SetVisibility(ESlateVisibility::Visible);
		ShopButton->SetVisibility(ESlateVisibility::Hidden);
		ExitButton->SetVisibility(ESlateVisibility::Hidden);
		SetNPCText(TEXT("제발 살려주세요"));
	}
}
//Story Skip버튼 클릭
void UNPCWidget::OnStorySkipButtonClicked()
{
	PlayButtonSound();
	TextNum += 1;
	switch (TextNum)
	{
	case 1:
		SetNPCText(TEXT("Grux라는 괴물에 의해 강가의 사업을 못하고 있습니다."));
		break;
	case 2:
		SetNPCText(TEXT("가능하다면 그 Grux라는 괴물을 잡아주셨으면 합니다."));
		break;
	case 3:
		SetNPCText(TEXT("제가 강해지도록 만들어 드리겠습니다.!!!!"));
		break;
	case 4:
		SetNPCText(TEXT("아!, 당연한 소리지만 돈을 주셔야 강해지도록 만들 수 있습니다."));
		break;
	case 5:
		SetNPCText(TEXT("하지만 무기가 없으시군요... 하지만 저기 정면에 보이는 나무 뒤에"));
		break;
	case 6:
		SetNPCText(TEXT("제가 무기를 하나 숨겨 놨습니다."));
		break;
	case 7:
		SetNPCText(TEXT("그리고 Grux의 부하들이 지키고 있는 검들로 더욱 더 강해지도록 해주세요!!!"));
		StorySkipButton->SetVisibility(ESlateVisibility::Hidden);
		StoryButton->SetVisibility(ESlateVisibility::Visible);
		ShopButton->SetVisibility(ESlateVisibility::Visible);
		ExitButton->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	if (TextNum == 7)
	{
		SetNPCText(TEXT("돈만주면 강해지게 해줄게!!"));
		TextNum = 0;
	}
}
//Shop버튼 클릭
void UNPCWidget::OnShopButtonClicked()
{
	PlayButtonSound();
	//Button Widget
	NPCShopSlotWidget = CreateWidget<UNPCShopSlotWidget>(PopolPlayerController, NPCShopSlotWidgetClass);
	if (NPCShopSlotWidget)
	{
		NPCShopSlotWidget->AddToViewport();
	}
	RemoveFromParent();
}
//Exit버튼 클릭
void UNPCWidget::OnEixtButtonClicked()
{
	PlayButtonSound();
	RemoveFromParent();
	PopolPlayerController->bShowMouseCursor = false;
	PopolPlayerController->SetPause(false);
}
//버튼 사운드 시작
void UNPCWidget::PlayButtonSound()
{
	if (ButtonSound)
	{
		//��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
}
//대화 내용 Text로 변경
void UNPCWidget::SetNPCText(FString NPCText)
{
	NPCConversation->SetText(FText::FromString(NPCText));
}


/*******   System   ******/

//���� �� System ����
void UNPCWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//�÷��̾��� ��Ʈ�ѷ�
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//���� ���� ����
	StorySkipButton->SetVisibility(ESlateVisibility::Hidden);
	TextNum = 0;
	//���丮 ��ư
	StoryButton->OnClicked.AddDynamic(this, &UNPCWidget::OnStoryButtonClicked);
	//���丮 �ѱ�� ��ư
	StorySkipButton->OnClicked.AddDynamic(this, &UNPCWidget::OnStorySkipButtonClicked);
	//���� ��ư
	ShopButton->OnClicked.AddDynamic(this, &UNPCWidget::OnShopButtonClicked);
	//������ ��ư
	ExitButton->OnClicked.AddDynamic(this, &UNPCWidget::OnEixtButtonClicked);
	//���� ���
	SetNPCText(TEXT("돈만주면 강해지게 해줄게!!"));
	PopolPlayerController->bShowMouseCursor = true;

	PopolPlayerController->SetPause(true);
}
