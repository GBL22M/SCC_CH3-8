#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DefaultGameState.generated.h"

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
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	virtual void BeginPlay() override;
	void StartLevel();
	void OnLevelTimeUp();
	void EndLevel();
	void UpdateHUD();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 TotalScore;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level");
	float LevelDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level");
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level");
	int32 MaxLevelIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level");
	TArray<FName> LevelMapNames;
	bool bPlayBefore;

private:
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	float RemainingTime;
};
