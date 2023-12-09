// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Character/Type/CharacterType.h"
#include "Engine/DataTable.h"
#include "Weapon.generated.h"

//�κ��丮�� �� ���� ����ü
USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FWeaponData()
		:Name(TEXT("")), Texture(nullptr), Damage(0), WeaponSpeed(0),
		WeaponClass(),ItemType(EItemType::ITEM_WEAPON), WeaponType(EWeaponRating::EWR_No)
	{};

public:
	//����ü ���� �⺻ Ÿ��
	//�̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	//�ؽ�Ʈ �̹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Texture;

	//���� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	//���� ���ǵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponSpeed;

	//���� �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AWeapon> WeaponClass;

	//������ Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> ItemType;

	//���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponRating> WeaponType;
};


class USceneComponent;


UCLASS()
class POPOL_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	/*******   MainSystem   ******/

	//Main
	AWeapon();


public:
	/*******   Equip   ******/

	//�� ���Ͽ� ��� ����
	void AttackMeshToSocket(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator);


	/*******   AttackSystem   ******/

	//Trace�� ���� Actor�� ��Ƴ��� �迭
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> IgnoreActors;


protected:
	/*******   System   ******/

	//Actor ���� �� ����
	virtual void BeginPlay() override;


	/*******   OverlapSystem   ******/

	//�ڽ��� ����� ��� �����ϴ� �Լ�
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//�ڽ� ����
	virtual void BoxTrace(FHitResult& BoxHit);


private:
	/*******   WeaponSystem   ******/

	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UStaticMeshComponent* WeaponMesh;	//���� �޽�
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UBoxComponent* WeaponBox;	//���� �ڽ�
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;	//�ڽ� Ʈ���̽� ��������
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;	//�ڽ� Ʈ���̽� �� ����
	UPROPERTY(EditAnywhere, Category = Vector)
	FVector TarceHalfSize;	//���� Ʈ���̽� ũ��


	/*******   AttackSystem   ******/

	class APopolPlayerController* PopolPlayerController;	//�÷��̾� ��Ʈ�ѷ��� �ҷ��´�.
	struct FWeaponData* WeaponData;		//���� ������
	//struct FCharacterStats* CharacterStats;		//ĳ���� ����
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	float PlayerAttackDamage;		//�÷��̾� ���ݷ�

public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
