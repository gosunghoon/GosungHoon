// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Character/Type/CharacterType.h"
#include "Engine/DataTable.h"
#include "Weapon.generated.h"

//인벤토리에 들어갈 웨폰 구조체
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
	//구조체 안의 기본 타입
	//이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	//텍스트 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Texture;

	//무기 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	//무기 스피드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponSpeed;

	//무기 메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AWeapon> WeaponClass;

	//아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> ItemType;

	//무기 타입
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

	//빈 소켓에 장비 장착
	void AttackMeshToSocket(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator);


	/*******   AttackSystem   ******/

	//Trace에 닿은 Actor를 담아놓는 배열
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> IgnoreActors;


protected:
	/*******   System   ******/

	//Actor 생성 시 설정
	virtual void BeginPlay() override;


	/*******   OverlapSystem   ******/

	//박스에 닿았을 경우 반응하는 함수
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//박스 추적
	virtual void BoxTrace(FHitResult& BoxHit);


private:
	/*******   WeaponSystem   ******/

	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UStaticMeshComponent* WeaponMesh;	//무기 메쉬
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UBoxComponent* WeaponBox;	//무기 박스
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;	//박스 트레이스 시작지점
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;	//박스 트레이스 끝 지점
	UPROPERTY(EditAnywhere, Category = Vector)
	FVector TarceHalfSize;	//라인 트레이스 크기


	/*******   AttackSystem   ******/

	class APopolPlayerController* PopolPlayerController;	//플레이어 컨트롤러를 불러온다.
	struct FWeaponData* WeaponData;		//무기 데이터
	//struct FCharacterStats* CharacterStats;		//캐릭터 스탯
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	float PlayerAttackDamage;		//플레이어 공격력

public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
