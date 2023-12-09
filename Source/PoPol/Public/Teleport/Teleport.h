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

	//Actor ���� �� ����
	virtual void BeginPlay() override;

	/*******   OverlapSystem   ******/

	//�ڽ��� ����� ��� �����ϴ� �Լ�
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:	
	/*******   TeleportSystem   ******/

	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UBoxComponent* TeleportBox;	//�ڷ���Ʈ �ڽ�
	UPROPERTY(EditAnywhere, Category = ActorTarget)
	class AActor* ActorTarget;	//TargetActorclass

	class APopolCharacter* PopolCharacter;
};
