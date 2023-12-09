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
//�ý��� ���� �� System
void APopolPlayerState::BeginPlay()
{
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));	//���� �ν��Ͻ�
	InitPlyaerLevel(PlayerLevle);							//ĳ���� ����
}

//1�� ���� Ȱ��ȭ ����
bool APopolPlayerState::SetOneWeaponEquipStateType(bool WeaponEquip)
{
	OneWeaponEquipType = WeaponEquip;
	return OneWeaponEquipType;
}
//2�� ���� Ȱ��ȭ ����
bool APopolPlayerState::SetTwoWeaponEquipStateType(bool WeaponEquip)
{
	TwoWeaponEquipType = WeaponEquip;
	return TwoWeaponEquipType;
}
//3�� ���� Ȱ��ȭ ����
bool APopolPlayerState::SetThreeWeaponEquipStateType(bool WeaponEquip)
{
	ThreeWeaponEquipType = WeaponEquip;
	return ThreeWeaponEquipType;
}
//4�� ���� Ȱ��ȭ ����
bool APopolPlayerState::SetForeWeaponEquipStateType(bool WeaponEquip)
{
	ForeWeaponEquipType = WeaponEquip;
	return ForeWeaponEquipType;
}
//1�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerState::GetOneWeaponEquipStateType()
{
	return OneWeaponEquipType;
}
//2�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerState::GetTwoWeaponEquipStateType()
{
	return TwoWeaponEquipType;
}
//3�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerState::GetThreeWeaponEquipStateType()
{
	return ThreeWeaponEquipType;
}
//4�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerState::GetForeWeaponEquipStateType()
{
	return ForeWeaponEquipType;
}

/*******   Level   ******/

//�÷��̾� ���� ��������
int APopolPlayerState::GetPlayerLevel()
{
	return  PlayerLevle;						//�÷��̾� ����(��)
}
//�÷��̾� ���� �ʱ�ȭ
void APopolPlayerState::InitPlyaerLevel(int Level)
{
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PlayerLevle = Level;																//�÷��̾� ����(��)
	CharacterStats = PopolGameInstance->GetCharacterStatsData(PlayerLevle);					//ĳ���� ����
}


/*******   EXP   ******/

//����ġ ȹ��
float APopolPlayerState::AddEXP(float EnemyEXP)
{
	CharacterStats->EXP = CharacterStats->EXP + EnemyEXP;
	return CharacterStats->EXP;
}


/*******   Gold   ******/

//��� ȹ��
int32 APopolPlayerState::AddGold(int32 EnemyGold)
{
	return PlayerGold = PlayerGold + EnemyGold + 7000;
}


/*******   Shop   ******/

//���ݷ� ���� Ƚ��
int APopolPlayerState::SetAttackShopNumState(int AttackNum)
{
	return AttackShopNum = AttackNum;
}
//���� ���� Ƚ��
int APopolPlayerState::SetDefenseShopNumState(int DefenseNum)
{
	return DefenseShopNum = DefenseNum;
}
//�ִ�ü�� ���� Ƚ��
int APopolPlayerState::SetMaxHPShopNumState(int MaxHPNum)
{
	return MaxHPShopNum = MaxHPNum;
}
//�ִ� ���¹̳� ���� Ƚ��
int APopolPlayerState::SetMaxStaminaShopNumState(int MaxStaminaNum)
{
	return MaxStaminaShopNum = MaxStaminaNum;
}
//���� ȸ���� ���� Ƚ��
int APopolPlayerState::SetPotionShopNumState(int PotionNum)
{
	return PotionShopNum = PotionNum;
}
//���ݷ� ���� Ƚ��
int APopolPlayerState::GetAttackShopNumState()
{
	return AttackShopNum;
}
//���� ���� Ƚ��
int APopolPlayerState::GetDefenseShopNumState()
{
	return DefenseShopNum;
}
//�ִ�ü�� ���� Ƚ��
int APopolPlayerState::GetMaxHPShopNumState()
{
	return MaxHPShopNum;
}
//�ִ� ���¹̳� ���� Ƚ��
int APopolPlayerState::GetMaxStaminaShopNumState()
{
	return MaxStaminaShopNum;
}
//���� ȸ���� ���� Ƚ��
int APopolPlayerState::GetPotionShopNumState()
{
	return PotionShopNum;
}

