#include "DefaultGameInstance.h"

UDefaultGameInstance::UDefaultGameInstance()
	:TotalScore(0)
	,CurrentLevel(0)
{

}

void UDefaultGameInstance::AddTotalScore(int32 Amount)
{
	TotalScore += Amount;
}
