// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PoPolGameMode.generated.h"


class AEnemyCharacter;

UCLASS()
class POPOL_API APoPolGameMode : public AGameMode
{
	GENERATED_BODY()
	


public:
	APoPolGameMode();
	//Tick
	virtual void Tick(float DeltaTime) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	bool OneEnemySPawnTyep(bool EnemySpawn); 
	bool TwoEnemySPawnTyep(bool EnemySpawn);
	bool ThreeEnemySPawnTyep(bool EnemySpawn);
	bool ForeEnemySpawnType(bool EnemySpawn);
	bool FiveEnemySpawnType(bool EnemySpawn);
	bool SixEnemySpawnType(bool EnemySpawn);
	bool SevenEnemySpawnType(bool EnemySpawn);
protected:
	/*******   	System   ******/

	//시작 시 시스템 설정
	virtual void BeginPlay() override;


private:
	//Music provided by 셀바이뮤직
	//Title : 선물하러 가는 길 by 배달의민족
	//https ://sellbuymusic.com/md/mycwcfz-lcxkcxf
	UPROPERTY(EditAnywhere, Category = Sound)
	class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundCue* MainMusicCue;

	//스폰 설정
	FActorSpawnParameters params;
	//SpawnEnemy
	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<TSubclassOf<AEnemyCharacter>> SpawnEnemyCharacter;
	//적 FVector
	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<FVector> SPawnLocationNum;
	//적 Rotator
	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<FRotator> SPawnRotationNum;

	//드워프 젠 타임
	float OneSpawnTime;
	float TwoSpawnTime;
	float ThreeSpawnTime;
	float ForeSpawnTime;
	float FiveSpawnTime;
	float SixSpawnTime;
	float SevenSpawnTime;

	//적 젠 대상
	void OneEnemySpawn();
	void TwoEnemySpawn();
	void ThreeEnemySpawn();
	void ForeEnemySpawn();
	void FfiveEnemySpawn();
	void SixEnemySpawn();
	void SevenEnemySpawn();


	//적 젠 여부
	bool OneEnemyDeath;
	bool TwoEnemyDeath;
	bool ThreeEnemyDeath;
	bool ForeEnemyDeath;
	bool FiveEnemyDeath;
	bool SixEnemyDeath;
	bool SevenEnemyDeath;


};
