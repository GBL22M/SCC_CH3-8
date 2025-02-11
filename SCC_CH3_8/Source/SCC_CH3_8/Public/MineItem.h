// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

class UInterpToMovementComponent;

UCLASS()
class SCC_CH3_8_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

//functions
public:
	AMineItem();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ActivateItem(AActor* Activator) override;
	void Explode();

//variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	TObjectPtr<USphereComponent> ExplosionCollisionComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float MinePower; //캐릭터를 밀어내는 힘

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	//TArray<FVector>	Positions;


private:
	FTimerHandle ExplosionTimerHandle;
	float ExplosionDelay;
	//UInterpToMovementComponent* InterpMovementComp;
	FVector OriginLocation;
	float TimeElapsed;
	float VibrationAmplitude;
	float VibrationFrequency;
};
