// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Engine/DataTable.h"
#include "Character/Type/CharacterType.h"
#include "PlayerShield.generated.h"

//인벤토리에 들어갈 웨폰 구조체
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
	//구조체 안의 기본 타입
	//이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	//텍스트 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;

	//텍스트 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	//무기 메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APlayerShield> ShieldClass;

	//아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> ItemType;

	//무기 타입
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
	/*******   ShieldSystem   ******/

	UPROPERTY(VisibleAnywhere, Category = "Shield Porperties")
	class UStaticMeshComponent* ShieldMesh; //방패 메시를 생성
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UBoxComponent* ShieldBox; //박스 콜리전 생성
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;//박스 콜리전 반응 시작 지점
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd; //박스 콜리전 반응 끝 지점
	UPROPERTY(EditAnywhere, Category = Vector)
	FVector TarceHalfSize;		//라인 트레이스 크기
	//아이템 파티클 생성
	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* ShieldParticles;


	struct FCharacterStats* CharacterStats;	//캐릭터 스탯 정보
	struct FShieldData* ShieldData;	//캐릭터 방패 정보


	//PlayerController
	class APopolPlayerController* PopolPlayerController;

public:
	FORCEINLINE UBoxComponent* GetShieldBox() const { return ShieldBox; }
};
