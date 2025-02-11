// Fill out your copyright notice in the Description page of Project Settings.


#include "BigScoreItem.h"

ABigScoreItem::ABigScoreItem()
{
	ItemType = "Big Item";
	PointValue = 50;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/PolygonPrototype/Meshes/Icons/SM_Icon_Banana_02.SM_Icon_Banana_02"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void ABigScoreItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
