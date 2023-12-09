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

	//���� �� �ý��� ����
	virtual void BeginPlay() override;


private:
	//Music provided by �����̹���
	//Title : �����Ϸ� ���� �� by ����ǹ���
	//https ://sellbuymusic.com/md/mycwcfz-lcxkcxf
	UPROPERTY(EditAnywhere, Category = Sound)
	class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundCue* MainMusicCue;

	//���� ����
	FActorSpawnParameters params;
	//SpawnEnemy
	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<TSubclassOf<AEnemyCharacter>> SpawnEnemyCharacter;
	//�� FVector
	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<FVector> SPawnLocationNum;
	//�� Rotator
	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<FRotator> SPawnRotationNum;

	//����� �� Ÿ��
	float OneSpawnTime;
	float TwoSpawnTime;
	float ThreeSpawnTime;
	float ForeSpawnTime;
	float FiveSpawnTime;
	float SixSpawnTime;
	float SevenSpawnTime;

	//�� �� ���
	void OneEnemySpawn();
	void TwoEnemySpawn();
	void ThreeEnemySpawn();
	void ForeEnemySpawn();
	void FfiveEnemySpawn();
	void SixEnemySpawn();
	void SevenEnemySpawn();


	//�� �� ����
	bool OneEnemyDeath;
	bool TwoEnemyDeath;
	bool ThreeEnemyDeath;
	bool ForeEnemyDeath;
	bool FiveEnemyDeath;
	bool SixEnemyDeath;
	bool SevenEnemyDeath;


};
