#pragma once

//움직임 상태
UENUM(BlueprintType)
enum class ECharacterMoveType : uint8
{
	//대기 상태
	ECM_Idle UMETA(DisplayName = "ECM_Idle"),
	//걷기 상태
	ECM_Walk UMETA(DisplayName = "ECM_Walk"),
	//달리기 상태
	ECM_Run UMETA(DisplayName = "ECM_Run"),
	//점프 상태
	ECM_JUMP UMETA(DisplayName = "ECM_JUMP"),
	//맞는 중 상태
	ECM_HIT UMETA(DisplayName = "ECM_HIT"),
	//공격 상태
	ECM_Attack UMETA(DisplayName = "ECM_Attack"),
	//방어 상태
	ECM_Block UMETA(DisplayName = "ECM_Block"),
};

//공격 몽타주 상태
UENUM(BlueprintType)
enum class ECharacterAttackType : uint8
{
	//보통 상태
	ECA_COMMONLY UMETA(DisplayName = "ECA_COMMONLY"),
	//공격 중1 번 몽타주 상태
	ECA_ATTACKKING_ONE UMETA(DisplayName = "Attack1"),
	//공격 중2 번 몽타주 상태
	ECA_ATTACKKING_TWO UMETA(DisplayName = "Attack2"),
	//공격 중3 번 몽타주 상태
	ECA_ATTACKKING_THREE UMETA(DisplayName = "Attack3"),
	//공격 중4 번 몽타주 상태
	ECA_ATTACKKING_FOUE UMETA(DisplayName = "Attack4")
}; 

//공격 하는 중 상태
UENUM(BlueprintType)
enum class EAttackingType : uint8
{
	//공격 대기 중
	EAK_ATTACK_WAIT UMETA(DisplayName = "EAK_ATTACK_WAIT"),
	//공격 몽타주 1번 실행 상태
	EAK_ATTACK_ONE UMETA(DisplayName = "ATTACK_ONE"),
	//공격 몽타주 2번 실행 상태
	EAK_ATTACK_TWO UMETA(DisplayName = "ATTACK_TWO"),
	//공격 몽타주 3번 실행 상태
	EAK_ATTACK_THREE UMETA(DisplayName = "ATTACK_THREE"),
	//공격 몽타주 4번 실행 상태
	EAK_ATTACK_FOUE UMETA(DisplayName = "ATTACK_FOUE")
};

//공격 끝난 상태
UENUM(BlueprintType)
enum class EAttackingEndType : uint8
{
	//공격 몽타주 1번 끝난 상태
	EAKE_ATTACK_NOMAL UMETA(DisplayName = "EAKE_ATTACK_NOMAL"),
	//공격 몽타주 1번 끝난 상태
	EAKE_ATTACK_ONE_END UMETA(DisplayName = "EAKE_ATTACK_ONE_END"),
	//공격 몽타주 2번 끝난 상태
	EAKE_ATTACK_TWO_END UMETA(DisplayName = "EAKE_ATTACK_TWO_END"),
	//공격 몽타주 3번 끝난 상태
	EAKE_ATTACK_THREE_END UMETA(DisplayName = "EAKE_ATTACK_THREE_END"),
	//공격 몽타주 4번 끝난 상태
	EAKE_ATTACK_FOUE_END UMETA(DisplayName = "EAKE_ATTACK_FOUE_END")
};
//방어 하는 중 상태
UENUM(BlueprintType)
enum class EBlockingType : uint8
{
	//방어 대기 중
	EBT_BLOCK_WAIT UMETA(DisplayName = "EAK_ATTACK_WAIT"),
	//방어 몽타주 실행 상태
	EBT_BLOCK_ONE UMETA(DisplayName = "ATTACK_ONE")
};

//아이템 타입
UENUM(BlueprintType)
enum class EItemType : uint8
{
	//아무것도 없음
	ITEM_None UMETA(DisplayName = "ITEM_None"),
	ITEM_POTION UMETA(DisplayName = "ITEM_POTION"),
	ITEM_WEAPON UMETA(DisplayName = "ITEM_WEAPON"),
	ITEM_SHIELD UMETA(DisplayName = "ITEM_SHIELD")

};

//무기 등급
UENUM(BlueprintType)
enum class EWeaponRating : uint8
{
	//등급 없음
	EWR_No UMETA(DisplayName = "EWR_No"),
	//노말
	EWR_Nomal UMETA(DisplayName = "EWR_Nomal"),
	//레어
	EWR_rare UMETA(DisplayName = "EWR_rare"),
	//유니크
	EWR_unique UMETA(DisplayName = "EWR_unique"),
	//레전더리
	EWR_Legendary UMETA(DisplayName = "EWR_Legendary")
};

//슬롯 타입
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	//슬롯에 아무것도 없음
	SLOT_None UMETA(DisplayName = "SLOT_None"),
	//슬롯에 아이템 있음
	SLOT_Item UMETA(DisplayName = "SLOT_Item"),
	//슬롯에 무기 있음
	SLOT_WEAPON UMETA(DisplayName = "SLOT_WEAPON"),
	//슬롯에 포션 있음
	SLOT_POTION UMETA(DisplayName = "SLOT_POTION"),
	//슬롯에 스킬 있음
	SLOT_SKILL UMETA(DisplayName = "SLOT_SKILL")
}; 

//장비 장착 여부
UENUM(BlueprintType)
enum class EEquipType : uint8
{
	//아무것도 장착 안함
	EIP_UNARMED UMETA(DisplayName = "EIP_UNARMED"),
	//무기 장착 상태
	EIP_ARMED UMETA(DisplayName = "EIP_ARMED")

};

//적 상태
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	//순찰
	EES_PATROLLING UMETA(DisplayName = "EES_PATROLLING"),
	//전투
	EES_COMBAT UMETA(DisplayName = "EES_COMBAT"),
	//추격
	EES_CHASING UMETA(DisplayName = "EES_CHASING"),
	//죽음
	EES_DEATH UMETA(DisplayName = "EES_DEATH")
};
//적 상태
UENUM(BlueprintType)
enum class EEnemyAttackState : uint8
{
	//기본 상태
	EEAS_NOATTACKING UMETA(DisplayName = "EEAS_ATTACKING"),
	//공격
	EEAS_ATTACKING UMETA(DisplayName = "EEAS_ATTACKING")
};
//무기 장착 상태
UENUM(BlueprintType)
enum class EWeaponEnable : uint8
{
	//비활성화
	EWE_Desable UMETA(DisplayName = "EWE_Desable"),
	//활성화
	EWE_Enable UMETA(DisplayName = "EWE_Enable")

};
//방패 장착 상태
UENUM(BlueprintType)
enum class EShieldEnable : uint8
{
	//비활성화
	ESE_Desable UMETA(DisplayName = "ESE_Desable"),
	//활성화
	ESE_Enable UMETA(DisplayName = "ESE_Enable")
};
UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering UMETA(DisplayName = "EIS_Hovering"),
	EIS_Equipped UMETA(DisplayName = "EIS_Equipped")
};