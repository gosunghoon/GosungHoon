// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Weapon.h"
#include "Item/Item.h"
#include "GameInstance/PopolGameInstance.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/HitInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "Character/PopolCharacter.h"
#include "Widget/CharacterMainWidget/ItemDropWidget.h"
#include "Character/Controller/PopolPlayerController.h"
#include "Character/State/PopolPlayerState.h"


/*******   MainSystem   ******/

//Main
AWeapon::AWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetNotifyRigidBodyCollision(true);
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

/*******   Equip   ******/

//빈 소켓에 장비 장착
void AWeapon::AttackMeshToSocket(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator)
{

	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	ItemState = EItemState::EIS_Equipped;
	//플레이어의 컨트롤러를 PopolPlayerController로 변경해준다.
	PopolPlayerController = Cast<APopolPlayerController>(NewInstigator->GetController());
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	WeaponMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}


/*******   System   ******/

//Actor 생성 시 설정
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("PlayerWeapon"));

	//플레이어의 컨트롤러를 PopolPlayerController로 변경해준다.
	PopolPlayerController = Cast<APopolPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}


/*******   OverlapSystem   ******/

//박스에 닿았을 경우 반응하는 함수
void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//대상이 적이라면
	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		// 적중 변수 이름
		FHitResult CharacterBoxHit;
		//박스 추적
		BoxTrace(CharacterBoxHit);

		//인스턴스를 불러온다.
		UPopolGameInstance* PopolGameInstance = Cast<UPopolGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		//무기 데이터
		WeaponData = PopolGameInstance->GetWeaponDamageData(PopolPlayerController->GetEqipWeaponNum());
		////캐릭터 스탯
		//CharacterStats = PopolGameInstance->GetCharacterStatsData(PopolPlayerController->GetStatePlayerLevel());


		//공격력 계산  후 공격
		PlayerAttackDamage = WeaponData->Damage + PopolPlayerController->GetPlayerAttackControll(); //플레이어 공격력 계산
		UGameplayStatics::ApplyDamage(CharacterBoxHit.GetActor(), PlayerAttackDamage, GetInstigator()->GetController(), this, UDamageType::StaticClass());


		//히트 인터페이스
		IHitInterface* HitInterpace = Cast<IHitInterface>(CharacterBoxHit.GetActor());
		if (HitInterpace)
		{
			//히트 포인트
			HitInterpace->GetHit(CharacterBoxHit.ImpactPoint);
		}
		//중복 불가
		IgnoreActors.AddUnique(CharacterBoxHit.GetActor());
	}
}
//박스 추적
void AWeapon::BoxTrace(FHitResult& BoxHit)
{
	//선 추격 시작 지점
	const FVector Start = BoxTraceStart->GetComponentLocation();
	//선 추격 끝 지점
	const FVector End = BoxTraceEnd->GetComponentLocation();

	//대상 저장
	TArray<AActor*> ActorsTognore;

	ActorsTognore.Add(this); // 무기
	ActorsTognore.Add(GetOwner()); // 플레이어

	//타격 무시 액터로 설정
	for (AActor* Actor : IgnoreActors)
	{
		//대상을 중복 체크하지 않고 한번만 체크
		ActorsTognore.AddUnique(Actor);
	}
	//싱글 박스 트레이스
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		TarceHalfSize,
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsTognore,
		EDrawDebugTrace::None,
		BoxHit,
		true
	);
	//중복 불가
	IgnoreActors.AddUnique(BoxHit.GetActor());
}