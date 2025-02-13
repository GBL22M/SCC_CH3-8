#include "ItemSpawnVolume.h"
#include "Components/BoxComponent.h"

AItemSpawnVolume::AItemSpawnVolume()
	:ItemDataTable(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SpawningBox->SetupAttachment(RootComponent);

	SpawningBox->SetRelativeLocation(FVector(0.f, -120.f, 70.f));
	SpawningBox->InitBoxExtent(FVector(200.f, 100.f, 5.f));
	
	//레벨 마다 다른 Data Table을 적용하도록
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Game/Data/DT_Level1.DT_Level1"));
	if (DataTableAsset.Succeeded())
	{
		ItemDataTable = DataTableAsset.Object;
	}

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/PolygonPrototype/Meshes/Generic/SM_Generic_Cloud_03.SM_Generic_Cloud_03"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
	StaticMeshComp->SetRelativeScale3D(FVector(0.7f, 1.f, 0.3f));
}

AActor* AItemSpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}
	return nullptr;
}

//스폰할 아이템
AActor* AItemSpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass)
		return nullptr;

	//real spawn
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ItemClass, GetRandomPointInVolume(), FRotator::ZeroRotator);
	
	return SpawnedActor;
}

FVector AItemSpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector
	(
		  FMath::RandRange(-BoxExtent.X, BoxExtent.X)
		, FMath::RandRange(-BoxExtent.Y, BoxExtent.Y)
		, FMath::RandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

FItemSpawnRow* AItemSpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable)
		return nullptr;

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));

	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty())
		return nullptr;

	float TotalChance = 0.f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.f, TotalChance);

	float AccumulateChance = 0.f;
	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}
	return nullptr;
}
