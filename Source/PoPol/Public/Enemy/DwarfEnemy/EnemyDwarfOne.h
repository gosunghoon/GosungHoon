// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "EnemyDwarfOne.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API AEnemyDwarfOne : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyDwarfOne();
	//Tick
	virtual void Tick(float DeltaTime) override;
private:
	/*******   EnemyPatrol   ******/

	//���� ����
	virtual void StartPatrolling() override;
	//Patrol����
	UPROPERTY(EditAnywhere, Category = Patrol)
	int PatrolNum;
	//Patrol ��ġ
	UPROPERTY(EditAnywhere, Category = Patrol)
	TArray<FVector> PatroLocation;
	//Patrol �ð�
	UPROPERTY(EditAnywhere, Category = Patrol)
	float OnePatrolTime;



	/*******   Death   ******/

	//���
	virtual void Death() override;

};

