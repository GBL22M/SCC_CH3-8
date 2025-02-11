#include "ScoreItem.h"
#include "DefaultGameState.h"

#include "Engine/World.h"

AScoreItem::AScoreItem()
	:PointValue(0)
{
	ItemType = "Score Item";


}

void AScoreItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("score item point : %d"), PointValue));
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
