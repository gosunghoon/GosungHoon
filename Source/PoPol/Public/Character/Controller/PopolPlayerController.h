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

	//플레이어 레벨 가져오기
	int GetStatePlayerLevel();
	//플레이어 레벨 증가 여부
	bool bPlayerLevel = true;


	/*******   HP   ******/


	//체력 초기화
	void HealthInit();
	//플레이어 체력비율
	float GetPlayerHealthpercent();
	//타격 시 HP재설정
	void SetHUDHealth(float DamageAmount);

	//회복 시 HP재설정
	void SetHUDPosionh(float Posion);
	//플레이어 생존여부
	bool PlayerIsAlive();
	//플레이어 죽음알림
	bool PlayerIsDead();


	/*******   Stamina   ******/

	//플레이어 스태미너 비율
	float GetStaminaPercent();
	//막을 시 Stamina 재설정
	void SetHUDBlockStamina(float DownStamina);
	//기본 상태 Stamina 재설정
	void SetHUDNomalStamina(float DownStamina);


	/*******   EXP   ******/

	//적을 죽였을 경우 경험치
	void EnemyKillEXP(class AEnemyCharacter* KilledNPC);
	//플레이어 경험치 비율s
	float GetPlayerExpPersent();


	/*******   Gold   ******/

	//적을 죽였을 경우 돈
	void EnemyKillGold(class AEnemyCharacter* KilledNPC);

	int32 SetPlayerGold_State(int32 Gold);
	int32 GetPlayerGoldState();


	/*******  Weapon   ******/

	//드롭
	//무기 번호 저장
	int SetEqipWeaponNum(int EquipNum);
	int GetEqipWeaponNum();

	//장착
	//무기 번호 스탯
	int SetEquipWeaponNum_Controller(int EquipWEapoin);
	int GetEquipWeaponNum_Controller();

	//1번 무기 활성화 여부 가져오기
	bool SetOneWeaponEquipControllType(bool WeaponEquip);
	//2번 무기 활성화 여부 가져오기
	bool SetTwoWeaponEquipControllType(bool WeaponEquip);
	//3번 무기 활성화 여부 가져오기
	bool SetThreeWeaponEquipControllType(bool WeaponEquip);
	//4번 무기 활성화 여부 가져오기
	bool SetForeWeaponEquipControllType(bool WeaponEquip);

	//1번 무기 활성화 여부 전달하기
	bool GetOneWeaponEquipControllType();
	//2번 무기 활성화 여부 전달하기
	bool GetTwoWeaponEquipControllType();
	//3번 무기 활성화 여부 전달하기
	bool GetThreeWeaponEquipControllType();
	//4번 무기 활성화 여부 전달하기
	bool GetForeWeaponEquipControllType();

	//무기 파괴
	bool WeaponDesroyType(bool bDestroy);
	bool GetWeaponDestroy();

	//무기 파괴 여부
	bool bWeaponDestroy;


	/*******  Shop   ******/

		//공격력 상점 횟수
	int SetAttackShopNumControl(int AttackNum);
	//방어력 상점 횟수
	int SetDefenseShopNumControl(int DefenseNum);
	//최대체력 상점 횟수
	int SetMaxHPShopNumControl(int MaxHPNum);
	//최대 스태미나 상점 횟수
	int SetMaxStaminaShopNumControl(int MaxStaminaNum);
	//포션 회복량 상점 횟수
	int SetPotionShopNumControl(int PotionNum);

	//공격력 상점 횟수
	int GetAttackShopNumControl();
	//방어력 상점 횟수
	int GetDefenseShopNumControl();
	//최대체력 상점 횟수
	int GetMaxHPShopNumControl();
	//최대 스태미나 상점 횟수
	int GetMaxStaminaShopNumControl();
	//포션 회복량 상점 횟수
	int GetPotionShopNumControl();

	/*******   LastStat   ******/

	float SetPlayerMaxHPControll(float HP);	//최종 체력 초기화
	float SetPlayerAttackControll(float Attack);	//최종 공격력 초기화
	float SetPlayerDefenseControll(float Defense);	//최종 방어력 초기화
	float SetPlayerMaxStaminaControll(float Stamina);	//최종 스태미나 초기화
	int SetPlayerPotionControll(int Potio);	//최종 포션량 초기화

	float GetPlayerMaxHPControll();	//최종 체력 가져오기
	float GetPlayerAttackControll();	//최종 공격력 가져오기
	float GetPlayerDefenseControll();	//최종 방어력 가져오기
	float GetPlayerMaxStaminaControll();	//최종 스태미나 가져오기
	int GetPlayerPotionControll();	//최종 포션량 가져오기


protected:
	virtual void BeginPlay() override;

	/*******   System   ******/

	UPROPERTY(EditDefaultsOnly, Category = PlayerHUD)
	TSubclassOf<class UPlayerWidget> PlayerHUDClass;			//플레이어 HUD


private:
	/*******   System   ******/

	UPROPERTY()
	class APopolPlayerState* PopolPlayerState;			//PlayerStats
	UPROPERTY()
	class UPopolGameInstance* PopolGameInstance;		//게임 인스턴스
	struct FCharacterStats* CharacterStats;				//캐릭터 스탯 정보
	UPROPERTY(VisibleAnywhere)
	class UPlayerWidget* PlayerWidget;					//플레이어 Widget


	/*******   Stat   ******/



	//레벨 업 사운드 생성
	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* LevelUPSound;


	float PlayerAttackDamage;
	float PlayerDefense;
	float PlayerMaxHP;
	float PlayerMaxStamina;
	int PlayerPotion;


	/*******   Weapon   ******/

	UPROPERTY()
	int PlayerEqipWeaponNum;	//플레이어가 드롭할 무기 번호
	UPROPERTY()
	int EquipWeaponNum_Controller;	//플레이어가 장착할 무기 번호
public:
	FORCEINLINE UPlayerWidget* GetPlayerHUD() const { return PlayerWidget; }
};
