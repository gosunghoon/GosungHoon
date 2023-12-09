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

	//플레이어 무기 데이터
	//Character Stats 데이터 테이블
	FCharacterStats* GetCharacterStatsData(int32 Row);
	//Character weapon 데이터 테이블
	FWeaponData* GetWeaponDamageData(int32 Row);
	//Character Shield 데이터 테이블
	FShieldData* GetShieldDefenseData(int32 Row);

	/*******   Enemy   ******/

	//적 스탯 데이터
	//Enemy Stats 데이터 테이블
	FEnemyStats* GetEnemyStatsData(int32 Row);
	//Enemy weapon 데이터 테이블
	FEnemyWeaponData* GetEnemyWeaponData(int32 Row);

	/*******   Shop   ******/

	//Shop Slot 데이터 테이블
	FShopSlot* GetShopSlotData(int32 Row);

private:

	/*******   Player   ******/

	//플레이어 무기 데이터
	UPROPERTY()
	UDataTable* WeaponDataStats;	//플레이어 무기 데이터 테이블
	UPROPERTY()
	UDataTable* ShieldDataStats;	//플레이어 무기 데이터 테이블
	UPROPERTY()
	UDataTable* CharacterStats;		//캐릭터 스탯


	/*******   Enemy   ******/

	//적 스탯 데이터
	UPROPERTY()
	UDataTable* EnemyStats;			//적 스탯
	UPROPERTY()
	UDataTable* EnemyWeaponStats;	//적 무기 테이블

	/*******   Shop   ******/

	UPROPERTY()
	UDataTable* ShopSlotStats;	//ShopSlot Data
};
