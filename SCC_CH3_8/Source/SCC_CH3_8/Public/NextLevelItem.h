// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "NextLevelItem.generated.h"

/**
 * 
 */
UCLASS()
class SCC_CH3_8_API ANextLevelItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ANextLevelItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;
	
private:
	float CollisionRadius;
};
