// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/GolemEnemy/GolemEnemyOne.h"
#include "GameMode/PoPolGameMode.h"


AGolemEnemyOne::AGolemEnemyOne()
{
}

/*******   Death   ******/

//»ç¸Á
void AGolemEnemyOne::Death()
{
	Super::Death();

	gameMode->SixEnemySpawnType(true);
}