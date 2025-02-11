// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreItem.h"
#include "BigScoreItem.generated.h"

/**
 * 
 */
UCLASS()
class SCC_CH3_8_API ABigScoreItem : public AScoreItem
{
	GENERATED_BODY()
	
public:
	ABigScoreItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

};
