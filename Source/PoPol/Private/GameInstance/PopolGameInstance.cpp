// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PopolGameInstance.h"
#include "Character/PopolCharacter.h"
#include "Item/Weapon/Weapon.h"
#include "Item/EnemyWeapon/EnemyWeapon.h"
#include "Enemy/EnemyCharacter.h"
#include "Widget/NPCWidget/NPCShopSlotWidget.h"

UPopolGameInstance::UPopolGameInstance()
{
	/*******   Player   ******/

	//플레이어 무기 데이터
	FString WeaponDataPath = TEXT("/Game/DataTable/WeaponData.WeaponData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WeaponData(*WeaponDataPath);
	if (DT_WeaponData.Succeeded())
	{
		WeaponDataStats = DT_WeaponData.Object;
	}

	//플레이어 방패 데이터
	FString ShieldDataPath = TEXT("/Game/DataTable/ShieldData.ShieldData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ShieldData(*ShieldDataPath);
	if (DT_ShieldData.Succeeded())
	{
		ShieldDataStats = DT_ShieldData.Object;
	}

	//플레이어 스탯 데이터
	FString CharacterStatsPath = TEXT("/Game/DataTable/CharacterStats.CharacterStats");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CharacterStats(*CharacterStatsPath);
	if (DT_CharacterStats.Succeeded())
	{
		CharacterStats = DT_CharacterStats.Object;
	}


	/*******   Enemy   ******/

	//적 스탯 데이터
	FString EnemyStatsPath = TEXT("/Game/DataTable/EnemyData.EnemyData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EnemyStats(*EnemyStatsPath);
	if (DT_EnemyStats.Succeeded())
	{
		EnemyStats = DT_EnemyStats.Object;
	}

	//적 무기 데이터
	FString EnemyWeaponPath = TEXT("/Game/DataTable/EnemyWeaponData.EnemyWeaponData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EnemyWeapon(*EnemyWeaponPath);
	if (DT_EnemyWeapon.Succeeded())
	{
		EnemyWeaponStats = DT_EnemyWeapon.Object;
	}


	/*******   Shop   ******/

	//ShopSlot Data
	FString ShopSlotPath = TEXT("/Game/DataTable/ShopSlotData.ShopSlotData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ShopSlot(*ShopSlotPath);
	if (DT_ShopSlot.Succeeded())
	{
		ShopSlotStats = DT_ShopSlot.Object;
	}
}


/*******   Player   ******/

//Character Stats 데이터 테이블
FCharacterStats* UPopolGameInstance::GetCharacterStatsData(int32 Row)
{
	return CharacterStats->FindRow<FCharacterStats>(*FString::FromInt(Row), TEXT(""));
}
//Character weapon 데이터 테이블
FWeaponData* UPopolGameInstance::GetWeaponDamageData(int32 Row)
{
	return WeaponDataStats->FindRow<FWeaponData>(*FString::FromInt(Row), TEXT(""));
}
//Character Shield 데이터 테이블
FShieldData* UPopolGameInstance::GetShieldDefenseData(int32 Row)
{
	return ShieldDataStats->FindRow<FShieldData>(*FString::FromInt(Row), TEXT(""));
}


/*******   Enemy   ******/

//적 스탯 데이터
//Enemy Stats 데이터 테이블
FEnemyStats* UPopolGameInstance::GetEnemyStatsData(int32 Row)
{
	return EnemyStats->FindRow<FEnemyStats>(*FString::FromInt(Row), TEXT(""));
}
//Enemy weapon 데이터 테이블
FEnemyWeaponData* UPopolGameInstance::GetEnemyWeaponData(int32 Row)
{
	return EnemyWeaponStats->FindRow<FEnemyWeaponData>(*FString::FromInt(Row), TEXT(""));
}


/*******   Shop   ******/

//Shop Slot 데이터 테이블
FShopSlot* UPopolGameInstance::GetShopSlotData(int32 Row)
{
	return ShopSlotStats->FindRow<FShopSlot>(*FString::FromInt(Row), TEXT(""));
}
