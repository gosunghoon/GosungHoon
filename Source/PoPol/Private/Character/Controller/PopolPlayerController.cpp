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
//�׷Ͻ� ����
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
//�÷��̾� ���� ��������
int APopolPlayerController::GetStatePlayerLevel()
{
	return PopolPlayerState->GetPlayerLevel();
}
//���� ���� �� �ʱ�ȭ
void APopolPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PopolPlayerState = Cast<APopolPlayerState>(PlayerState);	//PlayerStats
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));	//���� �ν��Ͻ�
	CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerState->GetPlayerLevel());	//ĳ���� ����
	PlayerWidget = CreateWidget<UPlayerWidget>(this, PlayerHUDClass);	//HUD ��������

	PlayerMaxHP = CharacterStats->MaxHP;
	PlayerMaxStamina = CharacterStats->MaxStamina;
	PlayerAttackDamage = CharacterStats->AttackDamage;
	PlayerDefense = CharacterStats->Defense;
	PlayerPotion = CharacterStats->Potion;

	if (PlayerWidget)
	{
		PlayerWidget->AddToViewport();	//ȭ�� ��������

		PlayerWidget->SetLevel(CharacterStats->Level);										//���� ��������
		PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());
		PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);
		PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());
		PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);
		PlayerWidget->SetEXPBarPercent(GetPlayerExpPersent());
		PlayerWidget->SetTextExp(CharacterStats->EXP, CharacterStats->MaxEXP);
		PlayerWidget->SetGold(PopolPlayerState->PlayerGold);

		PlayerWidget->Init();	//���� UI ��������
	}
}


/*******   HP   ******/


//ü�� �ʱ�ȭ
void APopolPlayerController::HealthInit()
{
	CharacterStats->HP = PlayerMaxHP;
	PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());				//ü�� �ۼ�Ʈ �ҷ�����
	PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);		//ü�� �ؽ�Ʈ �ҷ�����
}
//�¾��� ��� ü���ۼ�Ʈ �� �ؽ�Ʈ �� ����
void APopolPlayerController::SetHUDHealth(float DamageAmount)
{
	if (PlayerWidget && PopolPlayerState)
	{
		CharacterStats->HP = FMath::Clamp(CharacterStats->HP - DamageAmount, 0.f, PlayerMaxHP);	//������ ���	
		PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());				//ü�� �ۼ�Ʈ �ҷ�����
		PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);		//ü�� �ؽ�Ʈ �ҷ�����
	}
}
//ȸ�� �� HP�缳��
void APopolPlayerController::SetHUDPosionh(float Posion)
{
	if (PlayerWidget && PopolPlayerState)
	{
		CharacterStats->HP = FMath::Clamp(CharacterStats->HP + Posion, 0.f, PlayerMaxHP); // ȸ���� ���
		PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());				//ü�� �ۼ�Ʈ �ҷ�����
		PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);		//ü�� �ؽ�Ʈ �ҷ�����
	}
}
//������ ��� ���¹̳� �ۼ�Ʈ �� �ؽ�Ʈ ����
void APopolPlayerController::SetHUDBlockStamina(float DownStamina)
{
	if (PlayerWidget && PopolPlayerState)
	{
		CharacterStats->Stamina = FMath::Clamp(CharacterStats->Stamina - DownStamina, 0.f, PlayerMaxStamina);				
		PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());									//���¹̳� �ۼ�Ʈ �ҷ�����
		PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);		//���¹̳� �ؽ�Ʈ �ҷ�����
	}
}
//���¹̳� ���� �� ���¹̳� �ۼ�Ʈ �� �ؽ�Ʈ ����
void APopolPlayerController::SetHUDNomalStamina(float DownStamina)
{
	if (PlayerWidget)
	{
		CharacterStats->Stamina = FMath::Clamp(CharacterStats->Stamina + DownStamina, 0.f, PlayerMaxStamina);	//���¹̳� ���		
		PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());	//���¹̳� �ۼ�Ʈ �ҷ�����
		PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);	//���¹̳� �ؽ�Ʈ �ҷ�����
	}
}
//���� �׿��� ��� ����ġ
void APopolPlayerController::EnemyKillEXP(class AEnemyCharacter* KilledNPC)
{
	if (PopolPlayerState->GetPlayerLevel() == 3)	//�ִ� ����
	{
		bPlayerLevel = false;						//����ġ ȹ�� �Ұ�(������ �Ұ�)
	}

	if (PlayerWidget && bPlayerLevel)
	{
		PopolPlayerState->AddEXP(KilledNPC->GetEXP());							//����ġ �߰�
		PlayerWidget->SetEXPBarPercent(GetPlayerExpPersent());					//����ġ �ۼ�Ʈ �ҷ�����
		PlayerWidget->SetTextExp(CharacterStats->EXP, CharacterStats->MaxEXP);	//����ġ �ؽ�Ʈ �ҷ�����
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
			CharacterStats->EXP = 0;																		//���� �� ���� ����ġ
			PopolPlayerState->InitPlyaerLevel(PopolPlayerState->GetPlayerLevel() + 1);						//���� ��
			CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerState->GetPlayerLevel());	//ĳ���� ����

			PlayerMaxHP += CharacterStats->MaxHP;				//HP ���� �����ش�.
			PlayerMaxStamina += CharacterStats->MaxStamina;		//Stamina���� �����ش�.
			PlayerAttackDamage += CharacterStats->AttackDamage;	//���ݷ� ���� �����ش�.
			PlayerDefense += CharacterStats->Defense;			//���� ���� �����ش�.

			PlayerWidget->SetLevel(CharacterStats->Level);													//���� �缳��
			PlayerWidget->SetHealthBarPercent(GetPlayerHealthpercent());
			PlayerWidget->SetTextHealth(CharacterStats->HP, PlayerMaxHP);
			PlayerWidget->SetStaminaBarPercent(GetStaminaPercent());
			PlayerWidget->SetTextStamina(CharacterStats->Stamina, PlayerMaxStamina);
			PlayerWidget->SetEXPBarPercent(GetPlayerExpPersent());
			PlayerWidget->SetTextExp(CharacterStats->EXP, CharacterStats->MaxEXP);
		}
	}
}
//���� �׿��� ��� ��
void APopolPlayerController::EnemyKillGold(AEnemyCharacter* KilledNPC)
{
	if (PlayerWidget)
	{
		PopolPlayerState->AddGold(KilledNPC->GetGold());	//��� ȹ��
		PlayerWidget->SetGold(PopolPlayerState->PlayerGold);		//��� �ؽ�Ʈ �ҷ�����
	}
}
//��� �ʱ�ȭ
int32 APopolPlayerController::SetPlayerGold_State(int32 Gold)
{
	PopolPlayerState->PlayerGold += Gold;
	return PopolPlayerState->PlayerGold;
}
//�� ����
int32 APopolPlayerController::GetPlayerGoldState()
{
	return PopolPlayerState->PlayerGold + 7000;
}


/*******   PlayerStats   ******/

//�÷��̾� ü�º���
float APopolPlayerController::GetPlayerHealthpercent()
{
	return CharacterStats->HP / PlayerMaxHP;
}
//�÷��̾� ���¹̳� ����
float APopolPlayerController::GetStaminaPercent()
{
	return CharacterStats->Stamina / PlayerMaxStamina;
}
//�÷��̾� ����ġ ����
float APopolPlayerController::GetPlayerExpPersent()
{
	return CharacterStats->EXP / CharacterStats->MaxEXP;
}
//�÷��̾� ��������
bool APopolPlayerController::PlayerIsAlive()
{
	return CharacterStats->HP > 0.f;
}
//�÷��̾� ��������
bool APopolPlayerController::PlayerIsDead()
{
	return CharacterStats->HP <= 0.f;
}


/*******   Weapon   ******/

//���
//���� ��ȣ ��������
int APopolPlayerController::SetEqipWeaponNum(int EquipNum)
{
	PlayerEqipWeaponNum = EquipNum;
	PlayerWidget->Init();				//Widget �ҷ�����
	return PlayerEqipWeaponNum;
}
//���� ��ȣ �ҷ�����
int APopolPlayerController::GetEqipWeaponNum()
{
	return PlayerEqipWeaponNum;
}

//����
//���� ��ȣ ���� ��������
int APopolPlayerController::SetEquipWeaponNum_Controller(int EquipWEapoin)
{
	EquipWeaponNum_Controller = EquipWEapoin;
	return EquipWeaponNum_Controller;
}
//���� ��ȣ ���� �ҷ�����
int APopolPlayerController::GetEquipWeaponNum_Controller()
{
	return EquipWeaponNum_Controller;
}

//1�� ���� Ȱ��ȭ ����
bool APopolPlayerController::SetOneWeaponEquipControllType(bool WeaponEquip)
{
	
	return PopolPlayerState->SetOneWeaponEquipStateType(WeaponEquip);
}
//2�� ���� Ȱ��ȭ ����
bool APopolPlayerController::SetTwoWeaponEquipControllType(bool WeaponEquip)
{
	return PopolPlayerState->SetTwoWeaponEquipStateType(WeaponEquip);
}
//3�� ���� Ȱ��ȭ ����
bool APopolPlayerController::SetThreeWeaponEquipControllType(bool WeaponEquip)
{
	return PopolPlayerState->SetThreeWeaponEquipStateType(WeaponEquip);
}
//4�� ���� Ȱ��ȭ ����
bool APopolPlayerController::SetForeWeaponEquipControllType(bool WeaponEquip)
{
	return PopolPlayerState->SetForeWeaponEquipStateType(WeaponEquip);
}
//1�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerController::GetOneWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}
//2�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerController::GetTwoWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}
//3�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerController::GetThreeWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}
//4�� ���� Ȱ��ȭ ���� �����ϱ�
bool APopolPlayerController::GetForeWeaponEquipControllType()
{
	return PopolPlayerState->GetOneWeaponEquipStateType();
}


//���� ������ �ı� ���� ��������
bool APopolPlayerController::WeaponDesroyType(bool bDestroy)
{
	bWeaponDestroy = bDestroy;
	return bWeaponDestroy;
}
//���� ������ �ı� ���� �ҷ�����
bool APopolPlayerController::GetWeaponDestroy()
{
	return bWeaponDestroy;
}

/*******   Shop   ******/

//���ݷ� ���� Ƚ��
int APopolPlayerController::SetAttackShopNumControl(int AttackNum)
{
	return PopolPlayerState->SetAttackShopNumState(AttackNum);
}
//���� ���� Ƚ��
int APopolPlayerController::SetDefenseShopNumControl(int DefenseNum)
{
	return PopolPlayerState->SetDefenseShopNumState(DefenseNum);
}
//�ִ�ü�� ���� Ƚ��
int APopolPlayerController::SetMaxHPShopNumControl(int MaxHPNum)
{
	return PopolPlayerState->SetMaxHPShopNumState(MaxHPNum);
}
//�ִ� ���¹̳� ���� Ƚ��
int APopolPlayerController::SetMaxStaminaShopNumControl(int MaxStaminaNum)
{
	return PopolPlayerState->SetMaxStaminaShopNumState(MaxStaminaNum);
}
//���� ȸ���� ���� Ƚ��
int APopolPlayerController::SetPotionShopNumControl(int PotionNum)
{
	return PopolPlayerState->SetPotionShopNumState(PotionNum);
}
//���ݷ� ���� Ƚ��
int APopolPlayerController::GetAttackShopNumControl()
{
	return PopolPlayerState->GetAttackShopNumState();
}
//���� ���� Ƚ��
int APopolPlayerController::GetDefenseShopNumControl()
{
	return PopolPlayerState->GetDefenseShopNumState();
}
//�ִ�ü�� ���� Ƚ��
int APopolPlayerController::GetMaxHPShopNumControl()
{
	return PopolPlayerState->GetMaxHPShopNumState();
}
//�ִ� ���¹̳� ���� Ƚ��
int APopolPlayerController::GetMaxStaminaShopNumControl()
{
	return PopolPlayerState->GetMaxStaminaShopNumState();
}
//���� ȸ���� ���� Ƚ��
int APopolPlayerController::GetPotionShopNumControl()
{
	return PopolPlayerState->GetPotionShopNumState();
}


/*******   LastStat   ******/

//���� ü�� �ʱ�ȭ
float APopolPlayerController::SetPlayerMaxHPControll(float HP)
{
	PlayerMaxHP += HP;
	UE_LOG(LogTemp, Log, TEXT("SetPlayerMaxHPControll : %f"), PlayerMaxHP);
	return PlayerMaxHP;
}
//���� ���ݷ� �ʱ�ȭ
float APopolPlayerController::SetPlayerAttackControll(float Attack)
{
	PlayerAttackDamage += Attack;
	return PlayerAttackDamage;
}
//���� ���� �ʱ�ȭ
float APopolPlayerController::SetPlayerDefenseControll(float Defense)
{
	PlayerDefense +=  Defense;
	return PlayerDefense;
}
//���� ���¹̳� �ʱ�ȭ
float APopolPlayerController::SetPlayerMaxStaminaControll(float Stamina)
{
	PlayerMaxStamina += Stamina;
	return PlayerMaxStamina;
}
//���� ���Ƿ� �ʱ�ȭ
int APopolPlayerController::SetPlayerPotionControll(int Potio)
{
	PlayerPotion += Potio;
	return PlayerPotion;
}
//���� ü�� ��������
float APopolPlayerController::GetPlayerMaxHPControll()
{
	return PlayerMaxHP;
}
//���� ���¹̳� ��������
float APopolPlayerController::GetPlayerMaxStaminaControll()
{
	return PlayerMaxStamina;
}
//���� ���ݷ� ��������
float APopolPlayerController::GetPlayerAttackControll()
{
	return PlayerAttackDamage;
}
//���� ���� ��������
float APopolPlayerController::GetPlayerDefenseControll()
{
	return PlayerDefense;
}
//���� ���Ƿ� ��������
int APopolPlayerController::GetPlayerPotionControll()
{
	return PlayerPotion;
}
