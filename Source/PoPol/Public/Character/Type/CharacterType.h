#pragma once

//������ ����
UENUM(BlueprintType)
enum class ECharacterMoveType : uint8
{
	//��� ����
	ECM_Idle UMETA(DisplayName = "ECM_Idle"),
	//�ȱ� ����
	ECM_Walk UMETA(DisplayName = "ECM_Walk"),
	//�޸��� ����
	ECM_Run UMETA(DisplayName = "ECM_Run"),
	//���� ����
	ECM_JUMP UMETA(DisplayName = "ECM_JUMP"),
	//�´� �� ����
	ECM_HIT UMETA(DisplayName = "ECM_HIT"),
	//���� ����
	ECM_Attack UMETA(DisplayName = "ECM_Attack"),
	//��� ����
	ECM_Block UMETA(DisplayName = "ECM_Block"),
};

//���� ��Ÿ�� ����
UENUM(BlueprintType)
enum class ECharacterAttackType : uint8
{
	//���� ����
	ECA_COMMONLY UMETA(DisplayName = "ECA_COMMONLY"),
	//���� ��1 �� ��Ÿ�� ����
	ECA_ATTACKKING_ONE UMETA(DisplayName = "Attack1"),
	//���� ��2 �� ��Ÿ�� ����
	ECA_ATTACKKING_TWO UMETA(DisplayName = "Attack2"),
	//���� ��3 �� ��Ÿ�� ����
	ECA_ATTACKKING_THREE UMETA(DisplayName = "Attack3"),
	//���� ��4 �� ��Ÿ�� ����
	ECA_ATTACKKING_FOUE UMETA(DisplayName = "Attack4")
}; 

//���� �ϴ� �� ����
UENUM(BlueprintType)
enum class EAttackingType : uint8
{
	//���� ��� ��
	EAK_ATTACK_WAIT UMETA(DisplayName = "EAK_ATTACK_WAIT"),
	//���� ��Ÿ�� 1�� ���� ����
	EAK_ATTACK_ONE UMETA(DisplayName = "ATTACK_ONE"),
	//���� ��Ÿ�� 2�� ���� ����
	EAK_ATTACK_TWO UMETA(DisplayName = "ATTACK_TWO"),
	//���� ��Ÿ�� 3�� ���� ����
	EAK_ATTACK_THREE UMETA(DisplayName = "ATTACK_THREE"),
	//���� ��Ÿ�� 4�� ���� ����
	EAK_ATTACK_FOUE UMETA(DisplayName = "ATTACK_FOUE")
};

//���� ���� ����
UENUM(BlueprintType)
enum class EAttackingEndType : uint8
{
	//���� ��Ÿ�� 1�� ���� ����
	EAKE_ATTACK_NOMAL UMETA(DisplayName = "EAKE_ATTACK_NOMAL"),
	//���� ��Ÿ�� 1�� ���� ����
	EAKE_ATTACK_ONE_END UMETA(DisplayName = "EAKE_ATTACK_ONE_END"),
	//���� ��Ÿ�� 2�� ���� ����
	EAKE_ATTACK_TWO_END UMETA(DisplayName = "EAKE_ATTACK_TWO_END"),
	//���� ��Ÿ�� 3�� ���� ����
	EAKE_ATTACK_THREE_END UMETA(DisplayName = "EAKE_ATTACK_THREE_END"),
	//���� ��Ÿ�� 4�� ���� ����
	EAKE_ATTACK_FOUE_END UMETA(DisplayName = "EAKE_ATTACK_FOUE_END")
};
//��� �ϴ� �� ����
UENUM(BlueprintType)
enum class EBlockingType : uint8
{
	//��� ��� ��
	EBT_BLOCK_WAIT UMETA(DisplayName = "EAK_ATTACK_WAIT"),
	//��� ��Ÿ�� ���� ����
	EBT_BLOCK_ONE UMETA(DisplayName = "ATTACK_ONE")
};

//������ Ÿ��
UENUM(BlueprintType)
enum class EItemType : uint8
{
	//�ƹ��͵� ����
	ITEM_None UMETA(DisplayName = "ITEM_None"),
	ITEM_POTION UMETA(DisplayName = "ITEM_POTION"),
	ITEM_WEAPON UMETA(DisplayName = "ITEM_WEAPON"),
	ITEM_SHIELD UMETA(DisplayName = "ITEM_SHIELD")

};

//���� ���
UENUM(BlueprintType)
enum class EWeaponRating : uint8
{
	//��� ����
	EWR_No UMETA(DisplayName = "EWR_No"),
	//�븻
	EWR_Nomal UMETA(DisplayName = "EWR_Nomal"),
	//����
	EWR_rare UMETA(DisplayName = "EWR_rare"),
	//����ũ
	EWR_unique UMETA(DisplayName = "EWR_unique"),
	//��������
	EWR_Legendary UMETA(DisplayName = "EWR_Legendary")
};

//���� Ÿ��
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	//���Կ� �ƹ��͵� ����
	SLOT_None UMETA(DisplayName = "SLOT_None"),
	//���Կ� ������ ����
	SLOT_Item UMETA(DisplayName = "SLOT_Item"),
	//���Կ� ���� ����
	SLOT_WEAPON UMETA(DisplayName = "SLOT_WEAPON"),
	//���Կ� ���� ����
	SLOT_POTION UMETA(DisplayName = "SLOT_POTION"),
	//���Կ� ��ų ����
	SLOT_SKILL UMETA(DisplayName = "SLOT_SKILL")
}; 

//��� ���� ����
UENUM(BlueprintType)
enum class EEquipType : uint8
{
	//�ƹ��͵� ���� ����
	EIP_UNARMED UMETA(DisplayName = "EIP_UNARMED"),
	//���� ���� ����
	EIP_ARMED UMETA(DisplayName = "EIP_ARMED")

};

//�� ����
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	//����
	EES_PATROLLING UMETA(DisplayName = "EES_PATROLLING"),
	//����
	EES_COMBAT UMETA(DisplayName = "EES_COMBAT"),
	//�߰�
	EES_CHASING UMETA(DisplayName = "EES_CHASING"),
	//����
	EES_DEATH UMETA(DisplayName = "EES_DEATH")
};
//�� ����
UENUM(BlueprintType)
enum class EEnemyAttackState : uint8
{
	//�⺻ ����
	EEAS_NOATTACKING UMETA(DisplayName = "EEAS_ATTACKING"),
	//����
	EEAS_ATTACKING UMETA(DisplayName = "EEAS_ATTACKING")
};
//���� ���� ����
UENUM(BlueprintType)
enum class EWeaponEnable : uint8
{
	//��Ȱ��ȭ
	EWE_Desable UMETA(DisplayName = "EWE_Desable"),
	//Ȱ��ȭ
	EWE_Enable UMETA(DisplayName = "EWE_Enable")

};
//���� ���� ����
UENUM(BlueprintType)
enum class EShieldEnable : uint8
{
	//��Ȱ��ȭ
	ESE_Desable UMETA(DisplayName = "ESE_Desable"),
	//Ȱ��ȭ
	ESE_Enable UMETA(DisplayName = "ESE_Enable")
};
UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering UMETA(DisplayName = "EIS_Hovering"),
	EIS_Equipped UMETA(DisplayName = "EIS_Equipped")
};