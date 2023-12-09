// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/State/PopolPlayerState.h"
#include "Character/PopolCharacter.h"
#include "GameInstance/PopolGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Item/Weapon/Weapon.h"


/*******   System   ******/

//Main
APopolPlayerState::APopolPlayerState()
{
	PlayerLevle = 1;
}
//시스템 시작 시 System
void APopolPlayerState::BeginPlay()
{
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));	//게임 인스턴스
	InitPlyaerLevel(PlayerLevle);							//캐릭터 스탯
}

//1번 무기 활성화 여부
bool APopolPlayerState::SetOneWeaponEquipStateType(bool WeaponEquip)
{
	OneWeaponEquipType = WeaponEquip;
	return OneWeaponEquipType;
}
//2번 무기 활성화 여부
bool APopolPlayerState::SetTwoWeaponEquipStateType(bool WeaponEquip)
{
	TwoWeaponEquipType = WeaponEquip;
	return TwoWeaponEquipType;
}
//3번 무기 활성화 여부
bool APopolPlayerState::SetThreeWeaponEquipStateType(bool WeaponEquip)
{
	ThreeWeaponEquipType = WeaponEquip;
	return ThreeWeaponEquipType;
}
//4번 무기 활성화 여부
bool APopolPlayerState::SetForeWeaponEquipStateType(bool WeaponEquip)
{
	ForeWeaponEquipType = WeaponEquip;
	return ForeWeaponEquipType;
}
//1번 무기 활성화 여부 전달하기
bool APopolPlayerState::GetOneWeaponEquipStateType()
{
	return OneWeaponEquipType;
}
//2번 무기 활성화 여부 전달하기
bool APopolPlayerState::GetTwoWeaponEquipStateType()
{
	return TwoWeaponEquipType;
}
//3번 무기 활성화 여부 전달하기
bool APopolPlayerState::GetThreeWeaponEquipStateType()
{
	return ThreeWeaponEquipType;
}
//4번 무기 활성화 여부 전달하기
bool APopolPlayerState::GetForeWeaponEquipStateType()
{
	return ForeWeaponEquipType;
}

/*******   Level   ******/

//플레이얼 레벨 가져오기
int APopolPlayerState::GetPlayerLevel()
{
	return  PlayerLevle;						//플레이어 레벨(행)
}
//플레이어 레벨 초기화
void APopolPlayerState::InitPlyaerLevel(int Level)
{
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PlayerLevle = Level;																//플레이어 레벨(행)
	CharacterStats = PopolGameInstance->GetCharacterStatsData(PlayerLevle);					//캐릭터 스탯
}


/*******   EXP   ******/

//경험치 획득
float APopolPlayerState::AddEXP(float EnemyEXP)
{
	CharacterStats->EXP = CharacterStats->EXP + EnemyEXP;
	return CharacterStats->EXP;
}


/*******   Gold   ******/

//골드 획득
int32 APopolPlayerState::AddGold(int32 EnemyGold)
{
	return PlayerGold = PlayerGold + EnemyGold + 7000;
}


/*******   Shop   ******/

//공격력 상점 횟수
int APopolPlayerState::SetAttackShopNumState(int AttackNum)
{
	return AttackShopNum = AttackNum;
}
//방어력 상점 횟수
int APopolPlayerState::SetDefenseShopNumState(int DefenseNum)
{
	return DefenseShopNum = DefenseNum;
}
//최대체력 상점 횟수
int APopolPlayerState::SetMaxHPShopNumState(int MaxHPNum)
{
	return MaxHPShopNum = MaxHPNum;
}
//최대 스태미나 상점 횟수
int APopolPlayerState::SetMaxStaminaShopNumState(int MaxStaminaNum)
{
	return MaxStaminaShopNum = MaxStaminaNum;
}
//포션 회복량 상점 횟수
int APopolPlayerState::SetPotionShopNumState(int PotionNum)
{
	return PotionShopNum = PotionNum;
}
//공격력 상점 횟수
int APopolPlayerState::GetAttackShopNumState()
{
	return AttackShopNum;
}
//방어력 상점 횟수
int APopolPlayerState::GetDefenseShopNumState()
{
	return DefenseShopNum;
}
//최대체력 상점 횟수
int APopolPlayerState::GetMaxHPShopNumState()
{
	return MaxHPShopNum;
}
//최대 스태미나 상점 횟수
int APopolPlayerState::GetMaxStaminaShopNumState()
{
	return MaxStaminaShopNum;
}
//포션 회복량 상점 횟수
int APopolPlayerState::GetPotionShopNumState()
{
	return PotionShopNum;
}

