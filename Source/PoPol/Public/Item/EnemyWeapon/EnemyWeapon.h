// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Type/CharacterType.h"
#include "Engine/DataTable.h"
#include "EnemyWeapon.generated.h"

//�κ��丮�� �� ���� ����ü
USTRUCT(BlueprintType)
struct FEnemyWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//����ü �ȿ� �⺻ ������ ��(WeaponDaTA�� ������ ������ Ÿ���� Weapon)
	FEnemyWeaponData()
		:Name(TEXT("")), Texture(nullptr), Damage(0),
		WeaponSpeed(0), WeaponClass()
	{};

public:
	//����ü ���� �⺻ Ÿ��
	//�̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	//�ؽ�Ʈ �̹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;

	//���� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	//���� ���ǵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponSpeed;

	//���� �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AEnemyWeapon> WeaponClass;
};

class UBoxComponent;
class UStaticMeshComponent;
class UTexture2D;
class USceneComponent;
struct FEnemyWeaponData;

UCLASS()
class POPOL_API AEnemyWeapon : public AActor
{
	GENERATED_BODY()
public:
	/*******   MainSystem   ******/

	//Main
	AEnemyWeapon();
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
	void BoxTrace(FHitResult& BoxHit);


private:
	/*******   WeaponSystem   ******/

	//���� �޽�
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	UStaticMeshComponent* WeaponMesh;
	//���� �ڽ�
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	UBoxComponent* WeaponBox;
	//�ڽ� Ʈ���̽� ������������
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;
	//�ڽ� Ʈ���̽� �� ����
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;
	//���� Ʈ���̽� ũ��
	UPROPERTY(EditAnywhere, Category = Vector)
	FVector TarceHalfSize;
	//Enemy
	class AEnemyCharacter* EnemyCharacter;

	/*******   AttackSystem   ******/

	//�÷��̾� ��Ʈ�ѷ��� �ҷ��´�.
	class APopolPlayerController* PopolPlayerController;
	//���� ������ �ҷ���
	FEnemyWeaponData* EnemyWeaponData;
	//�� ���� ����
	struct FEnemyStats* EnemyStats;


public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
