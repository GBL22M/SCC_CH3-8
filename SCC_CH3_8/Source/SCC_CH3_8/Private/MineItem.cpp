#include "MineItem.h"
#include "PlayerCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InterpToMovementComponent.h"

AMineItem::AMineItem()
	:ExplosionDelay(2.f)
	,OriginLocation(FVector::ZeroVector)
	,MinePower(2000.f)
	,TimeElapsed(0.f)
	,VibrationAmplitude(10.f)
	,VibrationFrequency(5.f)
	,bFirstOverlap(false)
	,BoxCollisionWidth(100.f)
{
	PrimaryActorTick.bCanEverTick = true;

	ExplosionCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Explosion Collision"));
	ExplosionCollisionComp->InitBoxExtent(FVector(BoxCollisionWidth, BoxCollisionWidth, BoxCollisionWidth/3));
	ExplosionCollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamics"));
	ExplosionCollisionComp->SetupAttachment(SceneComp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/PolygonPrototype/Meshes/Icons/SM_Icon_Skull_01.SM_Icon_Skull_01"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void AMineItem::BeginPlay()
{
	Super::BeginPlay();
	OriginLocation = GetActorLocation();	
}

void AMineItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeElapsed += DeltaTime;

	if(bFirstOverlap)
		Vibrate();
}

void AMineItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);	 
	
	if (bFirstOverlap)
		return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator);
	if (PlayerCharacter)
	{
		LaunchVector = PlayerCharacter->GetActorForwardVector();
		LaunchVector.Normalize();
	}

	bFirstOverlap = true;

	GetWorld()->GetTimerManager().SetTimer
	(
		ExplosionTimerHandle
		, this
		, &AMineItem::Explode
		, ExplosionDelay
		, false
	);	
}

void AMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;

	ExplosionCollisionComp->GetOverlappingActors(OverlappingActors);

	for (AActor* Activator : OverlappingActors)
	{
		if (Activator && Activator->ActorHasTag("Player"))
		{
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator);
			if (PlayerCharacter)
			{
				FVector LaunchVelocity = FVector(-LaunchVector * MinePower);
				PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);										
			}

		}
	}
	DestroyItem();
}

void AMineItem::Vibrate()
{
	float Offset = FMath::Sin(TimeElapsed * VibrationFrequency * 2.0f * PI) * VibrationAmplitude;
	FVector NewLocation = OriginLocation + FVector(0, 0, Offset);
	SetActorLocation(NewLocation);
}
