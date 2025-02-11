#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DefaultGameState.generated.h"

/**
 * 
 */
UCLASS()
class SCC_CH3_8_API ADefaultGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ADefaultGameState();

public:
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 TotalScore;
};
