// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PopolPlayerState.generated.h"

UCLASS()
class POPOL_API APopolPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	/*******   System   ******/

	//Main
	APopolPlayerState();

	//1�� ���� Ȱ��ȭ ����
	bool SetOneWeaponEquipStateType(bool WeaponEquip);
	//2�� ���� Ȱ��ȭ ����
	bool SetTwoWeaponEquipStateType(bool WeaponEquip);
	//3�� ���� Ȱ��ȭ ����
	bool SetThreeWeaponEquipStateType(bool WeaponEquip);
	//4�� ���� Ȱ��ȭ ����
	bool SetForeWeaponEquipStateType(bool WeaponEquip);

	//1�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetOneWeaponEquipStateType();
	//2�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetTwoWeaponEquipStateType();
	//3�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetThreeWeaponEquipStateType();
	//4�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetForeWeaponEquipStateType();


	/*******   Level   ******/

	//�÷��̾� ���� ��������
	int GetPlayerLevel();
	//�÷��̾� ���� �ʱ�ȭ
	void InitPlyaerLevel(int Level);


	/*******   EXP   ******/

	//����ġ ȹ��
	float AddEXP(float EnemyEXP);

	/*******   Gold   ******/

	//��� ȹ��
	int32 AddGold(int32 EnemyGold);
	int32 PlayerGold;

	/*******   Shop   ******/

	//���ݷ� ���� Ƚ��
	int SetAttackShopNumState(int AttackNum);
	//���� ���� Ƚ��
	int SetDefenseShopNumState(int DefenseNum);
	//�ִ�ü�� ���� Ƚ��
	int SetMaxHPShopNumState(int MaxHPNum);
	//�ִ� ���¹̳� ���� Ƚ��
	int SetMaxStaminaShopNumState(int MaxStaminaNum);
	//���� ȸ���� ���� Ƚ��
	int SetPotionShopNumState(int PotionNum);

	//���ݷ� ���� Ƚ��
	int GetAttackShopNumState();
	//���� ���� Ƚ��
	int GetDefenseShopNumState();
	//�ִ�ü�� ���� Ƚ��
	int GetMaxHPShopNumState();
	//�ִ� ���¹̳� ���� Ƚ��
	int GetMaxStaminaShopNumState();
	//���� ȸ���� ���� Ƚ��
	int GetPotionShopNumState();


protected:
	//�ý��� ���� �� System
	virtual void BeginPlay() override;

private:
	/*******   System   ******/

	UPROPERTY()
	class UPopolGameInstance* PopolGameInstance;	//���� �ν��Ͻ�
	struct FCharacterStats* CharacterStats;			//ĳ���� ���� ����


	/*******   PlayerStats   ******/

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	int PlayerLevle;			//�÷��̾� ����(��)


	bool OneWeaponEquipType;	//1�� ���� ��� ���� ����
	bool TwoWeaponEquipType;	//2�� ���� ��� ���� ����
	bool ThreeWeaponEquipType;	//3�� ���� ��� ���� ����
	bool ForeWeaponEquipType;	//4�� ���� ��� ���� ����
	UPROPERTY(EditAnywhere, Category = Num)
	int AttackShopNum;		//���ݷ� ���� Ƚ��
	UPROPERTY(EditAnywhere, Category = Num)
	int DefenseShopNum;		//���� ���� Ƚ��	
	UPROPERTY(EditAnywhere, Category = Num)
	int MaxHPShopNum;		//�ִ�ü�� ���� Ƚ��
	UPROPERTY(EditAnywhere, Category = Num)
	int MaxStaminaShopNum;	//�ִ� ���¹̳� ���� Ƚ��
	UPROPERTY(EditAnywhere, Category = Num)
	int PotionShopNum;		//���� ȸ���� ���� Ƚ��
};
