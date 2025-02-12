// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

class UBoxComponent;

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
	void Vibrate();

//variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UBoxComponent> ExplosionCollisionComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	float BoxCollisionWidth;

private:
	FTimerHandle ExplosionTimerHandle;
	float ExplosionDelay;	
	FVector OriginLocation;
	FVector LaunchVector;

	float MinePower; //캐릭터를 밀어내는 힘
	float TimeElapsed;
	float VibrationAmplitude;
	float VibrationFrequency;

	bool bFirstOverlap;
};
