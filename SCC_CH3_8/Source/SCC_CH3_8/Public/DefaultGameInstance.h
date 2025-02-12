#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DefaultGameInstance.generated.h"

UCLASS()
class SCC_CH3_8_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDefaultGameInstance();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddTotalScore(int32 Amount);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevel;
};
