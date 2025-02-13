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

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset1(TEXT("/Game/Interface_And_Item_Sounds/WAV/Abstract_Pop_02.Abstract_Pop_02"));
	if (SoundAsset1.Succeeded())
	{
		PickupSounds.Push(SoundAsset1.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset2(TEXT("/Game/Interface_And_Item_Sounds/WAV/Abstract_Pop_03.Abstract_Pop_03"));
	if (SoundAsset2.Succeeded())
	{
		PickupSounds.Push(SoundAsset2.Object);
	}
}

void ABigScoreItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
