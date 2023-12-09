// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DwarfEnemy/EnemyDwarfOne.h"
#include "GameMode/PoPolGameMode.h"
#include "AIController.h"


AEnemyDwarfOne::AEnemyDwarfOne()
{

}
//Tick
void AEnemyDwarfOne::Tick(float DeltaTime)
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
void AEnemyDwarfOne::StartPatrolling()
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
void AEnemyDwarfOne::Death()
{
	Super::Death();

	gameMode->OneEnemySPawnTyep(true);
}