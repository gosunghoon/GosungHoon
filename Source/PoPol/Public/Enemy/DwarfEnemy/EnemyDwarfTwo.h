// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "EnemyDwarfTwo.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API AEnemyDwarfTwo : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	AEnemyDwarfTwo();
	//Tick
	virtual void Tick(float DeltaTime) override;
private:
	/*******   EnemyPatrol   ******/

	//¼øÂû ½ÃÀÛ
	virtual void StartPatrolling() override;


	UPROPERTY(EditAnywhere, Category = Patrol)
	int PatrolNum;
	UPROPERTY(EditAnywhere, Category = Patrol)
	TArray<FVector> PatroLocation;

	UPROPERTY(EditAnywhere, Category = Patrol)
	bool PatrolType;

	UPROPERTY(EditAnywhere, Category = Patrol)
	float TwoPatrolTime;

	/*******   Death   ******/

	//»ç¸Á
	virtual void Death() override;

};
