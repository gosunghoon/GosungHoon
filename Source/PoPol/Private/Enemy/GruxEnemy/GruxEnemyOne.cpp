// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/GruxEnemy/GruxEnemyOne.h"
#include "GameMode/PoPolGameMode.h"
#include "Character/Controller/PopolPlayerController.h"


AGruxEnemyOne::AGruxEnemyOne()
{
}

/*******   Death   ******/

//»ç¸Á
void AGruxEnemyOne::Death()
{
	Super::Death();

	PopolPlayerController->SetEnemyGruxDeath(1);
	gameMode->SevenEnemySpawnType(true);
}