// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/StartGameMode.h"
#include "Widget/GameStartWidget.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

AStartGameMode::AStartGameMode()
{
	StartAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	StartAudioComponent->bAutoActivate = false;
}

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 배경음악 재생
	StartAudioComponent->SetSound(StartMainMusicCue);
	StartAudioComponent->Play();

	GameStartWidget = CreateWidget<UGameStartWidget>(GetWorld(), GameStartWidgetclass);
	if (GameStartWidget)
	{
		GameStartWidget->AddToViewport();
	}
}