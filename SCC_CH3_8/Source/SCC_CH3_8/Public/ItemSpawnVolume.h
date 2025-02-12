#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "ItemSpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SCC_CH3_8_API AItemSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemSpawnVolume();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();

private:
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	FVector GetRandomPointInVolume() const;
	FItemSpawnRow* GetRandomItem() const;

//Variables
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning|Components")
	TObjectPtr<USceneComponent> Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning|Components")
	TObjectPtr<UBoxComponent> SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning|Components")
	TObjectPtr<UDataTable> ItemDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawing|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

};
