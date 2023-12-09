// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "GolemEnemyOne.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API AGolemEnemyOne : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AGolemEnemyOne();
private:
	/*******   Death   ******/

	//»ç¸Á
	virtual void Death() override;
};
