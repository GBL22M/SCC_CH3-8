// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"


UCLASS()
class SCC_CH3_8_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMineItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float MinePower;
};
