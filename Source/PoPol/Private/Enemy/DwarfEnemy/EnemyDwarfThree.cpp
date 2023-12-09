// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DwarfEnemy/EnemyDwarfThree.h"
#include "GameMode/PoPolGameMode.h"
#include "AIController.h"

AEnemyDwarfThree::AEnemyDwarfThree()
{
}

void AEnemyDwarfThree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ThreePatrolTime += DeltaTime;
	if (ThreePatrolTime >= PatrolTime)
	{
		ThreePatrolTime = 0;
		if (EnemyAttackState == EEnemyAttackState::EEAS_ATTACKING || EnemyState == EEnemyState::EES_CHASING) return;
		StartPatrolling();
	}
}

/*******   EnemyPatrol   ******/

//¼øÂû ½ÃÀÛ
void AEnemyDwarfThree::StartPatrolling()
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
void AEnemyDwarfThree::Death()
{
	Super::Death();

	gameMode->ThreeEnemySPawnTyep(true);
}