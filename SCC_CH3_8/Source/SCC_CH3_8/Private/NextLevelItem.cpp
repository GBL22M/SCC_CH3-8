#include "NextLevelItem.h"

#include "DefaultGameState.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"

ANextLevelItem::ANextLevelItem()
	:CollisionRadius(100.f)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/PolygonPrototype/Meshes/FX/SM_FX_Glow_Ring_01.SM_FX_Glow_Ring_01"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
	CollisionComp->InitSphereRadius(CollisionRadius);
}

void ANextLevelItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (ADefaultGameState* GameState = World->GetGameState<ADefaultGameState>())
			{			
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("level: %d"), GameState->CurrentLevelIndex));
				GameState->EndLevel();
			}
		}
	}
}
