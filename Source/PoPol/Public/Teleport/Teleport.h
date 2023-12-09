// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleport.generated.h"

UCLASS()
class POPOL_API ATeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	/*******   MainSystem   ******/

	//Main
	ATeleport();

protected:
	/*******   System   ******/

	//Actor 생성 시 설정
	virtual void BeginPlay() override;

	/*******   OverlapSystem   ******/

	//박스에 닿았을 경우 반응하는 함수
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:	
	/*******   TeleportSystem   ******/

	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UBoxComponent* TeleportBox;	//텔레포트 박스
	UPROPERTY(EditAnywhere, Category = ActorTarget)
	class AActor* ActorTarget;	//TargetActorclass

	class APopolCharacter* PopolCharacter;
};
