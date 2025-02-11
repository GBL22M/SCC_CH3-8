#include "MineItem.h"

AMineItem::AMineItem()
	:MinePower(0.f)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/PolygonPrototype/Meshes/Icons/SM_Icon_Skull_01.SM_Icon_Skull_01"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void AMineItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		//
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Mine Item")));
	}
}