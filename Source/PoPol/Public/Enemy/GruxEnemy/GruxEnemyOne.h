// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "GruxEnemyOne.generated.h"

/**
 * 
 */
UCLASS()
class POPOL_API AGruxEnemyOne : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AGruxEnemyOne();
private:
	/*******   Death   ******/

	//���
	virtual void Death() override;
};
