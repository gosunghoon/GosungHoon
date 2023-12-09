// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RaptorEnemy/RaptorEnemyOne.h"
#include "GameMode/PoPolGameMode.h"
#include "AIController.h"

ARaptorEnemyOne::ARaptorEnemyOne()
{
}
//Tick
void ARaptorEnemyOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnePatrolTime += DeltaTime;
	if (OnePatrolTime >= PatrolTime)
	{
		OnePatrolTime = 0;
		if (EnemyAttackState == EEnemyAttackState::EEAS_ATTACKING || EnemyState == EEnemyState::EES_CHASING) return;
		StartPatrolling();
	}
}

/*******   EnemyPatrol   ******/

//¼øÂû ½ÃÀÛ
void ARaptorEnemyOne::StartPatrolling()
{
	Super::StartPatrolling();

	if (PatrolNum == 0)
	{
		PatrolNum = 1;
		EnemyAIController->MoveToLocation(PatroLocation[0]);
	}
	else
	{
		PatrolNum = 0;
		EnemyAIController->MoveToLocation(PatroLocation[1]);
	}
}

/*******   Death   ******/

//»ç¸Á
void ARaptorEnemyOne::Death()
{
	Super::Death();

	gameMode->ForeEnemySpawnType(true);
}