// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Controller/PopolPlayerController.h"
#include "Character/State/PopolPlayerState.h"
#include "Character/PopolCharacter.h"
#include "GameInstance/PopolGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/CharacterMainWidget/PlayerWidget.h"
#include "Item/Weapon/Weapon.h"
#include "Widget/CharacterMainWidget/ItemDropWidget.h"
#include "Widget/CharacterItemSlot/SlotInvenWidget.h"
#include "GameFramework/GameModeBase.h"


/*******   MainSystem   ******/

//Main
APopolPlayerController::APopolPlayerController()
{
	//EAutoReceiveInput::Player1;
}
//그록스 죽음
int APopolPlayerController::SetEnemyGruxDeath(int Death)
{
	EnemyGruxDeath = Death;
	UE_LOG(LogTemp, Log, TEXT("EnemyGruxDeath %d"), EnemyGruxDeath);
	return EnemyGruxDeath;
}
int APopolPlayerController::GetEnemyGruxDeath()
{
	UE_LOG(LogTemp, Log, TEXT("EnemyGruxDeath %d"), EnemyGruxDeath);
	return EnemyGruxDeath;
}
//플레이어 레벨 가져오기
int APopolPlayerController::GetStatePlayerLevel()
{
	return PopolPlayerState->GetPlayerLevel();
}
//게임 시작 시 초기화
void APopolPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PopolPlayerState = Cast<APopolPlayerState>(PlayerState);	//PlayerStats
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));	//게임 인스턴스
	CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerState->GetPlayerLevel());	//캐릭터 스탯
	PlayerWidget = CreateWidget<UPlayerWidget>(this, PlayerHUDClass);	//HUD 가져오기

	PlayerMaxHP = CharacterStats->MaxHP;
	PlayerMaxStamina = CharacterStats->MaxStamina;
	PlayerAttackDamage = CharacterStats->AttackDamage;
	PlayerDefense = CharacterStats->Defense;
	PlayerPotion = CharacterStats->Potion;

	if (PlayerWidget)
	{
		PlayerWidget->AddToViewport();	//화면 가져오기

		PlayerWidget->SetLevel(CharacterStats->Level);										//스탯 가져오기
		PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());
		PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);
		PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());
		PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);
		PlayerWidget->SetEXPBarPercent(GetPlayerExpPersent());
		PlayerWidget->SetTextExp(CharacterStats->EXP, CharacterStats->MaxEXP);
		PlayerWidget->SetGold(PopolPlayerState->PlayerGold);

		PlayerWidget->Init();	//무기 UI 가져오기
	}
}


/*******   HP   ******/


//체력 초기화
void APopolPlayerController::HealthInit()
{
	CharacterStats->HP = PlayerMaxHP;
	PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());				//체력 퍼센트 불러오기
	PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);		//체력 텍스트 불러오기
}
//맞았을 경우 체력퍼센트 및 텍스트 량 수정
void APopolPlayerController::SetHUDHealth(float DamageAmount)
{
	if (PlayerWidget && PopolPlayerState)
	{
		CharacterStats->HP = FMath::Clamp(CharacterStats->HP - DamageAmount, 0.f, PlayerMaxHP);	//데미지 계산	
		PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());				//체력 퍼센트 불러오기
		PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);		//체력 텍스트 불러오기
	}
}
//회복 시 HP재설정
void APopolPlayerController::SetHUDPosionh(float Posion)
{
	if (PlayerWidget && PopolPlayerState)
	{
		CharacterStats->HP = FMath::Clamp(CharacterStats->HP + Posion, 0.f, PlayerMaxHP); // 회복량 계산
		PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());				//체력 퍼센트 불러오기
		PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);		//체력 텍스트 불러오기
	}
}
//막았을 경우 스태미나 퍼센트 및 텍스트 수정
void APopolPlayerController::SetHUDBlockStamina(float DownStamina)
{
	if (PlayerWidget && PopolPlayerState)
	{
		CharacterStats->Stamina = FMath::Clamp(CharacterStats->Stamina - DownStamina, 0.f, PlayerMaxStamina);				
		PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());									//스태미너 퍼센트 불러오기
		PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);		//스태미너 텍스트 불러오기
	}
}
//스태미나 충전 시 스태미나 퍼센트 및 텍스트 수정
void APopolPlayerController::SetHUDNomalStamina(float DownStamina)
{
	if (PlayerWidget)
	{
		CharacterStats->Stamina = FMath::Clamp(CharacterStats->Stamina + DownStamina, 0.f, PlayerMaxStamina);	//스태미너 계산		
		PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());	//스태미너 퍼센트 불러오기
		PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);	//스태미너 텍스트 불러오기
	}
}
//적을 죽였을 경우 경험치
void APopolPlayerController::EnemyKillEXP(class AEnemyCharacter* KilledNPC)
{
	if (PopolPlayerState->GetPlayerLevel() == 3)	//최대 레벨
	{
		bPlayerLevel = false;						//경험치 획득 불가(레벨업 불가)
	}

	if (PlayerWidget && bPlayerLevel)
	{
		PopolPlayerState->AddEXP(KilledNPC->GetEXP());							//경험치 추가
		PlayerWidget->SetEXPBarPercent(GetPlayerExpPersent());					//경험치 퍼센트 불러오기
		PlayerWidget->SetTextExp(CharacterStats->EXP, CharacterStats->MaxEXP);	//경험치 텍스트 불러오기
	}
	if (CharacterStats->EXP >= CharacterStats->MaxEXP || CharacterStats->EXP == CharacterStats->MaxEXP)
	{
		if (PlayerWidget)
		{
			if (LevelUPSound)
			{
				UGameplayStatics::PlaySound2D(this, LevelUPSound, 2.5f);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("UGameplayStatics::SpawnEmitterAtLocation"));
			}
			CharacterStats->EXP = 0;																		//레벨 업 이후 경험치
			PopolPlayerState->InitPlyaerLevel(PopolPlayerState->GetPlayerLevel() + 1);						//레벨 업
			CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerState->GetPlayerLevel());	//캐릭터 스탯

			PlayerMaxHP += CharacterStats->MaxHP;				//HP 값을 더해준다.
			PlayerMaxStamina += CharacterStats->MaxStamina;		//Stamina값을 더해준다.
			PlayerAttackDamage += CharacterStats->AttackDamage;	//공격력 값을 더해준다.
			PlayerDefense += CharacterStats->Defense;			//방어력 값을 더해준다.

			PlayerWidget->SetLevel(CharacterStats->Level);													//스탯 재설정
			PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());
			PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);
			PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());
			PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);
			PlayerWidget->SetEXPBarPercent(GetPlayerExpPersent());
			PlayerWidget->SetTextExp(CharacterStats->EXP, CharacterStats->MaxEXP);
		}
	}
}
//적을 죽였을 경우 돈
void APopolPlayerController::EnemyKillGold(AEnemyCharacter* KilledNPC)
{
	if (PlayerWidget)
	{
		PopolPlayerState->AddGold(KilledNPC->GetGold());	//골드 획득
		PlayerWidget->SetGold(PopolPlayerState->PlayerGold);		//골드 텍스트 불러오기
	}
}
//골드 초기화
int32 APopolPlayerController::SetPlayerGold_State(int32 Gold)
{
	PopolPlayerState->PlayerGold += Gold;
	return PopolPlayerState->PlayerGold;
}
//돈 전달
int32 APopolPlayerController::GetPlayerGoldState()
{
	return PopolPlayerState->PlayerGold + 7000;
}


/*******   PlayerStats   ******/

//플레이어 체력비율
float APopolPlayerController::GetPlayerHealthpercent()
{
	return CharacterStats->HP / PlayerMaxHP;
}
//플레이어 스태미너 비율
float APopolPlayerController::GetStaminaPercent()
{
	return CharacterStats->Stamina / PlayerMaxStamina;
}
//플레이어 경험치 비율
float APopolPlayerController::GetPlayerExpPersent()
{
	return CharacterStats->EXP / CharacterStats->MaxEXP;
}
//플레이어 생존여부
bool APopolPlayerController::PlayerIsAlive()
{
	return CharacterStats->HP > 0.f;
}
//플레이어 죽음여부
bool APopolPlayerController::PlayerIsDead()
{
	return CharacterStats->HP <= 0.f;
}


/*******   Weapon   ******/

//드롭
//무기 번호 가져오기
int APopolPlayerController::SetEqipWeaponNum(int EquipNum)
{
	PlayerEqipWeaponNum = EquipNum;
	PlayerWidget->Init();				//Widget 불러오기
	return PlayerEqipWeaponNum;
}
//무기 번호 불러오기
int APopolPlayerController::GetEqipWeaponNum()
{
	return PlayerEqipWeaponNum;
}

//장착
//무기 번호 스탯 가져오기
int APopolPlayerController::SetEquipWeaponNum_Controller(int EquipWEapoin)
{
	EquipWeaponNum_Controller = EquipWEapoin;
	return EquipWeaponNum_Controller;
}
//무기 번호 스탯 불러오기
int APopolPlayerController::GetEquipWeaponNum_Controller()
{
	return EquipWeaponNum_Controller;
}

//1번 무기 활성화 여부
bool APopolPlayerController::SetOneWeaponEquipControllType(bool WeaponEquip)
{
	
	return PopolPlayerState->SetOneWeaponEquipStateType(WeaponEquip);
}
//2번 무기 활성화 여부
bool APopolPlayerController::SetTwoWeaponEquipControllType(bool WeaponEquip)
{
	return PopolPlayerState->SetTwoWeaponEquipStateType(WeaponEquip);
}
//3번 무기 활성화 여부
bool APopolPlayerController::SetThreeWeaponEquipControllType(bool WeaponEquip)
{
	return PopolPlayerState->SetThreeWeaponEquipStateType(WeaponEquip);
}
//4번 무기 활성화 여부
bool APopolPlayerController::SetForeWeaponEquipControllType(bool WeaponEquip)
{
	return PopolPlayerState->SetForeWeaponEquipStateType(WeaponEquip);
}
//1번 무기 활성화 여부 전달하기
bool APopolPlayerController::GetOneWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}
//2번 무기 활성화 여부 전달하기
bool APopolPlayerController::GetTwoWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}
//3번 무기 활성화 여부 전달하기
bool APopolPlayerController::GetThreeWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}
//4번 무기 활성화 여부 전달하기
bool APopolPlayerController::GetForeWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}


//무기 아이템 파괴 여부 가져오기
bool APopolPlayerController::WeaponDesroyType(bool bDestroy)
{
	bWeaponDestroy = bDestroy;
	return bWeaponDestroy;
}
//무기 아이템 파괴 여부 불러오기
bool APopolPlayerController::GetWeaponDestroy()
{
	return bWeaponDestroy;
}

/*******   Shop   ******/

//공격력 상점 횟수
int APopolPlayerController::SetAttackShopNumControl(int AttackNum)
{
	return PopolPlayerState->SetAttackShopNumState(AttackNum);
}
//방어력 상점 횟수
int APopolPlayerController::SetDefenseShopNumControl(int DefenseNum)
{
	return PopolPlayerState->SetDefenseShopNumState(DefenseNum);
}
//최대체력 상점 횟수
int APopolPlayerController::SetMaxHPShopNumControl(int MaxHPNum)
{
	return PopolPlayerState->SetMaxHPShopNumState(MaxHPNum);
}
//최대 스태미나 상점 횟수
int APopolPlayerController::SetMaxStaminaShopNumControl(int MaxStaminaNum)
{
	return PopolPlayerState->SetMaxStaminaShopNumState(MaxStaminaNum);
}
//포션 회복량 상점 횟수
int APopolPlayerController::SetPotionShopNumControl(int PotionNum)
{
	return PopolPlayerState->SetPotionShopNumState(PotionNum);
}
//공격력 상점 횟수
int APopolPlayerController::GetAttackShopNumControl()
{
	return PopolPlayerState->GetAttackShopNumState();
}
//방어력 상점 횟수
int APopolPlayerController::GetDefenseShopNumControl()
{
	return PopolPlayerState->GetDefenseShopNumState();
}
//최대체력 상점 횟수
int APopolPlayerController::GetMaxHPShopNumControl()
{
	return PopolPlayerState->GetMaxHPShopNumState();
}
//최대 스태미나 상점 횟수
int APopolPlayerController::GetMaxStaminaShopNumControl()
{
	return PopolPlayerState->GetMaxStaminaShopNumState();
}
//포션 회복량 상점 횟수
int APopolPlayerController::GetPotionShopNumControl()
{
	return PopolPlayerState->GetPotionShopNumState();
}


/*******   LastStat   ******/

//최종 체력 초기화
float APopolPlayerController::SetPlayerMaxHPControll(float HP)
{
	PlayerMaxHP += HP;
	UE_LOG(LogTemp, Log, TEXT("SetPlayerMaxHPControll : %f"), PlayerMaxHP);
	return PlayerMaxHP;
}
//최종 공격력 초기화
float APopolPlayerController::SetPlayerAttackControll(float Attack)
{
	PlayerAttackDamage += Attack;
	return PlayerAttackDamage;
}
//최종 방어력 초기화
float APopolPlayerController::SetPlayerDefenseControll(float Defense)
{
	PlayerDefense +=  Defense;
	return PlayerDefense;
}
//최종 스태미나 초기화
float APopolPlayerController::SetPlayerMaxStaminaControll(float Stamina)
{
	PlayerMaxStamina += Stamina;
	return PlayerMaxStamina;
}
//최종 포션량 초기화
int APopolPlayerController::SetPlayerPotionControll(int Potio)
{
	PlayerPotion += Potio;
	return PlayerPotion;
}
//최종 체력 가져오기
float APopolPlayerController::GetPlayerMaxHPControll()
{
	return PlayerMaxHP;
}
//최종 스태미나 가져오기
float APopolPlayerController::GetPlayerMaxStaminaControll()
{
	return PlayerMaxStamina;
}
//최종 공격력 가져오기
float APopolPlayerController::GetPlayerAttackControll()
{
	return PlayerAttackDamage;
}
//최종 방어력 가져오기
float APopolPlayerController::GetPlayerDefenseControll()
{
	return PlayerDefense;
}
//최종 포션량 가져오기
int APopolPlayerController::GetPlayerPotionControll()
{
	return PlayerPotion;
}
