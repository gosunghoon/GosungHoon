
#include "Widget/CharacterStat/CharacterStatWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "GameInstance/PopolGameInstance.h"
#include "Character/PopolCharacter.h"
#include "Character/State/PopolPlayerState.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Item/Weapon/Weapon.h"

UCharacterStatWidget::UCharacterStatWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UCharacterStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어의 컨트롤러를 PopolPlayerController로 변경해준다.
	PopolPlayerController = Cast<APopolPlayerController>(GetOwningPlayer());
	//공격력 구매 버튼
	StatExitButton->OnClicked.AddDynamic(this, &UCharacterStatWidget::StatExitButtonUI);

	CharacterStatUI(); 
}

void UCharacterStatWidget::CharacterStatUI()
{
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//캐릭터 스탯
	CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerController->GetStatePlayerLevel());
	if (PopolPlayerController->GetEquipWeaponNum_Controller())
	{
		CharWeaponData = PopolGameInstance->GetWeaponDamageData(PopolPlayerController->GetEquipWeaponNum_Controller());
	}




	if (PopolGameInstance != nullptr)
	{
		//Text의 값을 변경
		//레벨
		StatUILevel->SetText(FText::FromString(FString::FromInt(CharacterStats->Level)));
		//HP
		StatUIHP->SetText(FText::FromString(FString::FromInt(CharacterStats->HP)));
		//MaxHP
		StatUIMaxHP->SetText(FText::FromString(FString::FromInt(PopolPlayerController->GetPlayerMaxHPControll())));
		//Stamina
		StatUIStamina->SetText(FText::FromString(FString::FromInt(CharacterStats->Stamina)));
		//MaxStamina
		StatUIMaxStamina->SetText(FText::FromString(FString::FromInt(PopolPlayerController->GetPlayerMaxStaminaControll())));
		if (CharWeaponData != nullptr)
		{
			//AttackDamage
			StatUIAttackDamage->SetText(FText::FromString(FString::FromInt(PopolPlayerController->GetPlayerAttackControll() + CharWeaponData->Damage)));
		}
		else
		{
			//AttackDamage
			StatUIAttackDamage->SetText(FText::FromString(FString::FromInt(PopolPlayerController->GetPlayerAttackControll())));
		}
		//Defense
		StatUIDefense->SetText(FText::FromString(FString::FromInt(PopolPlayerController->GetPlayerDefenseControll())));
		//회복량
		StatUIPosion->SetText(FText::FromString(FString::FromInt(PopolPlayerController->GetPlayerPotionControll())));
	}
}

void UCharacterStatWidget::StatExitButtonUI()
{
	PopolPlayerController->SetPause(false);
	RemoveFromParent();
	PopolPlayerController->bShowMouseCursor = false; //마우스 커서
}
