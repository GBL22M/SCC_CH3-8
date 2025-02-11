#include "MineItem.h"
#include "PlayerCharacter.h"

#include "Components/SphereComponent.h"
#include "Components/InterpToMovementComponent.h"

AMineItem::AMineItem()
	:MinePower(1000.f)
	,ExplosionDelay(2.f)
	, TimeElapsed(0.f)
	, VibrationAmplitude(10.f)
	, VibrationFrequency(5.f)
{
	PrimaryActorTick.bCanEverTick = true;

	ExplosionCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion Collision"));
	ExplosionCollisionComp->InitSphereRadius(300);
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
	float Offset = FMath::Sin(TimeElapsed * VibrationFrequency * 2.0f * PI) * VibrationAmplitude;
	FVector NewLocation = OriginLocation + FVector(0, 0, Offset);
	SetActorLocation(NewLocation);
}

void AMineItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	 
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
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("launch!")));
				FVector LaunchVelocity = FVector(-PlayerCharacter->GetActorForwardVector() * MinePower);
				PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);										
			}

		}
	}
	DestroyItem();
}
