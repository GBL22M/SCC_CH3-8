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
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset1(TEXT("/Game/Interface_And_Item_Sounds/WAV/Abstract_Pop_04.Abstract_Pop_04"));
	if (SoundAsset1.Succeeded())
	{
		PickupSounds.Push(SoundAsset1.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset2(TEXT("/Game/Interface_And_Item_Sounds/WAV/Abstract_Pop_05.Abstract_Pop_05"));
	if (SoundAsset2.Succeeded())
	{
		PickupSounds.Push(SoundAsset2.Object);
	}
}

void ASmallScoreItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
