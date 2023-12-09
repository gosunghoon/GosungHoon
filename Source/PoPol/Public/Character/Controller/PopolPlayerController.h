// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Enemy/EnemyCharacter.h"
#include "PopolPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API APopolPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/*******   MainSystem   ******/

	//Main
	APopolPlayerController();

	int SetEnemyGruxDeath(int Death);
	int GetEnemyGruxDeath();
	int EnemyGruxDeath;

	/*******   Level   ******/

	//�÷��̾� ���� ��������
	int GetStatePlayerLevel();
	//�÷��̾� ���� ���� ����
	bool bPlayerLevel = true;


	/*******   HP   ******/


	//ü�� �ʱ�ȭ
	void HealthInit();
	//�÷��̾� ü�º���
	float GetPlayerHealthpercent();
	//Ÿ�� �� HP�缳��
	void SetHUDHealth(float DamageAmount);

	//ȸ�� �� HP�缳��
	void SetHUDPosionh(float Posion);
	//�÷��̾� ��������
	bool PlayerIsAlive();
	//�÷��̾� �����˸�
	bool PlayerIsDead();


	/*******   Stamina   ******/

	//�÷��̾� ���¹̳� ����
	float GetStaminaPercent();
	//���� �� Stamina �缳��
	void SetHUDBlockStamina(float DownStamina);
	//�⺻ ���� Stamina �缳��
	void SetHUDNomalStamina(float DownStamina);


	/*******   EXP   ******/

	//���� �׿��� ��� ����ġ
	void EnemyKillEXP(class AEnemyCharacter* KilledNPC);
	//�÷��̾� ����ġ ����s
	float GetPlayerExpPersent();


	/*******   Gold   ******/

	//���� �׿��� ��� ��
	void EnemyKillGold(class AEnemyCharacter* KilledNPC);

	int32 SetPlayerGold_State(int32 Gold);
	int32 GetPlayerGoldState();


	/*******  Weapon   ******/

	//���
	//���� ��ȣ ����
	int SetEqipWeaponNum(int EquipNum);
	int GetEqipWeaponNum();

	//����
	//���� ��ȣ ����
	int SetEquipWeaponNum_Controller(int EquipWEapoin);
	int GetEquipWeaponNum_Controller();

	//1�� ���� Ȱ��ȭ ���� ��������
	bool SetOneWeaponEquipControllType(bool WeaponEquip);
	//2�� ���� Ȱ��ȭ ���� ��������
	bool SetTwoWeaponEquipControllType(bool WeaponEquip);
	//3�� ���� Ȱ��ȭ ���� ��������
	bool SetThreeWeaponEquipControllType(bool WeaponEquip);
	//4�� ���� Ȱ��ȭ ���� ��������
	bool SetForeWeaponEquipControllType(bool WeaponEquip);

	//1�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetOneWeaponEquipControllType();
	//2�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetTwoWeaponEquipControllType();
	//3�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetThreeWeaponEquipControllType();
	//4�� ���� Ȱ��ȭ ���� �����ϱ�
	bool GetForeWeaponEquipControllType();

	//���� �ı�
	bool WeaponDesroyType(bool bDestroy);
	bool GetWeaponDestroy();

	//���� �ı� ����
	bool bWeaponDestroy;


	/*******  Shop   ******/

		//���ݷ� ���� Ƚ��
	int SetAttackShopNumControl(int AttackNum);
	//���� ���� Ƚ��
	int SetDefenseShopNumControl(int DefenseNum);
	//�ִ�ü�� ���� Ƚ��
	int SetMaxHPShopNumControl(int MaxHPNum);
	//�ִ� ���¹̳� ���� Ƚ��
	int SetMaxStaminaShopNumControl(int MaxStaminaNum);
	//���� ȸ���� ���� Ƚ��
	int SetPotionShopNumControl(int PotionNum);

	//���ݷ� ���� Ƚ��
	int GetAttackShopNumControl();
	//���� ���� Ƚ��
	int GetDefenseShopNumControl();
	//�ִ�ü�� ���� Ƚ��
	int GetMaxHPShopNumControl();
	//�ִ� ���¹̳� ���� Ƚ��
	int GetMaxStaminaShopNumControl();
	//���� ȸ���� ���� Ƚ��
	int GetPotionShopNumControl();

	/*******   LastStat   ******/

	float SetPlayerMaxHPControll(float HP);	//���� ü�� �ʱ�ȭ
	float SetPlayerAttackControll(float Attack);	//���� ���ݷ� �ʱ�ȭ
	float SetPlayerDefenseControll(float Defense);	//���� ���� �ʱ�ȭ
	float SetPlayerMaxStaminaControll(float Stamina);	//���� ���¹̳� �ʱ�ȭ
	int SetPlayerPotionControll(int Potio);	//���� ���Ƿ� �ʱ�ȭ

	float GetPlayerMaxHPControll();	//���� ü�� ��������
	float GetPlayerAttackControll();	//���� ���ݷ� ��������
	float GetPlayerDefenseControll();	//���� ���� ��������
	float GetPlayerMaxStaminaControll();	//���� ���¹̳� ��������
	int GetPlayerPotionControll();	//���� ���Ƿ� ��������


protected:
	virtual void BeginPlay() override;

	/*******   System   ******/

	UPROPERTY(EditDefaultsOnly, Category = PlayerHUD)
	TSubclassOf<class UPlayerWidget> PlayerHUDClass;			//�÷��̾� HUD


private:
	/*******   System   ******/

	UPROPERTY()
	class APopolPlayerState* PopolPlayerState;			//PlayerStats
	UPROPERTY()
	class UPopolGameInstance* PopolGameInstance;		//���� �ν��Ͻ�
	struct FCharacterStats* CharacterStats;				//ĳ���� ���� ����
	UPROPERTY(VisibleAnywhere)
	class UPlayerWidget* PlayerWidget;					//�÷��̾� Widget


	/*******   Stat   ******/



	//���� �� ���� ����
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* LevelUPSound;


	float PlayerAttackDamage;
	float PlayerDefense;
	float PlayerMaxHP;
	float PlayerMaxStamina;
	int PlayerPotion;


	/*******   Weapon   ******/

	UPROPERTY()
	int PlayerEqipWeaponNum;	//�÷��̾ ����� ���� ��ȣ
	UPROPERTY()
	int EquipWeaponNum_Controller;	//�÷��̾ ������ ���� ��ȣ
public:
	FORCEINLINE UPlayerWidget* GetPlayerHUD() const { return PlayerWidget; }
};
