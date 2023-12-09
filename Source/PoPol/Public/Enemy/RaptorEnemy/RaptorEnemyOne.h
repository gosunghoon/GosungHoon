// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "RaptorEnemyOne.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API ARaptorEnemyOne : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	ARaptorEnemyOne();
	//Tick
	virtual void Tick(float DeltaTime) override;
private:
	/*******   EnemyPatrol   ******/

	//순찰 시작
	virtual void StartPatrolling() override;
	//Patrol순서
	UPROPERTY(EditAnywhere, Category = Patrol)
	int PatrolNum;
	//Patrol 위치
	UPROPERTY(EditAnywhere, Category = Patrol)
	TArray<FVector> PatroLocation;
	//Patrol 시간
	UPROPERTY(EditAnywhere, Category = Patrol)
	float OnePatrolTime;


	/*******   Death   ******/

	//사망
	virtual void Death() override;
};
