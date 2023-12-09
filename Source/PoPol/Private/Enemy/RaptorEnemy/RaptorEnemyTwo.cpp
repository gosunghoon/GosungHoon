// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RaptorEnemy/RaptorEnemyTwo.h"
#include "GameMode/PoPolGameMode.h"
#include "AIController.h"

ARaptorEnemyTwo::ARaptorEnemyTwo()
{
}

//Tick
void ARaptorEnemyTwo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TwoPatrolTime += DeltaTime;
	if (TwoPatrolTime >= PatrolTime)
	{
		TwoPatrolTime = 0;
		if (EnemyAttackState == EEnemyAttackState::EEAS_ATTACKING || EnemyState == EEnemyState::EES_CHASING) return;
		StartPatrolling();
	}
}

/*******   EnemyPatrol   ******/

//¼øÂû ½ÃÀÛ
void ARaptorEnemyTwo::StartPatrolling()
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
void ARaptorEnemyTwo::Death()
{
	Super::Death();

	gameMode->FiveEnemySpawnType(true);
}
