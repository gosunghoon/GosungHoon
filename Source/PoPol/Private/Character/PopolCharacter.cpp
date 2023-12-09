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

	//캐릭터 회전
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//카메라 거치대
	BoomCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("BoomCamera"));
	BoomCamera->SetupAttachment(GetRootComponent());
	BoomCamera->TargetArmLength = 300.f;					//카메라 거치대 거리
	BoomCamera->bUsePawnControlRotation = true;				//카메라 거치대 회전 여부

	//카메라
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(BoomCamera);

	//Sphere Collision
	CharSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CharSphere"));
	CharSphere->SetupAttachment(RootComponent);

	//Player - Warp 이동 대상 가져오기
	PlayerMotionWarpingComponent = CreateDefaultSubobject<UPlayerMotionWarpingComponent>(TEXT("PlayerMotionWarping"));

	//기본 상태
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
	if (CharacterMoveType == ECharacterMoveType::ECM_Run)							//캐릭터 상태
	{
		GuardDownTime += DeltaTime;
		if (GuardDownTime >= 2)
		{
			PopolPlayerController->SetHUDNomalStamina(DeltaTime);					//스태미너 회복
			if (CharacterMoveType != ECharacterMoveType::ECM_Run)
			{
				GuardDownTime = 0;													//대기시간 초기화
			}
		}
	}
	if(CharacterMoveType == ECharacterMoveType::ECM_Block)							//캐릭터 상태
	{
		PopolPlayerController->SetHUDBlockStamina(DeltaTime);						//스태미너 다운
		GuardDownTime = 0;															//대기시간 초기화
	}
	if (bDrop)																		//아이템 드롭 여부
	{
		Item->Destroy();															//아이템 파괴
		bDrop = false;
	}
	if (ShieldBlockingType == true && BlockingType == EBlockingType::EBT_BLOCK_ONE)
	{
		Blocking();
	}
}

/*******   Item   ******/

//Drop 활성화 여부
bool APopolCharacter::SetbDrop(bool Drop)
{
	bDrop = Drop;
	return bDrop;
}


/*******   	System   ******/

//시작 시 시스템 설정
void APopolCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("PlayerCharacter"));	// 태그
	PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));	//GameInstance
	PopolPlayerState = Cast<APopolPlayerState>(GetPlayerState());	//PlayerStats
	PopolPlayerController = Cast<APopolPlayerController>(GetController());	//PlayerController
	CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerController->GetStatePlayerLevel());	//CharStats
	CharShieldData = PopolGameInstance->GetShieldDefenseData(1);	//ShieldStat


	CharSphere->OnComponentBeginOverlap.AddDynamic(this, &APopolCharacter::OnCharOverlap);	//Collision
	CharSphere->OnComponentEndOverlap.AddDynamic(this, &APopolCharacter::OnCharOverlapEnd);	//Collision
	Shield_Equip();	//ShieldEquip
}
//Move 타입
void APopolCharacter::WalkRun()
{
	if (!WalkState())										//걷기 상태가 아닐 경우
	{
		MoveSpeed(MoveWalk);								//걷는 속도
		CharacterMoveType = ECharacterMoveType::ECM_Walk;	//걷는 상태
	}
	else if (!RunState())									//달리기 상태가 아닐 경우
	{
		MoveSpeed(MoveRun);									//달리는 속도
		CharacterMoveType = ECharacterMoveType::ECM_Run;	//달리는 상태
	}
}
//걷기 상태
bool APopolCharacter::WalkState()
{
	return CharacterMoveType == ECharacterMoveType::ECM_Walk;
}
//달리기 상태
bool APopolCharacter::RunState()
{
	return CharacterMoveType == ECharacterMoveType::ECM_Run;
}
//레벨 업
void APopolCharacter::LevelUp()
{
	if (CharacterStats->EXP >= CharacterStats->MaxEXP || CharacterStats->EXP == CharacterStats->MaxEXP)
	{
		//레벨 업 파티클 생성
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
//Player - Warp 이동 대상 가져오기
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

//카메라 확대
void APopolCharacter::CameraZoomenlargement()
{
	if (CameraZoom)
	{
		//CameraZoomSpeed = BoomCamera->TargetArmLength - CameraZoom;
		BoomCamera->TargetArmLength = FMath::Clamp(BoomCamera->TargetArmLength + CameraZoom, CameraZoomMin, CaceraZoomMax);
	}
}
//카메라 축소
void APopolCharacter::CameraZoomreduction()
{
	if (CameraZoom)
	{
		//CameraZoomSpeed = BoomCamera->TargetArmLength - CameraZoom;
		BoomCamera->TargetArmLength = FMath::Clamp(BoomCamera->TargetArmLength - CameraZoom, CameraZoomMin, CaceraZoomMax);
	}
}
//점프
void APopolCharacter::Jump()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Run)
	{
		Super::Jump();

		CharacterMoveType = ECharacterMoveType::ECM_JUMP;
		PlayMontage(JumpMontage, FName("Jump"));
	}
}
//공격
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
//숫자 1번키로 아이템 장착
void APopolCharacter::WeaponChange_One()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	//TSharedPtr<int8> WeaponRow;
	WeaponRow = 0;													//초기화
	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetOneWeaponEquipControllType() == true)
		{
			WeaponRow += 1;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//생성 및 부착
		}

	}
}
//숫자 2번키로 아이템 장착
void APopolCharacter::WeaponChange_Two()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	WeaponRow = 0;													//초기화
	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetTwoWeaponEquipControllType() == true)
		{
			WeaponRow += 2;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//생성 및 부착
		}
	}

}
//숫자 3번키로 아이템 장착
void APopolCharacter::WeaponChange_Three()
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	WeaponRow = 0;													//초기화
	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetThreeWeaponEquipControllType() == true)
		{
			WeaponRow += 3;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//생성 및 부착
		}
	}
}
//숫자 4번키로 아이템 장착
void APopolCharacter::WeaponChange_four()
{

	if (CharacterMoveType == ECharacterMoveType::ECM_Attack) return;
	WeaponRow = 0;													//초기화

	if (WeaponRow == 0)
	{
		if (PopolPlayerController->GetForeWeaponEquipControllType() == true)
		{
			WeaponRow += 4;
			WeaponType = EWeaponEnable::EWE_Enable;
			Weapon_Equip(WeaponRow);								//생성 및 부착
		}
	}
}
//방어
void APopolCharacter::Block()
{
	if (!ATTACK_WAIT() || ShieldType != EShieldEnable::ESE_Enable) return;

	CharacterMoveType = ECharacterMoveType::ECM_Block;
	PlayMontage(ShieldMontage, FName("Player_Shield_Start"));
}
//방어 지속
void APopolCharacter::Blocking()
{
	PlayMontage(ShieldMontage, FName("Player_Shield_Loop"));
}
//방어 종료
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
		ItemDropWidget->OnButtonClicked();						//DropWIdget의 버튼 클릭 함수 실행
		ItemCollision = false;
	}
}
//대화
void APopolCharacter::NPCTok()
{
	if (bNPC)
	{
		NPCButtonWidget->OnButtonClicked();		//DropWIdget의 버튼 클릭 함수 실행
		bNPC = false;
	}
}
//Potion
void APopolCharacter::Potion()
{
	//레벨 업 파티클 생성
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
//앞, 뒤
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
//왼쪽, 오른쪽
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
//마우스 아래, 위
void APopolCharacter::Lookup(float Value)
{
	AddControllerPitchInput(Value);
}
//마우스 왼쪽, 오른쪽
void APopolCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}


/*******   	Collision   ******/

//Character충돌 반응
void APopolCharacter::OnCharOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Item")))										//대상이 아이템
	{
		Item = Cast<AItem>(OtherActor);												//Item Cast
		if (Item)
		{
			ItemCollision = true;
			//아이템 버튼 Widget
			ItemDropWidget = Cast<UItemDropWidget>(Item->GetItemDropWidget());		//Item에 있는 DropWidget
		}
	}
	if (OtherActor->ActorHasTag(FName("NPC")))										//대상이 아이템
	{
		NPC = Cast<ANPC>(OtherActor);												//Item Cast
		if (NPC)
		{
			bNPC = true;
			//아이템 버튼 Widget
			NPCButtonWidget = Cast<UNPCButtonWidget>(NPC->GetNPCButtonWidget());		//Item에 있는 DropWidget
		}
	}
}
//Box충돌 끝 반응
void APopolCharacter::OnCharOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName("Item")))										//대상이 아이템
	{
		Item = Cast<AItem>(OtherActor);												//Item Cast
		if (Item)
		{
			ItemCollision = false;
			//아이템 버튼 Widget
			if (ItemDropWidget != nullptr)
			{
				ItemDropWidget->RemoveFromParent();
			}

		}
	}


	if (OtherActor->ActorHasTag(FName("NPC")))										//대상이 아이템
	{
		NPC = Cast<ANPC>(OtherActor);												//Item Cast
		if (NPC)
		{
			bNPC = false;
			//Widget 삭제
			if (NPCButtonWidget != nullptr)
			{
				NPCButtonWidget->RemoveFromParent();
			}
		}
	}
}


/*******   	Hit   ******/

//맞았을 경우
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
		Death();														//죽음
	}
	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
}
//받는 데미지
float APopolCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CharacterMoveType == ECharacterMoveType::ECM_Block)
	{
		PlayerLastDamage = Damage(DamageAmount, (PopolPlayerController->GetPlayerDefenseControll() + CharShieldData->defense));	//데미지 = Char방어력 + Shield방어력
		if (PopolPlayerController->GetStaminaPercent() > 0.f && CharacterStats->Stamina > 0.f)
		{
			StaminaDown = 10.f;	//스태미너 다운량
			BlockingType = EBlockingType::EBT_BLOCK_ONE;
			PlayMontage(ShieldMontage, FName("Player_Shield_Hit"));
			PopolPlayerController->SetHUDBlockStamina(StaminaDown);	//스태미너 다운
		}
	}
	else
	{
		PlayerLastDamage = Damage(DamageAmount, PopolPlayerController->GetPlayerDefenseControll());	//데미지 = Char방어력
	}
	PopolPlayerController->SetHUDHealth(PlayerLastDamage);	//체력 퍼센트 설정 및 텍스트
	if (PopolPlayerController->PlayerIsDead())
	{
		Death();	//사망
	}
	return PlayerLastDamage;
}
//Hit끝 변경
void APopolCharacter::HitEnd()
{
	CharacterMoveType = ECharacterMoveType::ECM_Run;					//움직임 상태 여부
	AttackingType = EAttackingType::EAK_ATTACK_WAIT;					//공격 몽타주 실행중 상태 여부
	CharacterAttackType = ECharacterAttackType::ECA_COMMONLY;			//공격 몽타주 상태 여부
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_FOUE_END;			//공격 몽타주 끝난 상태 여부
}


/*******   	Death   ******/

//죽음
void APopolCharacter::Death()
{
	Super::Death();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);		//콜리전 상태
	GetMovementComponent()->StopMovementImmediately();	//모든 움직임 정지
	DetachFromControllerPendingDestroy();	//폰과 컨트롤러 분리
	if (Shield != NULL)
	{
		Shield->Destroy();	//방패가 존재한다면 파괴
	}
	if (Weapon != NULL)
	{
		Weapon->Destroy();	//무기가 존재한다면 파괴
	}
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &APopolCharacter::RespawnTimer, 1.0f, true);
}
//시체 제거
void APopolCharacter::DeathEnd()
{
	SetLifeSpan(0.5f);			//시간 지난 후 제거
}
//스폰 시간
void APopolCharacter::RespawnTimer()
{
	RespawnTime = RespawnTime - 1.0f;
	if (RespawnTime < 1)
	{
		GetWorldTimerManager().ClearTimer(RespawnHandle);
		RespawnTimeHasFinished();
	}
}
//스폰
void APopolCharacter::RespawnTimeHasFinished()
{
	SetLifeSpan(0.5f);
	DeathWidget = CreateWidget<UDeathWidget>(PopolPlayerController, DeathWidgetClass);
	DeathWidget->AddToViewport();
}


/*******   	Widget   ******/

//캐릭터 스탯 버튼
void APopolCharacter::UICharacterStat()
{
	//MainIwdget타입의 변수에 CharacterStatnUIClass가 들어와서 CharacterStatWidget타입으로 변환후 만들어준다.
	CharacterMainStatWidget = CreateWidget<UCharacterMainStatWidget>(PopolPlayerController, CharacterMainStatUIClass);
	//MAinWidget타입의 Widget을 불러올 변수의 값이 null이 아니라면
	if (CharacterMainStatWidget)
	{
		CharacterMainStatWidget->AddToViewport();
		PopolPlayerController->SetPause(true);			//게임 일시정지
		PopolPlayerController->bShowMouseCursor = true; //마우스 커서
	}

}
//GameMenu
void APopolCharacter::GameMenu()
{
	//MainIwdget타입의 변수에 CharacterStatnUIClass가 들어와서 CharacterStatWidget타입으로 변환후 만들어준다.
	GameExitWidget = CreateWidget<UGameExitWidget>(PopolPlayerController, UGameExitWidgetclass);
	//MAinWidget타입의 Widget을 불러올 변수의 값이 null이 아니라면
	if (GameExitWidget)
	{
		GameExitWidget->AddToViewport();
		PopolPlayerController->SetPause(true);			//게임 일시정지
		PopolPlayerController->bShowMouseCursor = true; //마우스 커서
	}
}


/*******   	Weapon  ******/

//무기 장착
void APopolCharacter::Weapon_Equip(int row)
{
	if (Weapon != NULL)
	{
		Weapon->Destroy();	//무기가 존재한다면 파괴
	}

	if (PopolGameInstance != nullptr)
	{
		if (Weapon != NULL)
		{
			Weapon->Destroy();	//무기가 존재한다면 파괴
		}
		CharWeaponData = PopolGameInstance->GetWeaponDamageData(row);	//DataTable의 행 확인
		PopolPlayerController->SetEquipWeaponNum_Controller(row);
		UWorld* World = GetWorld();
		if (World)
		{
			EquipWeapon = World->SpawnActor<AWeapon>(CharWeaponData->WeaponClass);	//행의 무기를 월드에 불러와준다.
			if (EquipWeapon)
			{
				EquipWeapon->AttackMeshToSocket(GetMesh(), FName("WeaponSocket"), this, this);	//소켓에 장착
				Weapon = EquipWeapon;	//장착 유무
			}
		}
	}
}
//무기 충돌 활성화
void APopolCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquipWeapon && EquipWeapon->GetWeaponBox())
	{
		EquipWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);	//콜리전 상태 유무
		EquipWeapon->IgnoreActors.Empty();
	}
}


/*******   	Shield  ******/

//방패 장착
void APopolCharacter::Shield_Equip()
{
	if (Shield != NULL)
	{
		Shield->Destroy();																		//방패가 존재한다면 파괴
	}
	if (PopolGameInstance != nullptr)
	{
		if (Shield != NULL)
		{
			Shield->Destroy();																	//방패가 존재한다면 파괴
		}
		CharShieldData = PopolGameInstance->GetShieldDefenseData(1);							//DataTable의 행 확인
		UWorld* World = GetWorld();
		if (World)
		{
			PlayerShield = World->SpawnActor<APlayerShield>(CharShieldData->ShieldClass);	//행의 무기를 월드에 불러와준다.
			if (PlayerShield)
			{
				ShieldType = EShieldEnable::ESE_Enable;
				PlayerShield->AttackMeshToSocket(GetMesh(), FName("ShieldSocket"), this, this);	//소켓에 장착
				Shield = PlayerShield;	//장착 유무
			}
		}
	}
}
//방패 충돌 비활성화
void APopolCharacter::SetShieldCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (PlayerShield && PlayerShield->GetShieldBox())
	{
		PlayerShield->GetShieldBox()->SetCollisionEnabled(CollisionEnabled);	//콜리전 상태 유무
		PlayerShield->IgnoreActors.Empty();
	}
}
//방패 시작 모션 끝
void APopolCharacter::ShieldBlockStart()
{
	ShieldBlockingType = true;
	BlockingType = EBlockingType::EBT_BLOCK_ONE;
}
//방패 모션 끝
void APopolCharacter::ShieldBlockEnd()
{
	BlockingType = EBlockingType::EBT_BLOCK_WAIT;
}


/*******   	AttackSystem  ******/

//공격 대기 중
bool APopolCharacter::ATTACK_WAIT()
{
	return AttackingType == EAttackingType::EAK_ATTACK_WAIT;
}
//Attack_A조건
bool APopolCharacter::Attack_A()
{
	return AttackingType == EAttackingType::EAK_ATTACK_WAIT && AttackingType != EAttackingType::EAK_ATTACK_ONE && CharacterAttackType != ECharacterAttackType::ECA_ATTACKKING_ONE && AttackingEndType != EAttackingEndType::EAKE_ATTACK_ONE_END;
}
//Attack_B조건
bool APopolCharacter::Attack_B()
{
	return AttackingType == EAttackingType::EAK_ATTACK_ONE && AttackingType != EAttackingType::EAK_ATTACK_TWO && CharacterAttackType == ECharacterAttackType::ECA_ATTACKKING_ONE && AttackingEndType == EAttackingEndType::EAKE_ATTACK_ONE_END;
}
//Attack_C조건
bool APopolCharacter::Attack_C()
{
	return AttackingType == EAttackingType::EAK_ATTACK_TWO && AttackingType != EAttackingType::EAK_ATTACK_THREE && CharacterAttackType == ECharacterAttackType::ECA_ATTACKKING_TWO && AttackingEndType == EAttackingEndType::EAKE_ATTACK_TWO_END;
}
//Attack_D조건
bool APopolCharacter::Attack_D()
{
	return AttackingType == EAttackingType::EAK_ATTACK_THREE && AttackingType != EAttackingType::EAK_ATTACK_FOUE && CharacterAttackType == ECharacterAttackType::ECA_ATTACKKING_THREE && AttackingEndType == EAttackingEndType::EAKE_ATTACK_THREE_END;
}
//공격 끝
void APopolCharacter::AttackEnd()
{
	CharacterMoveType = ECharacterMoveType::ECM_Run;			//움직임 상태 여부
	AttackingType = EAttackingType::EAK_ATTACK_WAIT;			//공격 몽타주 실행중 상태 여부
	CharacterAttackType = ECharacterAttackType::ECA_COMMONLY;	//공격 몽타주 상태 여부
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_NOMAL;	//공격 몽타주 끝난 상태 여부
}
//공격 몽타주 1번 끝난 상태
void APopolCharacter::vAttacking_One_End()
{
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_ONE_END;
}
//공격 몽타주 2번 끝난 상태
void APopolCharacter::vAttacking_Two_End()
{
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_TWO_END;
}
//공격 몽타주 3번 끝난 상태
void APopolCharacter::vAttacking_Three_End()
{
	AttackingEndType = EAttackingEndType::EAKE_ATTACK_THREE_END;
}


/*******   	JumpSystem  ******/

//점프 끝
void APopolCharacter::JumpEnd()
{
	CharacterMoveType = ECharacterMoveType::ECM_Run;
}