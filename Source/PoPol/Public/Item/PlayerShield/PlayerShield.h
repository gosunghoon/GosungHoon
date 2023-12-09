// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Engine/DataTable.h"
#include "Character/Type/CharacterType.h"
#include "PlayerShield.generated.h"

//�κ��丮�� �� ���� ����ü
USTRUCT(BlueprintType)
struct FShieldData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FShieldData()
		:Name(TEXT("")), Texture(nullptr), defense(20.f),
		ShieldClass(), ItemType(EItemType::ITEM_WEAPON), WeaponType(EWeaponRating::EWR_No)
	{};

public:
	//����ü ���� �⺻ Ÿ��
	//�̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	//�ؽ�Ʈ �̹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;

	//�ؽ�Ʈ �̹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	//���� �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APlayerShield> ShieldClass;

	//������ Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> ItemType;

	//���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponRating> WeaponType;
};

/**
 * 
 */
UCLASS()
class POPOL_API APlayerShield : public AItem
{
	GENERATED_BODY()
	

public:
	/*******   MainSystem   ******/

	//Main
	APlayerShield();


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
	/*******   ShieldSystem   ******/

	UPROPERTY(VisibleAnywhere, Category = "Shield Porperties")
	class UStaticMeshComponent* ShieldMesh; //���� �޽ø� ����
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UBoxComponent* ShieldBox; //�ڽ� �ݸ��� ����
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;//�ڽ� �ݸ��� ���� ���� ����
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd; //�ڽ� �ݸ��� ���� �� ����
	UPROPERTY(EditAnywhere, Category = Vector)
	FVector TarceHalfSize;		//���� Ʈ���̽� ũ��
	//������ ��ƼŬ ����
	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* ShieldParticles;


	struct FCharacterStats* CharacterStats;	//ĳ���� ���� ����
	struct FShieldData* ShieldData;	//ĳ���� ���� ����


	//PlayerController
	class APopolPlayerController* PopolPlayerController;

public:
	FORCEINLINE UBoxComponent* GetShieldBox() const { return ShieldBox; }
};
