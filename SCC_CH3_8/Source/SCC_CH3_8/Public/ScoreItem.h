#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ScoreItem.generated.h"


UCLASS()
class SCC_CH3_8_API AScoreItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AScoreItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 PointValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	TArray<TObjectPtr<USoundBase>> PickupSounds;
};
