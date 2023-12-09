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


	//����
	void StartShopWIdget(UImage* image, UTexture2D* tex, UTextBlock* PriceBlock, int16 PriceText , UTextBlock* shameBlock,int16 tshameText);

	//���� �� ������ Max�� ���
	void StartShopWIdgetMaxLevel(int ShopLevel, UImage* image, UTextBlock* MaxLevelText);

	//��ư Ŭ�� �� �켱 ����
	void PlayerShopButtonStart(int16 ShopGold, int32 PlayerGold ,float product, float productTarget);


	/*******   Image   ******/

	//Texture2D -> Image ��ȯ
	void SlotSetTexture(UImage* image, UTexture2D* tex);

	/*******   Text   ******/

	//���� ����
	void SetpriceText(UTextBlock* Block, int16 Text);
	//��ġ ����
	void SetshameText(UTextBlock* Block, int16 Text);
	//�÷��̾� �� �ʱ�ȭ
	UFUNCTION()
	void SetGoldText(int32 PlayerGold);

	/*******   Slot   ******/

	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMax = 5, UIMin = 0))
	int Slotnum;


	/*******   Button   ******/

	//���� �� �ʱ�ȭ
	void InitShopSLot();
	//���ݷ� ���� ��ư
	UFUNCTION()
	void SetAttackShopSlot();
	//���� ���� ��ư
	UFUNCTION()
	void SetDefenseShopSlot();
	//�ִ� ü�� ���� ��ư
	UFUNCTION()
	void SetMaxHPShopSlot();
	//�ִ� ���¹̳� ���� ��ư
	UFUNCTION()
	void SetMaxStaminaShopSlot();
	//���� ȸ���� ���� ��ư
	UFUNCTION()
	void SetPotionShopSlot();
	//������ ��ư
	UFUNCTION()
	void ShopSlotExitButton();

	//��ư ���� ����
	UFUNCTION()
	void PlayButtonSound();

protected:
	/*******   System   ******/

	//���� �� Widget ����
	virtual void NativeConstruct() override;


private:
	/*******   	System  ******/

	UPROPERTY()
	class UPopolGameInstance* PopolGameInstance;	//GameInstance
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;	//��Ʈ�ѷ�

	
	int AttackNum;
	int MaxHPNum;
	int MaxDefenseNum;
	int MaxStaminaNum;
	int PotionNum;

	/*******   	Widget  ******/

	class UPlayerWidget* PlayerWidget;


	/*******   Image   ******/

	//���ݷ� �̹���
	UPROPERTY(meta = (BindWidget))
	UImage* AttackSlotImg;
	//���� �̹���
	UPROPERTY(meta = (BindWidget))
	UImage* DefenseSlotImg;
	//�ִ� ü�� �̹���
	UPROPERTY(meta = (BindWidget))
	UImage* MaxHPSlotImg;
	//�ִ� ���¹̳� �̹���
	UPROPERTY(meta = (BindWidget))
	UImage* MaxStaminaSlotImg;
	//���� �̹���
	UPROPERTY(meta = (BindWidget))
	UImage* PotionSlotImg;


	/*******   Button   ******/

	//Attack Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	UButton* AttackUPButton;
	//Attack Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	UButton* DefenseUPButton;
	//Attack Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	UButton* MaxHPUPButton;
	//Attack Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	UButton* MaxStaminaUPButton;
	//Attack Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	UButton* PotionUPButton;
	//SlotExit Button Ŭ����
	UPROPERTY(meta = (BindWidget))
	class UButton* SlotExitButton;


	/*******   Text   ******/

	//���ݷ� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackpriceText;
	//���ݷ� ��ġ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackShameText;
	//�÷��̾� �ִ� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxAttackLevelText;

	//���� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefensepriceText;
	//���� ��ġ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefenseShameText;
	//�÷��̾� �ִ� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxDefenseLevelText;

	//�ִ� ü�� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHPUPpriceText;
	//�ִ� ü�� ��ġ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHPUPShameText;
	//�÷��̾� �ִ� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxMaxHPLevelText;

	//���¹̳� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStaminaUPpriceText;
	//���¹̳� ��ġ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStaminaUPShameText;
	//�÷��̾� �ִ� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxMaxStaminaLevelText;

	//���� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionpriceText;
	//���� ��ġ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionShameText;
	//�÷��̾� �ִ� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxPotionLevelText;
	//�÷��̾� ���� ��� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldText;
	//�÷��̾� ���ݷ� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerAttackText;
	//�÷��̾� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerDefenseText;
	//�÷��̾� �ִ� ü�� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerMaxHPText;
	//�÷��̾� �ִ� ���¹̳� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerMaxStaminaText;
	//�÷��̾� ���� �� �ؽ�Ʈ
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

	//��ư ���� ����
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* ButtonSound;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterMoveType CharacterMoveType;						//������ ���� ����
};
