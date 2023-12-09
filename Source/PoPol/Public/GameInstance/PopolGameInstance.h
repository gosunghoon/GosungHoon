// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Enemy/EnemyCharacter.h"
#include "PopolGameInstance.generated.h"

struct FWeaponData;
struct FCharacterStats;
struct FEnemyStats;
struct FEnemyWeaponData;
struct FShieldData;
struct FShopSlot;
class UDataTable;

/**
 * 
 */
UCLASS()
class POPOL_API UPopolGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPopolGameInstance();


	/*******   Player   ******/

	//�÷��̾� ���� ������
	//Character Stats ������ ���̺�
	FCharacterStats* GetCharacterStatsData(int32 Row);
	//Character weapon ������ ���̺�
	FWeaponData* GetWeaponDamageData(int32 Row);
	//Character Shield ������ ���̺�
	FShieldData* GetShieldDefenseData(int32 Row);

	/*******   Enemy   ******/

	//�� ���� ������
	//Enemy Stats ������ ���̺�
	FEnemyStats* GetEnemyStatsData(int32 Row);
	//Enemy weapon ������ ���̺�
	FEnemyWeaponData* GetEnemyWeaponData(int32 Row);

	/*******   Shop   ******/

	//Shop Slot ������ ���̺�
	FShopSlot* GetShopSlotData(int32 Row);

private:

	/*******   Player   ******/

	//�÷��̾� ���� ������
	UPROPERTY()
	UDataTable* WeaponDataStats;	//�÷��̾� ���� ������ ���̺�
	UPROPERTY()
	UDataTable* ShieldDataStats;	//�÷��̾� ���� ������ ���̺�
	UPROPERTY()
	UDataTable* CharacterStats;		//ĳ���� ����


	/*******   Enemy   ******/

	//�� ���� ������
	UPROPERTY()
	UDataTable* EnemyStats;			//�� ����
	UPROPERTY()
	UDataTable* EnemyWeaponStats;	//�� ���� ���̺�

	/*******   Shop   ******/

	UPROPERTY()
	UDataTable* ShopSlotStats;	//ShopSlot Data
};
