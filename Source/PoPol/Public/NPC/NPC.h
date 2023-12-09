// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class POPOL_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	/*******   MainSystem   ******/

	//Main
	ANPC();
	virtual void Tick(float DeltaTime) override;

protected:
	/*******   System   ******/

	//Actor ���� �� ����
	virtual void BeginPlay() override;


	/*******   OverlapSystem   ******/

	//Box�浹 ����
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Box�浹 �� ����
	UFUNCTION()
	void OnButtonOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/*******   WidgetSystem   ******/

//NPC ButtonHUD
	UPROPERTY(EditDefaultsOnly, Category = PlayerButton)
	TSubclassOf<class UNPCButtonWidget> NPCButtonWidgetClass;
	//NPC ButtonWidget
	class UNPCButtonWidget* NPCButtonWidget;

private:
	/*******   System   ******/

	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;	//��Ʈ�ѷ�
	UPROPERTY(VisibleAnywhere, Category = "Weapon Porperties")
	class UBoxComponent* NPCBox;	//NPC �浹 �ڽ�
	//NPC �ݸ��� ����
	UPROPERTY(EditAnywhere, Category = Weapon)
	int CollisionNum;


public:
	FORCEINLINE UNPCButtonWidget* GetNPCButtonWidget() const { return NPCButtonWidget; }
};
