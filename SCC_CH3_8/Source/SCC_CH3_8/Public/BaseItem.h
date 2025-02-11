// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class SCC_CH3_8_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	virtual void OnItemOverlap
	(
		UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult& SweepResult
	) override;

	UFUNCTION()
	virtual void OnItemEndOverlap
	(
		UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
	) override;

	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;
	virtual void DestroyItem();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "item")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<USphereComponent> CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
};
