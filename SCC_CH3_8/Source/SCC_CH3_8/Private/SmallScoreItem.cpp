// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallScoreItem.h"

ASmallScoreItem::ASmallScoreItem()
{
	ItemType = "Small Item";
	PointValue = 15;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/PolygonPrototype/Meshes/Icons/SM_Icon_Banana_01.SM_Icon_Banana_01"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void ASmallScoreItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
