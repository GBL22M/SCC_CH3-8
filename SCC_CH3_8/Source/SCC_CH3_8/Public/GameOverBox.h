#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOverBox.generated.h"

class UBoxComponent;

UCLASS()
class SCC_CH3_8_API AGameOverBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameOverBox();

protected:
	UFUNCTION()
	void OnItemOverlap
	(
		UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnItemEndOverlap
	(
		UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
	);
	

public:
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> BoxCollisionComp;
};
