// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PoPolGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Enemy/EnemyCharacter.h"


APoPolGameMode::APoPolGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
}
//몬스터 젠 시간
void APoPolGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OneEnemyDeath)
	{
		OneSpawnTime += DeltaTime;
		if (OneSpawnTime >= 2.f)
		{
			OneEnemySpawn();
		}
	}
	if (TwoEnemyDeath)
	{
		TwoSpawnTime += DeltaTime;
		if (TwoSpawnTime >= 3.f)
		{
			TwoEnemySpawn();
		}
	}
	if (ThreeEnemyDeath)
	{
		ThreeSpawnTime += DeltaTime;
		if (ThreeSpawnTime >= 3.f)
		{
			ThreeEnemySpawn();
		}
	}
	if (ForeEnemyDeath)
	{
		ForeSpawnTime += DeltaTime;
		if (ForeSpawnTime >= 3.f)
		{
			ForeEnemySpawn();
		}
	}
	if (FiveEnemyDeath)
	{
		FiveSpawnTime += DeltaTime;
		if (FiveSpawnTime >= 3.f)
		{
			FfiveEnemySpawn();
		}
	}
	if (SixEnemyDeath)
	{
		SixSpawnTime += DeltaTime;
		if (SixSpawnTime >= 3.f)
		{
			SixEnemySpawn();
		}
	}
	if (SevenEnemyDeath)
	{
		SevenSpawnTime += DeltaTime;
		if (SevenSpawnTime >= 3.f)
		{
			SevenEnemySpawn();
		}
	}
}
void APoPolGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	const UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		bPauseable = false;
	}
}
//몬스터 젠 여부
bool APoPolGameMode::OneEnemySPawnTyep(bool EnemySpawn)
{
	OneEnemyDeath = EnemySpawn;
	return OneEnemyDeath;
}
bool APoPolGameMode::TwoEnemySPawnTyep(bool EnemySpawn)
{
	TwoEnemyDeath = EnemySpawn;
	return TwoEnemyDeath;
}
bool APoPolGameMode::ThreeEnemySPawnTyep(bool EnemySpawn)
{
	ThreeEnemyDeath = EnemySpawn;
	return ThreeEnemyDeath;
}
bool APoPolGameMode::ForeEnemySpawnType(bool EnemySpawn)
{
	ForeEnemyDeath = EnemySpawn;
	return ForeEnemyDeath;
}
bool APoPolGameMode::FiveEnemySpawnType(bool EnemySpawn)
{
	FiveEnemyDeath = EnemySpawn;
	return FiveEnemyDeath;
}
bool APoPolGameMode::SixEnemySpawnType(bool EnemySpawn)
{
	SixEnemyDeath = EnemySpawn;
	return SixEnemyDeath;
}
bool APoPolGameMode::SevenEnemySpawnType(bool EnemySpawn)
{
	SevenEnemyDeath = EnemySpawn;
	return SevenEnemyDeath;
}
//스폰 타입 설정 및 배경음악 재생
void APoPolGameMode::BeginPlay()
{
	Super::BeginPlay();

	//스폰 설정
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// 배경음악 재생
	AudioComponent->SetSound(MainMusicCue);
	AudioComponent->Play();
}
//몬스터 젠
void APoPolGameMode::OneEnemySpawn()
{
	OneSpawnTime = 0;
	OneEnemyDeath = false;
	GetWorld()->SpawnActor<AEnemyCharacter>(SpawnEnemyCharacter[0], SPawnLocationNum[0], SPawnRotationNum[0], params); //대상 적 스폰
}
void APoPolGameMode::TwoEnemySpawn()
{
	TwoSpawnTime = 0;
	TwoEnemyDeath = false;
	GetWorld()->SpawnActor<AEnemyCharacter>(SpawnEnemyCharacter[1], SPawnLocationNum[1], SPawnRotationNum[1], params); //대상 적 스폰
}
void APoPolGameMode::ThreeEnemySpawn()
{
	ThreeSpawnTime = 0;
	ThreeEnemyDeath = false;
	GetWorld()->SpawnActor<AEnemyCharacter>(SpawnEnemyCharacter[2], SPawnLocationNum[2], SPawnRotationNum[2], params); //대상 적 스폰
}
void APoPolGameMode::ForeEnemySpawn()
{
	ForeSpawnTime = 0;
	ForeEnemyDeath = false;
	GetWorld()->SpawnActor<AEnemyCharacter>(SpawnEnemyCharacter[3], SPawnLocationNum[3], SPawnRotationNum[3], params); //대상 적 스폰
}
void APoPolGameMode::FfiveEnemySpawn()
{
	FiveSpawnTime = 0;
	FiveEnemyDeath = false;
	GetWorld()->SpawnActor<AEnemyCharacter>(SpawnEnemyCharacter[4], SPawnLocationNum[4], SPawnRotationNum[4], params); //대상 적 스폰
}
void APoPolGameMode::SixEnemySpawn()
{
	SixSpawnTime = 0;
	SixEnemyDeath = false;
	GetWorld()->SpawnActor<AEnemyCharacter>(SpawnEnemyCharacter[5], SPawnLocationNum[5], SPawnRotationNum[5], params); //대상 적 스폰
}
void APoPolGameMode::SevenEnemySpawn()
{
	SevenSpawnTime = 0;
	SevenEnemyDeath = false;
	GetWorld()->SpawnActor<AEnemyCharacter>(SpawnEnemyCharacter[6], SPawnLocationNum[6], SPawnRotationNum[6], params); //대상 적 스폰
}
