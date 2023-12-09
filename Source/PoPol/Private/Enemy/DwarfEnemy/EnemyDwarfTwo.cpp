// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DwarfEnemy/EnemyDwarfTwo.h"
#include "GameMode/PoPolGameMode.h"
#include "AIController.h"

AEnemyDwarfTwo::AEnemyDwarfTwo()
{
}

void AEnemyDwarfTwo::Tick(float DeltaTime)
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

//���� ����
void AEnemyDwarfTwo::StartPatrolling()
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

//���
void AEnemyDwarfTwo::Death()
{
	Super::Death();

	gameMode->TwoEnemySPawnTyep(true);
}