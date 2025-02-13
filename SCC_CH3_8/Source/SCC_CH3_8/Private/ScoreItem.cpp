#include "ScoreItem.h"
#include "DefaultGameState.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AScoreItem::AScoreItem()
	:PointValue(0)
{
	ItemType = "Score Item";
}

void AScoreItem::ActivateItem(AActor* Activator)
{
	if (PickupSounds.Num() > 0)
	{
		int RandIdx = FMath::RandRange(0, PickupSounds.Num() - 1);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSounds[RandIdx], GetActorLocation());
	}

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (ADefaultGameState* GameState = World->GetGameState<ADefaultGameState>())
			{
				GameState->AddScore(PointValue);
			}
		}
	}
	DestroyItem();
}
