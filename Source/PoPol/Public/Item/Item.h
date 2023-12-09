// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Type/CharacterType.h"
#include "Item.generated.h"


UCLASS()
class POPOL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	/*******   System   ******/

	//Main
	AItem();
	virtual void Tick(float DeltaTime) override;

	/*******   AttackSystem   ******/

	//무기 번호
	UPROPERTY(EditAnywhere, Category = Weapon)
	int WeaponNum;

protected:
	/*******   System   ******/

	//시작 시 System 설정
	virtual void BeginPlay() override;
	//Sin값 이동
	UFUNCTION(BlueprintPure)
	float TransformedSin();

	/*******   OverlapSystem   ******/

	//Shere충돌 반응
	UFUNCTION()
	void OnButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Shere충돌 끝 반응
	UFUNCTION()
	void OnButtonOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	/*******   	EnumType  ******/

	//Item Type
	UPROPERTY(VisibleAnywhere)
	EItemState ItemState;

private:
	/*******   System   ******/

	//컨트롤러
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//플레이어
	class APopolCharacter* PopolCharacter;
	//Sin 움직이는 시간
	UPROPERTY(EditAnywhere, Category = System)
	float RunningTime;
	//넓이
	UPROPERTY(EditDefaultsOnly, Category = System)
	float Amplitude = 0.25f;
	//왕복 시간
	UPROPERTY(EditInstanceOnly, Category = System)
	float TimeConstant = 5.f;

	/*******   ItemSystem   ******/

	//Item Mesh
	UPROPERTY(VisibleAnywhere, Category = "Shield Porperties")
	class UStaticMeshComponent* ItemMesh;
	//Sphere Collision
	UPROPERTY(EditAnywhere, Category = "Shield Porperties")
	class USphereComponent* ItemSphere;
	//아이템 콜리전 반응
	UPROPERTY(EditAnywhere, Category = Weapon)
	int CollisionNum;

	//아이템 파티클 생성
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* EmbersEffect;


	/*******   WidgetSystem   ******/

	//플레이어 HUD
	UPROPERTY(EditDefaultsOnly, Category = PlayerButton)
	TSubclassOf<class UItemDropWidget> PlayerItemDropClass;
	//드롭 위드겟
	class UItemDropWidget* ItemDropWidget;


public:
	FORCEINLINE UItemDropWidget* GetItemDropWidget() const { return ItemDropWidget; }

};
