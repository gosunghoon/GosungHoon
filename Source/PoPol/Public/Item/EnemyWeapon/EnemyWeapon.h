// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Type/CharacterType.h"
#include "Engine/DataTable.h"
#include "EnemyWeapon.generated.h"

//인벤토리에 들어갈 웨폰 구조체
USTRUCT(BlueprintType)
struct FEnemyWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//구조체 안에 기본 구성과 값(WeaponDaTA라서 무조건 아이템 타입은 Weapon)
	FEnemyWeaponData()
		:Name(TEXT("")), Texture(nullptr), Damage(0),
		WeaponSpeed(0), WeaponClass()
	{};

public:
	//구조체 안의 기본 타입
	//이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	//텍스트 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;

	//무기 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	//무기 스피드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponSpeed;

	//무기 메시
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
	void BoxTrace(FHitResult& BoxHit);


private:
	/*******   WeaponSystem   ******/

	//무기 메쉬
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	UStaticMeshComponent* WeaponMesh;
	//무기 박스
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	UBoxComponent* WeaponBox;
	//박스 트레이스 추적시작지점
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;
	//박스 트레이스 끝 지점
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;
	//라인 트레이스 크기
	UPROPERTY(EditAnywhere, Category = Vector)
	FVector TarceHalfSize;
	//Enemy
	class AEnemyCharacter* EnemyCharacter;

	/*******   AttackSystem   ******/

	//플레이어 컨트롤러를 불러온다.
	class APopolPlayerController* PopolPlayerController;
	//무기 데이터 불러옴
	FEnemyWeaponData* EnemyWeaponData;
	//적 스탯 정보
	struct FEnemyStats* EnemyStats;


public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
