#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BadItem.generated.h"


UCLASS()
class SCC_CH3_8_API ABadItem : public ABaseItem
{
	GENERATED_BODY()

//functions
public:
	ABadItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

//variables
private:
};
