#include "BadItem.h"

#include "PlayerCharacter.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ABadItem::ABadItem()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/PolygonPrototype/Meshes/Icons/SM_Icon_Letter_Question_01.SM_Icon_Letter_Question_01"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void ABadItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator);
		if (PlayerCharacter)
		{
			PlayerCharacter->ReverseMove();
		}
	}

	DestroyItem();
}