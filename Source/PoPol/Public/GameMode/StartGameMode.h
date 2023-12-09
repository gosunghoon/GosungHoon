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
		//���� �� �ý��� ����
	virtual void BeginPlay() override;

	//Music provided by �����̹���
	//Title : ����� �������� by ����ǹ���
	//https ://sellbuymusic.com/md/mocwcfx-pcxkcxf
	UPROPERTY(EditAnywhere, Category = Sound)
	class UAudioComponent* StartAudioComponent;
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundCue* StartMainMusicCue;

	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<UGameStartWidget> GameStartWidgetclass;
	UGameStartWidget* GameStartWidget;


};
