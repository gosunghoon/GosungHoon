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

	//1번 무기 활성화 여부
	bool SetOneWeaponEquipStateType(bool WeaponEquip);
	//2번 무기 활성화 여부
	bool SetTwoWeaponEquipStateType(bool WeaponEquip);
	//3번 무기 활성화 여부
	bool SetThreeWeaponEquipStateType(bool WeaponEquip);
	//4번 무기 활성화 여부
	bool SetForeWeaponEquipStateType(bool WeaponEquip);

	//1번 무기 활성화 여부 전달하기
	bool GetOneWeaponEquipStateType();
	//2번 무기 활성화 여부 전달하기
	bool GetTwoWeaponEquipStateType();
	//3번 무기 활성화 여부 전달하기
	bool GetThreeWeaponEquipStateType();
	//4번 무기 활성화 여부 전달하기
	bool GetForeWeaponEquipStateType();


	/*******   Level   ******/

	//플레이어 레벨 가져오기
	int GetPlayerLevel();
	//플레이어 레벨 초기화
	void InitPlyaerLevel(int Level);


	/*******   EXP   ******/

	//경험치 획득
	float AddEXP(float EnemyEXP);

	/*******   Gold   ******/

	//골드 획득
	int32 AddGold(int32 EnemyGold);
	int32 PlayerGold;

	/*******   Shop   ******/

	//공격력 상점 횟수
	int SetAttackShopNumState(int AttackNum);
	//방어력 상점 횟수
	int SetDefenseShopNumState(int DefenseNum);
	//최대체력 상점 횟수
	int SetMaxHPShopNumState(int MaxHPNum);
	//최대 스태미나 상점 횟수
	int SetMaxStaminaShopNumState(int MaxStaminaNum);
	//포션 회복량 상점 횟수
	int SetPotionShopNumState(int PotionNum);

	//공격력 상점 횟수
	int GetAttackShopNumState();
	//방어력 상점 횟수
	int GetDefenseShopNumState();
	//최대체력 상점 횟수
	int GetMaxHPShopNumState();
	//최대 스태미나 상점 횟수
	int GetMaxStaminaShopNumState();
	//포션 회복량 상점 횟수
	int GetPotionShopNumState();


protected:
	//시스템 시작 시 System
	virtual void BeginPlay() override;

private:
	/*******   System   ******/

	UPROPERTY()
	class UPopolGameInstance* PopolGameInstance;	//게임 인스턴스
	struct FCharacterStats* CharacterStats;			//캐릭터 스탯 정보


	/*******   PlayerStats   ******/

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	int PlayerLevle;			//플레이어 레벨(행)


	bool OneWeaponEquipType;	//1번 무기 사용 가능 여부
	bool TwoWeaponEquipType;	//2번 무기 사용 가능 여부
	bool ThreeWeaponEquipType;	//3번 무기 사용 가능 여부
	bool ForeWeaponEquipType;	//4번 무기 사용 가능 여부
	UPROPERTY(EditAnywhere, Category = Num)
	int AttackShopNum;		//공격력 상점 횟수
	UPROPERTY(EditAnywhere, Category = Num)
	int DefenseShopNum;		//방어력 상점 횟수	
	UPROPERTY(EditAnywhere, Category = Num)
	int MaxHPShopNum;		//최대체력 상점 횟수
	UPROPERTY(EditAnywhere, Category = Num)
	int MaxStaminaShopNum;	//최대 스태미나 상점 횟수
	UPROPERTY(EditAnywhere, Category = Num)
	int PotionShopNum;		//포션 회복량 상점 횟수
};
