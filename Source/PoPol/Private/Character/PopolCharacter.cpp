// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PopolCharacter.h"
#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widget/CharacterStat/CharacterMainStatWidget.h"
#include "Widget/CharacterStat/CharacterStatWidget.h"
#include "Item/Weapon/Weapon.h"
#include "Components/BoxComponent.h"
#include "GameInstance/PopolGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Character/State/PopolPlayerState.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Item/PlayerShield/PlayerShield.h"
#include "Widget/CharacterMainWidget/ItemDropWidget.h"
#include "Components/SphereComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Widget/CharacterMainWidget/DeathWidget.h"
#include "Widget/NPCWidget/NPCButtonWidget.h"
#include "NPC/NPC.h"
#include "Widget/GameExitWidget.h"
#include "MotionWarping/PlayerMotionWarpingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PawnSensingComponent.h"
#include "NiagaraFunctionLibrary.h"


/*******   MainSystem   ******/

//Main
APopolCharacter::APopolCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//ĳ���� ȸ��
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//ī�޶� ��ġ��
	BoomCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("BoomCamera"));
	BoomCamera->SetupAttachment(GetRootComponent());
	BoomCamera->TargetArmLength = 300.f;					//ī�޶� ��ġ�� �Ÿ�
	BoomCamera->bUsePawnControlRotation = true;				//ī�޶� ��ġ�� ȸ�� ����

	//ī�޶�
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(BoomCamera);

	//Sphere Collision
	CharSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CharSphere"));
	CharSphere->SetupAttachment(RootComponent);

	//Player - Warp �̵� ��� ��������
	PlayerMotionWarpingComponent = CreateDefaultSubobject<UPlayerMotionWarpingComponent>(TEXT("PlayerMotionWarping"));

	//�⺻ ����
	WeaponType = EWeaponEnable::EWE_Desable;
	ShieldType = EShieldEnable::ESE_Enable;

	//AutoPossessPlayer = EAutoReceiveInput::Player1;

}
//PlayerCollback
void APopolCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &APopolCharacter::Attack);
	PlayerInputComponent->BindAction(FName("Block"), IE_Pressed, this, &APopolCharacter::Block);
	PlayerInputComponent->BindAction(FName("Block"), IE_Repeat, this, &APopolCharacter::Blocking);
	PlayerInputComponent->BindAction(FName("Block"), IE_Released, this, &APopolCharacter::BlockExit);
	PlayerInputComponent->BindAction(FName("WeaponChange_One"), IE_Pressed, this, &APopolCharacter::WeaponChange_One);
	PlayerInputComponent->BindAction(FName("WeaponChange_Two"), IE_Pressed, this, &APopolCharacter::WeaponChange_Two);
	PlayerInputComponent->BindAction(FName("WeaponChange_Three"), IE_Pressed, this, &APopolCharacter::WeaponChange_Three);
	PlayerInputComponent->BindAction(FName("WeaponChange_four"), IE_Pressed, this, &APopolCharacter::WeaponChange_four);
	PlayerInputComponent->BindAction(FName("CameraZoomenlargement"), IE_Pressed, this, &APopolCharacter::CameraZoomenlargement);
	PlayerInputComponent->BindAction(FName("CameraZoomreduction"), IE_Pressed, this, &APopolCharacter::CameraZoomreduction);
	PlayerInputComponent->BindAction(FName("UICharacterStat"), IE_Pressed, this, &APopolCharacter::UICharacterStat);
	PlayerInputComponent->BindAction(FName("Walk"), IE_Pressed, this, &APopolCharacter::MoveType);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &APopolCharacter::Jump);
	PlayerInputComponent->BindAction(FName("Drop"), IE_Pressed, this, &APopolCharacter::Drop);
	PlayerInputComponent->BindAction(FName("Potion"), IE_Pressed, this, &APopolCharacter::Potion);
	PlayerInputComponent->BindAction(FName("NPCTok"), IE_Pressed, this, &APopolCharacter::NPCTok);
	PlayerInputComponent->BindAction(FName("GameMenu"), IE_Pressed, this, &APopolCharacter::GameMenu);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &APopolCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &APopolCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &APopolCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("Lookup"), this, &APopolCharacter::Lookup);
}
//Tick
void APopolCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CharacterMoveType == ECharacterMoveType::ECM_Run)							//ĳ���� ����
	{
		GuardDownTime += DeltaTime;
		if (GuardDownTime >= 2)
		{
			PopolPlayerController->SetHUDNomalStamina(DeltaTime);					//���¹̳� ȸ��
			if (CharacterMoveType != ECharacterMoveType::ECM_Run)
			{
				GuardDownTime = 0;													//���ð� �ʱ�ȭ
			}
		}
	}
	if(CharacterMoveType == ECharacterMoveType::ECM_Block)							//ĳ���� ����
	{
		PopolPlayerController->SetHUDBlockStamina(DeltaTime);						//���¹̳� �ٿ�
		GuardDownTime = 0;															//���ð� �ʱ�ȭ
	}
	if (bDrop)																		//������ ��� ����
	{
		Item->Destroy();															//������ �ı�
		bDrop = false;
	}
	if (ShieldBlockingType == true && BlockingType == EBlockingType::EBT_BLOCK_ONE)
	{
		Blocking();
	}
}

/*******   Item   ******/

//Drop Ȱ��ȭ ����
bool APopolCharacter::SetbDrop(bool Drop)
{
	bDrop = Drop;
	return bDrop;
}


/*******   	System   ******/

//���� �� �ý��� ����
void APopolCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("PlayerCharacter"));	// �±�
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));	//GameInstance
	PopolPlayerState = Cast<APopolPlayerState>(GetPlayerState());	//PlayerStats
	PopolPlayerController = Cast<APopolPlayerController>(GetController());	//PlayerController
	CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerController->GetStatePlayerLevel());	//CharStats
	CharShieldData = PopolGameInstance->GetShieldDefenseData(1);	//ShieldStat


	CharSphere->OnComponentBeginOverlap.AddDynamic(this, &APopolCharacter::OnCharOverlap);	//Collision
	CharSphere->OnComponentEndOverlap.AddDynamic(this, &APopolCharacter::OnCharOverlapEnd);	//Collision
	Shield_Equip();	//ShieldEquip
}
//Move Ÿ��
void APopolCharacter::WalkRun()
{
	if (!WalkState())										//�ȱ� ���°� �ƴ� ���
	{
		MoveSpeed(MoveWalk);								//�ȴ� �ӵ�
		CharacterMoveType = ECharacterMoveType::ECM_Walk;	//�ȴ� ����
	}
	else if (!RunState())									//�޸��� ���°� �ƴ� ���
	{
		MoveSpeed(MoveRun);									//�޸��� �ӵ�
		CharacterMoveType = ECharacterMoveType::ECM_Run;	//�޸��� ����
	}
}
//�ȱ� ����
bool APopolCharacter::WalkState()
{
	return CharacterMoveType == ECharacterMoveType::ECM_Walk;
}
//�޸��� ����
bool APopolCharacter::RunState()
{
	return CharacterMoveType == ECharacterMoveType::ECM_Run;
}
//���� ��
void APopolCharacter::LevelUp()
{
	if (CharacterStats->EXP >= CharacterStats->MaxEXP || CharacterStats->EXP == CharacterStats->MaxEXP)
	{
		//���� �� ��ƼŬ ����
		if (LevelUPParticles && GetWorld())
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				LevelUPParticles,
				GetActorLocation()
			);
			UE_LOG(LogTemp, Log, TEXT("LevelUp"));
		}
	}
}
//Player - Warp �̵� ��� ��������
void APopolCharacter::PlayerTransformWarpTarget()
{
	//FVector TargetLoc = PlayerCombatTarget->GetActorLocation() - PlayerCombatTarget->GetActorForwardVector();
	//FRotator TargetRot = PlayerCombatTarget->GetActorRotation();
	//PlayerMotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("Target"), TargetLoc, TargetRot);
	//FMotionWarpingTarget Target = {};
	//Target.Name = FName("Target");
	//Target.Location = GetLastMovementInputVector();
	//Target.Rotation = GetActorRotation();

	//PlayerMotionWarpingComponent->AddOrUpdateWarpTarget(Target);

	//FVector MovementInputVector = GetLastMovementInputVector();
	//const FVector TargetLocatoin = GetActorLocation();
	//const FVector TargetLoc = (MovementInputVector.GetSafeNormal()* MotionSpeed) + TargetLocatoin;
	//const FRotator TargetRotator = UKismetMathLibrary::MakeRotFromX(MovementInputVector);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyCharacter, OutActors);
	//PlayerMotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("Target"), OutActors[0]->GetActorLocation(), UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), OutActors[0]->GetActorLocation()));
	//PlayerMotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("Target"), TargetLocatoin, GetActorRotation());
}





/*******   	PlayerCollback   ******/

//ī�޶� Ȯ��
void APopolCharacter::CameraZoomenlargement()
{
	if (CameraZoom)
	{
		//CameraZoomSpeed = BoomCamera->TargetArmLength - CameraZoom;
		BoomCamera->TargetArmLength = FMath::Clamp(BoomCamera->TargetArmLength + CameraZoom, CameraZoomMin, CaceraZoomMax);
	}
}
//ī�޶� ���
void APopolCharacter::CameraZoomreduction()
{
	if (CameraZoom)
	{
		//CameraZoomSpeed = BoomCamera->TargetArmLength - CameraZoom;
		BoomCamera->TargetArmLength = FMath::Clamp(BoomCamera->TargetArmLength - CameraZoom, CameraZoomMin, CaceraZoomMax);
	}
}
//����
void APopolCharacter::Jump()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Run)
	{
		Super::Jump();

		CharacterMoveType = ECharacterMoveType::ECM_JUMP;
		PlayMontage(JumpMontage, FName("Jump"));
	}
}
//����
void APopolCharacter::Attack()
{
	if (WeaponType != EWeaponEnable::EWE_Enable) return;
	CharacterMoveType = ECharacterMoveType::ECM_Attack;

	if (Attack_A())
	{
		PlayMontage(AttackMontage, FName("Attack_A"));
		AttackingType = EAttackingType::EAK_ATTACK_ONE;
		CharacterAttackType = ECharacterAttackType::ECA_ATTACKKING_ONE;
	}
	if (Attack_B())
	{
		PlayMontage(AttackMontage, FName("Attack_B"));
		AttackingType = EAttackingType::EAK_ATTACK_TWO;
		CharacterAttackType = ECharacterAttackType::ECA_ATTACKKING_TWO;
	}
	if (Attack_C())
	{
		PlayMontage(AttackMontage, FName("Attack_C"));
		AttackingType = EAttackingType::EAK_ATTACK_THREE;
		CharacterAttackType = ECharacterAttackType::ECA_ATTACKKING_THREE;
	}
	if (Attack_D())
	{
		PlayMontage(AttackMontage, FName("Attack_D"));
		AttackingType = EAttackingType::EAK_ATTACK_FOUE;
		CharacterAttackType = ECharacterAttackType::ECA_ATTACKKING_FOUE;
	}
}
//���� 1��Ű�� ������ ����
void APopolCharacter::WeaponChange_One()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	//TSharedPtr<int8> WeaponRow;
	WeaponRow = 0;													//�ʱ�ȭ
	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetOneWeaponEquipControllType() == true)
		{
			WeaponRow += 1;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//���� �� ����
		}

	}
}
//���� 2��Ű�� ������ ����
void APopolCharacter::WeaponChange_Two()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	WeaponRow = 0;													//�ʱ�ȭ
	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetTwoWeaponEquipControllType() == true)
		{
			WeaponRow += 2;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//���� �� ����
		}
	}

}
//���� 3��Ű�� ������ ����
void APopolCharacter::WeaponChange_Three()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	WeaponRow = 0;													//�ʱ�ȭ
	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetThreeWeaponEquipControllType() == true)
		{
			WeaponRow += 3;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//���� �� ����
		}
	}
}
//���� 4��Ű�� ������ ����
void APopolCharacter::WeaponChange_four()
{

	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	WeaponRow = 0;													//�ʱ�ȭ

	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetForeWeaponEquipControllType() == true)
		{
			WeaponRow += 4;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//���� �� ����
		}
	}
}
//���
void APopolCharacter::Block()
{
	if (!ATTACK_WAIT() || ShieldType != EShieldEnable::ESE_Enable) return;

	CharacterMoveType = ECharacterMoveType::ECM_Block;
	PlayMontage(ShieldMontage, FName("Player_Shield_Start"));
}
//��� ����
void APopolCharacter::Blocking()
{
	PlayMontage(ShieldMontage, FName("Player_Shield_Loop"));
}
//��� ����
void APopolCharacter::BlockExit()
{
	if (!ATTACK_WAIT() || ShieldType != EShieldEnable::ESE_Enable) return;

	PlayMontage(ShieldMontage, FName("Player_Shield_End"));
	ShieldBlockingType = false;
	CharacterMoveType = ECharacterMoveType::ECM_Run;
	BlockingType = EBlockingType::EBT_BLOCK_WAIT;
}
//Move Type
void APopolCharacter::MoveType()
{
	WalkRun();
}
//Drop
void APopolCharacter::Drop()
{
	if (ItemCollision)
	{
		ItemDropWidget->OnButtonClicked();						//DropWIdget�� ��ư Ŭ�� �Լ� ����
		ItemCollision = false;
	}
}
//��ȭ
void APopolCharacter::NPCTok()
{
	if (bNPC)
	{
		NPCButtonWidget->OnButtonClicked();		//DropWIdget�� ��ư Ŭ�� �Լ� ����
		bNPC = false;
	}
}
//Potion
void APopolCharacter::Potion()
{
	//���� �� ��ƼŬ ����
	if (PotionParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PotionParticles,
			GetActorLocation()
		);
		UE_LOG(LogTemp, Log, TEXT("PotionParticles"));
	}
	PopolPlayerController->SetHUDPosionh(PopolPlayerController->GetPlayerPotionControll());
	if (CharacterStats->HP >= PopolPlayerController->GetPlayerMaxHPControll())
	{
		CharacterStats->HP = PopolPlayerController->GetPlayerMaxHPControll();
	}
}
//��, ��
void APopolCharacter::MoveForward(float Value)
{
	if (!ATTACK_WAIT() || CharacterMoveType == ECharacterMoveType::ECM_Attack || BlockingType == EBlockingType::EBT_BLOCK_ONE) return;

	if ((Controller != NULL) && (Value != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}
//����, ������
void APopolCharacter::MoveRight(float Value)
{
	if (!ATTACK_WAIT() || CharacterMoveType == ECharacterMoveType::ECM_Attack || BlockingType == EBlockingType::EBT_BLOCK_ONE) return;

	if ((Controller != NULL) && (Value != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
//���콺 �Ʒ�, ��
void APopolCharacter::Lookup(float Value)
{
	AddControllerPitchInput(Value);
}
//���콺 ����, ������
void APopolCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}


/*******   	Collision   ******/

//Character�浹 ����
void APopolCharacter::OnCharOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Item")))										//����� ������
	{
		Item = Cast<AItem>(OtherActor);												//Item Cast
		if (Item)
		{
			ItemCollision = true;
			//������ ��ư Widget
			ItemDropWidget = Cast<UItemDropWidget>(Item->GetItemDropWidget());		//Item�� �ִ� DropWidget
		}
	}
	if (OtherActor->ActorHasTag(FName("NPC")))										//����� ������
	{
		NPC = Cast<ANPC>(OtherActor);												//Item Cast
		if (NPC)
		{
			bNPC = true;
			//������ ��ư Widget
			NPCButtonWidget = Cast<UNPCButtonWidget>(NPC->GetNPCButtonWidget());		//Item�� �ִ� DropWidget
		}
	}
}
//Box�浹 �� ����
void APopolCharacter::OnCharOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName("Item")))										//����� ������
	{
		Item = Cast<AItem>(OtherActor);												//Item Cast
		if (Item)
		{
			ItemCollision = false;
			//������ ��ư Widget
			if (ItemDropWidget != nullptr)
			{
				ItemDropWidget->RemoveFromParent();
			}

		}
	}


	if (OtherActor->ActorHasTag(FName("NPC")))										//����� ������
	{
		NPC = Cast<ANPC>(OtherActor);												//Item Cast
		if (NPC)
		{
			bNPC = false;
			//Widget ����
			if (NPCButtonWidget != nullptr)
			{
				NPCButtonWidget->RemoveFromParent();
			}
		}
	}
}


/*******   	Hit   ******/

//�¾��� ���
void APopolCharacter::GetHit(const FVector& ImpactPoint)
{
	Super::GetHit(ImpactPoint);

	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;

	if (CharacterMoveType != ECharacterMoveType::ECM_Block)
	{
		DirectionalHitReact(ImpactPoint);								//Hit
	}

	CharacterMoveType = ECharacterMoveType::ECM_HIT;

	if (PopolPlayerController->PlayerIsDead())
	{
		Death();														//����
	}
	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
}
//�޴� ������
float APopolCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Block)
	{
		PlayerLastDamage = Damage(DamageAmount, (PopolPlayerController->GetPlayerDefenseControll() + CharShieldData->defense));	//������ = Char���� + Shield����
		if (PopolPlayerController->GetStaminaPercent() > 0.f && CharacterStats->Stamina > 0.f)
		{
			StaminaDown = 10.f;	//���¹̳� �ٿ
			BlockingType = EBlockingType::EBT_BLOCK_ONE;
			PlayMontage(ShieldMontage, FName("Player_Shield_Hit"));
			PopolPlayerController->SetHUDBlockStamina(StaminaDown);	//���¹̳� �ٿ�
		}
	}
	else
	{
		PlayerLastDamage = Damage(DamageAmount, PopolPlayerController->GetPlayerDefenseControll());	//������ = Char����
	}
	PopolPlayerController->SetHUDHealth(PlayerLastDamage);	//ü�� �ۼ�Ʈ ���� �� �ؽ�Ʈ
	if (PopolPlayerController->PlayerIsDead())
	{
		Death();	//���
	}
	return PlayerLastDamage;
}
//Hit�� ����
void APopolCharacter::HitEnd()
{
	CharacterMoveType = ECharacterMoveType::ECM_Run;					//������ ���� ����
	AttackingType = EAttackingType::EAK_ATTACK_WAIT;					//���� ��Ÿ�� ������ ���� ����
	CharacterAttackType = ECharacterAttackType::ECA_COMMONLY;			//���� ��Ÿ�� ���� ����
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_FOUE_END;			//���� ��Ÿ�� ���� ���� ����
}


/*******   	Death   ******/

//����
void APopolCharacter::Death()
{
	Super::Death();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);		//�ݸ��� ����
	GetMovementComponent()->StopMovementImmediately();	//��� ������ ����
	DetachFromControllerPendingDestroy();	//���� ��Ʈ�ѷ� �и�
	if (Shield != NULL)
	{
		Shield->Destroy();	//���а� �����Ѵٸ� �ı�
	}
	if (Weapon != NULL)
	{
		Weapon->Destroy();	//���Ⱑ �����Ѵٸ� �ı�
	}
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &APopolCharacter::RespawnTimer, 1.0f, true);
}
//��ü ����
void APopolCharacter::DeathEnd()
{
	SetLifeSpan(0.5f);			//�ð� ���� �� ����
}
//���� �ð�
void APopolCharacter::RespawnTimer()
{
	RespawnTime = RespawnTime - 1.0f;
	if (RespawnTime < 1)
	{
		GetWorldTimerManager().ClearTimer(RespawnHandle);
		RespawnTimeHasFinished();
	}
}
//����
void APopolCharacter::RespawnTimeHasFinished()
{
	SetLifeSpan(0.5f);
	DeathWidget = CreateWidget<UDeathWidget>(PopolPlayerController, DeathWidgetClass);
	DeathWidget->AddToViewport();
}


/*******   	Widget   ******/

//ĳ���� ���� ��ư
void APopolCharacter::UICharacterStat()
{
	//MainIwdgetŸ���� ������ CharacterStatnUIClass�� ���ͼ� CharacterStatWidgetŸ������ ��ȯ�� ������ش�.
	CharacterMainStatWidget = CreateWidget<UCharacterMainStatWidget>(PopolPlayerController, CharacterMainStatUIClass);
	//MAinWidgetŸ���� Widget�� �ҷ��� ������ ���� null�� �ƴ϶��
	if (CharacterMainStatWidget)
	{
		CharacterMainStatWidget->AddToViewport();
		PopolPlayerController->SetPause(true);			//���� �Ͻ�����
		PopolPlayerController->bShowMouseCursor = true; //���콺 Ŀ��
	}

}
//GameMenu
void APopolCharacter::GameMenu()
{
	//MainIwdgetŸ���� ������ CharacterStatnUIClass�� ���ͼ� CharacterStatWidgetŸ������ ��ȯ�� ������ش�.
	GameExitWidget = CreateWidget<UGameExitWidget>(PopolPlayerController, UGameExitWidgetclass);
	//MAinWidgetŸ���� Widget�� �ҷ��� ������ ���� null�� �ƴ϶��
	if (GameExitWidget)
	{
		GameExitWidget->AddToViewport();
		PopolPlayerController->SetPause(true);			//���� �Ͻ�����
		PopolPlayerController->bShowMouseCursor = true; //���콺 Ŀ��
	}
}


/*******   	Weapon  ******/

//���� ����
void APopolCharacter::Weapon_Equip(int row)
{
	if (Weapon != NULL)
	{
		Weapon->Destroy();	//���Ⱑ �����Ѵٸ� �ı�
	}

	if (PopolGameInstance != nullptr)
	{
		if (Weapon != NULL)
		{
			Weapon->Destroy();	//���Ⱑ �����Ѵٸ� �ı�
		}
		CharWeaponData = PopolGameInstance->GetWeaponDamageData(row);	//DataTable�� �� Ȯ��
		PopolPlayerController->SetEquipWeaponNum_Controller(row);
		UWorld* World = GetWorld();
		if (World)
		{
			EquipWeapon = World->SpawnActor<AWeapon>(CharWeaponData->WeaponClass);	//���� ���⸦ ���忡 �ҷ����ش�.
			if (EquipWeapon)
			{
				EquipWeapon->AttackMeshToSocket(GetMesh(), FName("WeaponSocket"), this, this);	//���Ͽ� ����
				Weapon = EquipWeapon;	//���� ����
			}
		}
	}
}
//���� �浹 Ȱ��ȭ
void APopolCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquipWeapon && EquipWeapon->GetWeaponBox())
	{
		EquipWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);	//�ݸ��� ���� ����
		EquipWeapon->IgnoreActors.Empty();
	}
}


/*******   	Shield  ******/

//���� ����
void APopolCharacter::Shield_Equip()
{
	if (Shield != NULL)
	{
		Shield->Destroy();																		//���а� �����Ѵٸ� �ı�
	}
	if (PopolGameInstance != nullptr)
	{
		if (Shield != NULL)
		{
			Shield->Destroy();																	//���а� �����Ѵٸ� �ı�
		}
		CharShieldData = PopolGameInstance->GetShieldDefenseData(1);							//DataTable�� �� Ȯ��
		UWorld* World = GetWorld();
		if (World)
		{
			PlayerShield = World->SpawnActor<APlayerShield>(CharShieldData->ShieldClass);	//���� ���⸦ ���忡 �ҷ����ش�.
			if (PlayerShield)
			{
				ShieldType = EShieldEnable::ESE_Enable;
				PlayerShield->AttackMeshToSocket(GetMesh(), FName("ShieldSocket"), this, this);	//���Ͽ� ����
				Shield = PlayerShield;	//���� ����
			}
		}
	}
}
//���� �浹 ��Ȱ��ȭ
void APopolCharacter::SetShieldCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (PlayerShield && PlayerShield->GetShieldBox())
	{
		PlayerShield->GetShieldBox()->SetCollisionEnabled(CollisionEnabled);	//�ݸ��� ���� ����
		PlayerShield->IgnoreActors.Empty();
	}
}
//���� ���� ��� ��
void APopolCharacter::ShieldBlockStart()
{
	ShieldBlockingType = true;
	BlockingType = EBlockingType::EBT_BLOCK_ONE;
}
//���� ��� ��
void APopolCharacter::ShieldBlockEnd()
{
	BlockingType = EBlockingType::EBT_BLOCK_WAIT;
}


/*******   	AttackSystem  ******/

//���� ��� ��
bool APopolCharacter::ATTACK_WAIT()
{
	return AttackingType == EAttackingType::EAK_ATTACK_WAIT;
}
//Attack_A����
bool APopolCharacter::Attack_A()
{
	return AttackingType == EAttackingType::EAK_ATTACK_WAIT && AttackingType != EAttackingType::EAK_ATTACK_ONE && CharacterAttackType != ECharacterAttackType::ECA_ATTACKKING_ONE && AttackingEndType != EAttackingEndType::EAKE_ATTACK_ONE_END;
}
//Attack_B����
bool APopolCharacter::Attack_B()
{
	return AttackingType == EAttackingType::EAK_ATTACK_ONE && AttackingType != EAttackingType::EAK_ATTACK_TWO && CharacterAttackType == ECharacterAttackType::ECA_ATTACKKING_ONE && AttackingEndType == EAttackingEndType::EAKE_ATTACK_ONE_END;
}
//Attack_C����
bool APopolCharacter::Attack_C()
{
	return AttackingType == EAttackingType::EAK_ATTACK_TWO && AttackingType != EAttackingType::EAK_ATTACK_THREE && CharacterAttackType == ECharacterAttackType::ECA_ATTACKKING_TWO && AttackingEndType == EAttackingEndType::EAKE_ATTACK_TWO_END;
}
//Attack_D����
bool APopolCharacter::Attack_D()
{
	return AttackingType == EAttackingType::EAK_ATTACK_THREE && AttackingType != EAttackingType::EAK_ATTACK_FOUE && CharacterAttackType == ECharacterAttackType::ECA_ATTACKKING_THREE && AttackingEndType == EAttackingEndType::EAKE_ATTACK_THREE_END;
}
//���� ��
void APopolCharacter::AttackEnd()
{
	CharacterMoveType = ECharacterMoveType::ECM_Run;			//������ ���� ����
	AttackingType = EAttackingType::EAK_ATTACK_WAIT;			//���� ��Ÿ�� ������ ���� ����
	CharacterAttackType = ECharacterAttackType::ECA_COMMONLY;	//���� ��Ÿ�� ���� ����
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_NOMAL;	//���� ��Ÿ�� ���� ���� ����
}
//���� ��Ÿ�� 1�� ���� ����
void APopolCharacter::vAttacking_One_End()
{
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_ONE_END;
}
//���� ��Ÿ�� 2�� ���� ����
void APopolCharacter::vAttacking_Two_End()
{
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_TWO_END;
}
//���� ��Ÿ�� 3�� ���� ����
void APopolCharacter::vAttacking_Three_End()
{
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_THREE_END;
}


/*******   	JumpSystem  ******/

//���� ��
void APopolCharacter::JumpEnd()
{
	CharacterMoveType = ECharacterMoveType::ECM_Run;
}