// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPCWidget/NPCShopSlotWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameInstance/PopolGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Character/PopolCharacter.h"
#include "GameInstance/PopolGameInstance.h"
#include "Widget/CharacterMainWidget/PlayerWidget.h"


/*******   System   ******/

UNPCShopSlotWidget::UNPCShopSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
//SghopWidget 수정
void UNPCShopSlotWidget::StartShopWIdget(UImage* image, UTexture2D* tex, UTextBlock* PriceBlock, int16 PriceText, UTextBlock* shameBlock, int16 tshameText)
{
	SlotSetTexture(image, tex);		//Texture2D -> Image 변환
	SetpriceText(PriceBlock, PriceText);		//가격 변경
	SetshameText(shameBlock, tshameText);		//수치 변경
	shameBlock->SetText(FText::FromString(FString::FromInt(tshameText)));
}
//MaxLevelSlot
void UNPCShopSlotWidget::StartShopWIdgetMaxLevel(int ShopLevel, UImage* image, UTextBlock* MaxLevelText)
{
	if (ShopLevel >= 5)
	{
		image->SetColorAndOpacity(FLinearColor(.3f, .3f, .3f, .3f)); //슬롯 밝기를 낮춰준다.
		MaxLevelText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		MaxLevelText->SetVisibility(ESlateVisibility::Hidden);
	}
}
//SghopWidget 시작 시 설정
void UNPCShopSlotWidget::PlayerShopButtonStart(int16 ShopGold, int32 PlayerGold, float product, float productTarget)
{
	PopolPlayerController->SetPlayerGold_State(-ShopGold);		//돈 감소 
	PlayerWidget->SetGold(PlayerGold);	//돈 Text 초기화
	product = productTarget;	//Damage 초기화
}

void UNPCShopSlotWidget::InitShopSLot()
{

	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));	//GameInstance
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	PlayerWidget = Cast<UPlayerWidget>(PopolPlayerController->GetPlayerHUD());	//플레이어 Widget
	PlayerWidget->SetGold(PopolPlayerController->GetPlayerGoldState());	//골드값 초기화

	CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerController->GetStatePlayerLevel());	//캐릭터 스탯
	AttackShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetAttackShopNumControl());
	DefenseShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetDefenseShopNumControl());
	MaxHPShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetMaxHPShopNumControl());
	MaxStaminaShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetMaxStaminaShopNumControl());
	PotionShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetPotionShopNumControl());

	//SghopWidget 시작 시 설정
	StartShopWIdget(AttackSlotImg, AttackShopSlot->AttackDamageTexture, AttackpriceText, AttackShopSlot->Gold, AttackShameText, AttackShopSlot->AttackDamage);
	StartShopWIdget(DefenseSlotImg, DefenseShopSlot->DefenseTexture, DefensepriceText,DefenseShopSlot->Gold,DefenseShameText, DefenseShopSlot->Defense);
	StartShopWIdget(MaxHPSlotImg, MaxHPShopSlot->MaxHPTexture, MaxHPUPpriceText,MaxHPShopSlot->Gold,MaxHPUPShameText, MaxHPShopSlot->MaxHP);
	StartShopWIdget(MaxStaminaSlotImg, MaxStaminaShopSlot->MaxStaminaTexture,MaxStaminaUPpriceText, MaxStaminaShopSlot->Gold, MaxStaminaUPShameText, MaxStaminaShopSlot->MaxStamina);
	StartShopWIdget(PotionSlotImg, PotionShopSlot->PotionTexture, PotionpriceText,PotionShopSlot->Gold, PotionShameText, PotionShopSlot->Potion);


	//Widget 오픈 시 플레이어 스탯
	SetGoldText(PopolPlayerController->GetPlayerGoldState());
	SetshameText(PlayerAttackText, CharacterStats->AttackDamage);
	SetshameText(PlayerDefenseText, CharacterStats->Defense);
	SetshameText(PlayerMaxHPText, CharacterStats->MaxHP);
	SetshameText(PlayerMaxStaminaText, CharacterStats->MaxStamina);
	SetshameText(PlayerPotionText, CharacterStats->Potion);

	//MaxLevelSlot 시작 시 설정
	StartShopWIdgetMaxLevel(PopolPlayerController->GetAttackShopNumControl(), AttackSlotImg, MaxAttackLevelText);
	StartShopWIdgetMaxLevel(PopolPlayerController->GetDefenseShopNumControl(), DefenseSlotImg, MaxDefenseLevelText);
	StartShopWIdgetMaxLevel(PopolPlayerController->GetMaxHPShopNumControl(), MaxHPSlotImg, MaxMaxHPLevelText);
	StartShopWIdgetMaxLevel(PopolPlayerController->GetMaxStaminaShopNumControl(), MaxStaminaSlotImg, MaxMaxStaminaLevelText);
	StartShopWIdgetMaxLevel(PopolPlayerController->GetPotionShopNumControl(), PotionSlotImg, MaxPotionLevelText);
}

//공격력 구매 버튼
void UNPCShopSlotWidget::SetAttackShopSlot()
{
	PlayButtonSound();
	if (PopolPlayerController->GetAttackShopNumControl() >= 6)return;
	StartShopWIdgetMaxLevel(PopolPlayerController->GetAttackShopNumControl(), AttackSlotImg, MaxAttackLevelText);	//클릭 시 버튼 재설정
	//공격력을 더해준다.
	if (PopolPlayerController->GetPlayerGoldState() >= AttackShopSlot->Gold, PopolPlayerController->GetPlayerGoldState())
	{
		PlayerShopButtonStart(AttackShopSlot->Gold, PopolPlayerController->GetPlayerGoldState(), ShopAttackDamage, AttackShopSlot->AttackDamage);
		PopolPlayerController->SetPlayerAttackControll(ShopAttackDamage);	//데미지 증가
		SetshameText(PlayerAttackText, PopolPlayerController->GetPlayerAttackControll());	//데미지 텍스트 초기화
		AttackNum = PopolPlayerController->GetAttackShopNumControl() + 1;	//상점 공격력 구매 레벨 증가
		PopolPlayerController->SetAttackShopNumControl(AttackNum);	//레벨 증가
		AttackShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetAttackShopNumControl());	//증가한 레벨 값
		StartShopWIdget(AttackSlotImg, AttackShopSlot->AttackDamageTexture, AttackpriceText, AttackShopSlot->Gold, AttackShameText, AttackShopSlot->AttackDamage);//구매 후 초기화

		SetGoldText(PopolPlayerController->GetPlayerGoldState()); // 플레이어가 가진 골드 확인
	}
}
//방어력 구매 버튼
void UNPCShopSlotWidget::SetDefenseShopSlot()
{
	PlayButtonSound();
	if (PopolPlayerController->GetDefenseShopNumControl() >= 6)return;
	StartShopWIdgetMaxLevel(PopolPlayerController->GetDefenseShopNumControl(), DefenseSlotImg, MaxDefenseLevelText);	//클릭 시 버튼 재설정
	//방어력을 더해준다.
	if (PopolPlayerController->GetPlayerGoldState() >= DefenseShopSlot->Gold, PopolPlayerController->GetPlayerGoldState())
	{
		PlayerShopButtonStart(DefenseShopSlot->Gold, PopolPlayerController->GetPlayerGoldState(), ShopDefense, DefenseShopSlot->Defense);
		PopolPlayerController->SetPlayerGold_State(ShopDefense);	//방어력 증가
		SetshameText(PlayerDefenseText, PopolPlayerController->GetPlayerDefenseControll());	//방어력 텍스트 초기화
		MaxDefenseNum = PopolPlayerController->GetDefenseShopNumControl() + 1;	//상점 방어력 구매 레벨 증가
		PopolPlayerController->SetDefenseShopNumControl(MaxDefenseNum);	//레벨 증가
		DefenseShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetDefenseShopNumControl());	//증가한 레벨 값
		StartShopWIdget(DefenseSlotImg, DefenseShopSlot->DefenseTexture, DefensepriceText, DefenseShopSlot->Gold, DefenseShameText, DefenseShopSlot->Defense);//구매 후 초기화

		SetGoldText(PopolPlayerController->GetPlayerGoldState()); // 플레이어가 가진 골드 확인
	}
}
//최대 체력 구매 버튼
void UNPCShopSlotWidget::SetMaxHPShopSlot()
{
	PlayButtonSound();
	if (PopolPlayerController->GetMaxHPShopNumControl() >= 6)return;
	StartShopWIdgetMaxLevel(PopolPlayerController->GetMaxHPShopNumControl(), MaxHPSlotImg, MaxMaxHPLevelText);	//클릭 시 버튼 재설정
	//최대 체력을 더해준다.
	if (PopolPlayerController->GetPlayerGoldState() >= MaxHPShopSlot->Gold, PopolPlayerController->GetPlayerGoldState())
	{
		PlayerShopButtonStart(MaxHPShopSlot->Gold, PopolPlayerController->GetPlayerGoldState(), ShopMaxHP, MaxHPShopSlot->MaxHP);
		PopolPlayerController->SetPlayerMaxHPControll(ShopMaxHP);	//최대 체력 증가
		SetshameText(PlayerMaxHPText, PopolPlayerController->GetPlayerMaxHPControll());	//최대 체력 텍스트 초기화
		MaxHPNum = PopolPlayerController->GetMaxHPShopNumControl() + 1;	//상점 최대 체력 구매 레벨 증가
		PopolPlayerController->SetMaxHPShopNumControl(MaxHPNum);	//레벨 증가
		MaxHPShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetMaxHPShopNumControl());	//증가한 레벨 값
		StartShopWIdget(MaxHPSlotImg, MaxHPShopSlot->MaxHPTexture, MaxHPUPpriceText, MaxHPShopSlot->Gold, MaxHPUPShameText, MaxHPShopSlot->MaxHP);//구매 후 초기화

		SetGoldText(PopolPlayerController->GetPlayerGoldState()); // 플레이어가 가진 골드 확인
	}
}
//최대 스태미나 구매 버튼
void UNPCShopSlotWidget::SetMaxStaminaShopSlot()
{
	PlayButtonSound();
	if (PopolPlayerController->GetMaxStaminaShopNumControl() >= 6)return;
	StartShopWIdgetMaxLevel(PopolPlayerController->GetMaxStaminaShopNumControl(), MaxStaminaSlotImg, MaxMaxStaminaLevelText);	//클릭 시 버튼 재설정
	//스태미나를 더해준다.
	if (PopolPlayerController->GetPlayerGoldState() >= MaxStaminaShopSlot->Gold, PopolPlayerController->GetPlayerGoldState())
	{
		PlayerShopButtonStart(MaxStaminaShopSlot->Gold, PopolPlayerController->GetPlayerGoldState(), ShopMaxStamina, MaxStaminaShopSlot->MaxStamina);
		PopolPlayerController->SetPlayerMaxStaminaControll(ShopMaxStamina);	//최대 스태미나 증가
		SetshameText(PlayerMaxStaminaText, PopolPlayerController->GetPlayerMaxStaminaControll());	//최대 스태미나 텍스트 초기화
		MaxStaminaNum = PopolPlayerController->GetMaxStaminaShopNumControl() + 1;	//상점 스태미나 구매 레벨 증가
		PopolPlayerController->SetMaxStaminaShopNumControl(MaxStaminaNum);	//레벨 증가
		MaxStaminaShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetMaxStaminaShopNumControl());	//증가한 레벨 값
		StartShopWIdget(MaxStaminaSlotImg, MaxStaminaShopSlot->MaxStaminaTexture, MaxStaminaUPpriceText, MaxStaminaShopSlot->Gold, MaxStaminaUPShameText, MaxStaminaShopSlot->MaxStamina);//구매 후 초기화

		SetGoldText(PopolPlayerController->GetPlayerGoldState()); // 플레이어가 가진 골드 확인
	}
}
//포션 회복량 구매 버튼
void UNPCShopSlotWidget::SetPotionShopSlot()
{
	PlayButtonSound();
	if (PopolPlayerController->GetPotionShopNumControl() >= 6)return;
	StartShopWIdgetMaxLevel(PopolPlayerController->GetPotionShopNumControl(), PotionSlotImg, MaxPotionLevelText);	//클릭 시 버튼 재설정
	//포션 회복량을 더해준다.
	if (PopolPlayerController->GetPlayerGoldState() >= PotionShopSlot->Gold, PopolPlayerController->GetPlayerGoldState())
	{
		PlayerShopButtonStart(PotionShopSlot->Gold, PopolPlayerController->GetPlayerGoldState(), ShopPotion, PotionShopSlot->Potion);
		PopolPlayerController->SetPlayerPotionControll(ShopPotion);	//회복량 증가
		SetshameText(PlayerPotionText, PopolPlayerController->GetPlayerPotionControll());	//회복량 텍스트 초기화
		PotionNum = PopolPlayerController->GetPotionShopNumControl() + 1;	//상점 회복량 구매 레벨 증가
		PopolPlayerController->SetPotionShopNumControl(PotionNum);	//레벨 증가
		PotionShopSlot = PopolGameInstance->GetShopSlotData(PopolPlayerController->GetPotionShopNumControl());	//증가한 레벨 값
		StartShopWIdget(PotionSlotImg, PotionShopSlot->PotionTexture, PotionpriceText, PotionShopSlot->Gold, PotionShameText, PotionShopSlot->Potion);//구매 후 초기화

		SetGoldText(PopolPlayerController->GetPlayerGoldState()); // 플레이어가 가진 골드 확인
	}
}
//나가기 버튼
void UNPCShopSlotWidget::ShopSlotExitButton()
{
	PlayButtonSound();
	PopolPlayerController->SetPause(false);
	RemoveFromParent();
	PopolPlayerController->bShowMouseCursor = false;
}
//버튼 사운드 시작
void UNPCShopSlotWidget::PlayButtonSound()
{
	if (ButtonSound)
	{
		//��ü �Ҹ��� ���� ����ϴ� �Լ�
		UGameplayStatics::PlaySound2D(this, ButtonSound, 2.5f);
	}
}
//시작 시 Widget 설정
void UNPCShopSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AttackUPButton->OnClicked.AddDynamic(this, &UNPCShopSlotWidget::SetAttackShopSlot);

	DefenseUPButton->OnClicked.AddDynamic(this, &UNPCShopSlotWidget::SetDefenseShopSlot);

	MaxHPUPButton->OnClicked.AddDynamic(this, &UNPCShopSlotWidget::SetMaxHPShopSlot);

	MaxStaminaUPButton->OnClicked.AddDynamic(this, &UNPCShopSlotWidget::SetMaxStaminaShopSlot);

	PotionUPButton->OnClicked.AddDynamic(this, &UNPCShopSlotWidget::SetPotionShopSlot); 

	SlotExitButton->OnClicked.AddDynamic(this, &UNPCShopSlotWidget::ShopSlotExitButton);
	InitShopSLot();

	//CharacterMoveType = ECharacterMoveType::ECM_Attack;
}
//가격 변경
void UNPCShopSlotWidget::SetpriceText(UTextBlock* Block, int16 Text)
{
	Block->SetText(FText::FromString(FString::FromInt(Text)));
}
//수치 변경
void UNPCShopSlotWidget::SetshameText(UTextBlock* Block, int16 Text)
{
	Block->SetText(FText::FromString(FString::FromInt(Text)));
}
//Texture2D -> Image 변환
void UNPCShopSlotWidget::SlotSetTexture(UImage* image, UTexture2D* tex)
{
	if (tex == nullptr) return;
	image->SetBrushFromTexture(tex);
}
//상점에서 플레이어 돈 초기화
void UNPCShopSlotWidget::SetGoldText(int32 PlayerGold)
{
	GoldText->SetText(FText::FromString(FString::FromInt(PlayerGold)));
}