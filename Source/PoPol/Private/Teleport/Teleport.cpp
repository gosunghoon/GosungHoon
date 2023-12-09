// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport/Teleport.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Character/PopolCharacter.h"

ATeleport::ATeleport()
{
	PrimaryActorTick.bCanEverTick = false;

	TeleportBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	TeleportBox->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();

	TeleportBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleport::OnBoxOverlap);
}

void ATeleport::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PopolCharacter = Cast<APopolCharacter>(OtherActor);
	//대상이 캐릭터라면
	if (OtherActor->ActorHasTag(FName("PlayerCharacter")))
	{
		if (ActorTarget)
		{
			FVector TargetLocation = ActorTarget->GetActorLocation();
			PopolCharacter->SetActorRelativeLocation(TargetLocation, false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}