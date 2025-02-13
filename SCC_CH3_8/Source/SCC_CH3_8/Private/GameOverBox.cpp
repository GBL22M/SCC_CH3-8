#include "GameOverBox.h"
#include "DefaultGameState.h"

#include "Components/BoxComponent.h"

AGameOverBox::AGameOverBox()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComp;

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollisionComp->SetupAttachment(RootComponent);
	BoxCollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGameOverBox::OnItemOverlap);
	BoxCollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGameOverBox::OnItemEndOverlap);
}

void AGameOverBox::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ADefaultGameState* DefaultGameState = GetWorld() ? GetWorld()->GetGameState<ADefaultGameState>() : nullptr;
		if (DefaultGameState)
		{
			DefaultGameState->EndLevel();
		}
	}
}

void AGameOverBox::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

