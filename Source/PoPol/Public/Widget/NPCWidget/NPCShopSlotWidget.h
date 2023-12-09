// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Character/Type/CharacterType.h"
#include "NPCShopSlotWidget.generated.h"


USTRUCT(BlueprintType)
struct FShopSlot : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FShopSlot()
		: MaxHP(50), MaxStamina(50),
		AttackDamage(0), Defense(20), Gold(0)
	{};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Potion;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* MaxHPTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* MaxStaminaTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* AttackDamageTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* DefenseTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* PotionTexture;
};


class UTextBlock;
class UImage;
class UButton;


/**
 * 
 */
UCLASS()
class POPOL_API UNPCShopSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UNPCShopSlotWidget(const FObjectInitializer& ObjectInitializer);


	//시작
	void StartShopWIdget(UImage* image, UTexture2D* tex, UTextBlock* PriceBlock, int16 PriceText , UTextBlock* shameBlock,int16 tshameText);

	//상점 별 레벨이 Max일 경우
	void StartShopWIdgetMaxLevel(int ShopLevel, UImage* image, UTextBlock* MaxLevelText);

	//버튼 클릭 시 우선 적용
	void PlayerShopButtonStart(int16 ShopGold, int32 PlayerGold ,float product, float productTarget);


	/*******   Image   ******/

	//Texture2D -> Image 변환
	void SlotSetTexture(UImage* image, UTexture2D* tex);

	/*******   Text   ******/

	//가격 변경
	void SetpriceText(UTextBlock* Block, int16 Text);
	//수치 변경
	void SetshameText(UTextBlock* Block, int16 Text);
	//플레이어 돈 초기화
	UFUNCTION()
	void SetGoldText(int32 PlayerGold);

	/*******   Slot   ******/

	//슬롯 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMax = 5, UIMin = 0))
	int Slotnum;


	/*******   Button   ******/

	//시작 시 초기화
	void InitShopSLot();
	//공격력 구매 버튼
	UFUNCTION()
	void SetAttackShopSlot();
	//방어력 구매 버튼
	UFUNCTION()
	void SetDefenseShopSlot();
	//최대 체력 구매 버튼
	UFUNCTION()
	void SetMaxHPShopSlot();
	//최대 스태미나 구매 버튼
	UFUNCTION()
	void SetMaxStaminaShopSlot();
	//포션 회복량 구매 버튼
	UFUNCTION()
	void SetPotionShopSlot();
	//나가기 버튼
	UFUNCTION()
	void ShopSlotExitButton();

	//버튼 사운드 시작
	UFUNCTION()
	void PlayButtonSound();

protected:
	/*******   System   ******/

	//시작 시 Widget 설정
	virtual void NativeConstruct() override;


private:
	/*******   	System  ******/

	UPROPERTY()
	class UPopolGameInstance* PopolGameInstance;	//GameInstance
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;	//컨트롤러

	
	int AttackNum;
	int MaxHPNum;
	int MaxDefenseNum;
	int MaxStaminaNum;
	int PotionNum;

	/*******   	Widget  ******/

	class UPlayerWidget* PlayerWidget;


	/*******   Image   ******/

	//공격력 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* AttackSlotImg;
	//방어력 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* DefenseSlotImg;
	//최대 체력 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* MaxHPSlotImg;
	//최대 스태미나 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* MaxStaminaSlotImg;
	//물약 이미지
	UPROPERTY(meta = (BindWidget))
	UImage* PotionSlotImg;


	/*******   Button   ******/

	//Attack Button 클래스
	UPROPERTY(meta = (BindWidget))
	UButton* AttackUPButton;
	//Attack Button 클래스
	UPROPERTY(meta = (BindWidget))
	UButton* DefenseUPButton;
	//Attack Button 클래스
	UPROPERTY(meta = (BindWidget))
	UButton* MaxHPUPButton;
	//Attack Button 클래스
	UPROPERTY(meta = (BindWidget))
	UButton* MaxStaminaUPButton;
	//Attack Button 클래스
	UPROPERTY(meta = (BindWidget))
	UButton* PotionUPButton;
	//SlotExit Button 클래스
	UPROPERTY(meta = (BindWidget))
	class UButton* SlotExitButton;


	/*******   Text   ******/

	//공격력 가격 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackpriceText;
	//공격력 수치 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackShameText;
	//플레이어 최대 레벨 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxAttackLevelText;

	//방어력 가격 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefensepriceText;
	//방어력 수치 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefenseShameText;
	//플레이어 최대 레벨 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxDefenseLevelText;

	//최대 체력 가격 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHPUPpriceText;
	//최대 체력 수치 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHPUPShameText;
	//플레이어 최대 레벨 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxMaxHPLevelText;

	//스태미나 가격 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStaminaUPpriceText;
	//스태미나 수치 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStaminaUPShameText;
	//플레이어 최대 레벨 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxMaxStaminaLevelText;

	//포션 가격 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionpriceText;
	//포션 수치 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionShameText;
	//플레이어 최대 레벨 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxPotionLevelText;
	//플레이어 소지 골드 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldText;
	//플레이어 공격력 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerAttackText;
	//플레이어 방어력 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerDefenseText;
	//플레이어 최대 체력 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerMaxHPText;
	//플레이어 최대 스태미나 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerMaxStaminaText;
	//플레이어 포션 량 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerPotionText;

	/*******   Data   ******/

	struct FShopSlot* AttackShopSlot;
	struct FShopSlot* DefenseShopSlot;
	struct FShopSlot* MaxHPShopSlot;
	struct FShopSlot* MaxStaminaShopSlot;
	struct FShopSlot* PotionShopSlot;
	struct FCharacterStats* CharacterStats;

	float ShopAttackDamage;
	float ShopDefense;
	float ShopMaxHP;
	float ShopMaxStamina;
	int ShopPotion;

	int32 GoldMinus;

	//버튼 사운드 생성
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* ButtonSound;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterMoveType CharacterMoveType;						//움직임 상태 여부
};
