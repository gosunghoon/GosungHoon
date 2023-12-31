// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

class POPOL_API IHitInterface
{
	GENERATED_BODY()

public:

	virtual void GetHit(const FVector& ImpactPoint) = 0;	//히트 포인트
};
