// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Type/CharacterType.h"
#include "Item.generated.h"


UCLASS()
class POPOL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	/*******   System   ******/

	//Main
	AItem();
	virtual void Tick(float DeltaTime) override;

	/*******   AttackSystem   ******/

	//���� ��ȣ
	UPROPERTY(EditAnywhere, Category = Weapon)
	int WeaponNum;

protected:
	/*******   System   ******/

	//���� �� System ����
	virtual void BeginPlay() override;
	//Sin�� �̵�
	UFUNCTION(BlueprintPure)
	float TransformedSin();

	/*******   OverlapSystem   ******/

	//Shere�浹 ����
	UFUNCTION()
	void OnButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Shere�浹 �� ����
	UFUNCTION()
	void OnButtonOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	/*******   	EnumType  ******/

	//Item Type
	UPROPERTY(VisibleAnywhere)
	EItemState ItemState;

private:
	/*******   System   ******/

	//��Ʈ�ѷ�
	UPROPERTY()
	class APopolPlayerController* PopolPlayerController;
	//�÷��̾�
	class APopolCharacter* PopolCharacter;
	//Sin �����̴� �ð�
	UPROPERTY(EditAnywhere, Category = System)
	float RunningTime;
	//����
	UPROPERTY(EditDefaultsOnly, Category = System)
	float Amplitude = 0.25f;
	//�պ� �ð�
	UPROPERTY(EditInstanceOnly, Category = System)
	float TimeConstant = 5.f;

	/*******   ItemSystem   ******/

	//Item Mesh
	UPROPERTY(VisibleAnywhere, Category = "Shield Porperties")
	class UStaticMeshComponent* ItemMesh;
	//Sphere Collision
	UPROPERTY(EditAnywhere, Category = "Shield Porperties")
	class USphereComponent* ItemSphere;
	//������ �ݸ��� ����
	UPROPERTY(EditAnywhere, Category = Weapon)
	int CollisionNum;

	//������ ��ƼŬ ����
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* EmbersEffect;


	/*******   WidgetSystem   ******/

	//�÷��̾� HUD
	UPROPERTY(EditDefaultsOnly, Category = PlayerButton)
	TSubclassOf<class UItemDropWidget> PlayerItemDropClass;
	//��� �����
	class UItemDropWidget* ItemDropWidget;


public:
	FORCEINLINE UItemDropWidget* GetItemDropWidget() const { return ItemDropWidget; }

};
