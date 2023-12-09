// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartGameMode.generated.h"

class UGameStartWidget;

UCLASS()
class POPOL_API AStartGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AStartGameMode();
protected:

	/*******   	System   ******/
		//시작 시 시스템 설정
	virtual void BeginPlay() override;

	//Music provided by 셀바이뮤직
	//Title : 출발은 떨렸지만 by 배달의민족
	//https ://sellbuymusic.com/md/mocwcfx-pcxkcxf
	UPROPERTY(EditAnywhere, Category = Sound)
	class UAudioComponent* StartAudioComponent;
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundCue* StartMainMusicCue;

	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<UGameStartWidget> GameStartWidgetclass;
	UGameStartWidget* GameStartWidget;


};
