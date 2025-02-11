// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreItem.h"
#include "SmallScoreItem.generated.h"

/**
 * 
 */
UCLASS()
class SCC_CH3_8_API ASmallScoreItem : public AScoreItem
{
	GENERATED_BODY()

public:
	ASmallScoreItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;
};
