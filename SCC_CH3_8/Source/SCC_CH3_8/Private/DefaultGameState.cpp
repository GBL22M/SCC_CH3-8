#include "DefaultGameState.h"
#include "Kismet/GameplayStatics.h"

#include "DefaultGameInstance.h"
#include "ItemSpawnVolume.h"

#include "Kismet/GameplayStatics.h"

ADefaultGameState::ADefaultGameState()
	:TotalScore(0)
	,LevelDuration(30.f)
	,CurrentLevelIndex(0)
	,MaxLevelIndex(3)
{
	LevelMapNames.Push(FName("Level1"));
	LevelMapNames.Push(FName("Level2"));
	LevelMapNames.Push(FName("Level3"));
}

int32 ADefaultGameState::GetScore() const
{
	return TotalScore;
}

void ADefaultGameState::AddScore(int32 Amount)
{
	TotalScore += Amount;
}

void ADefaultGameState::OnGameOver()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("END GAME")));
}

void ADefaultGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	//HUD Timer
}

void ADefaultGameState::StartLevel()
{
	//game instance - level
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("GameInstance OK")));

		UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(GameInstance);
		if (DefaultGameInstance)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("start level: %d"), DefaultGameInstance->CurrentLevel));
			CurrentLevelIndex = DefaultGameInstance->CurrentLevel;
		}
	}

	//random spawn
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 3;

	for (int32 i = 0; i < FoundVolumes.Num(); ++i)
	{
		AItemSpawnVolume* SpawnVolume = Cast<AItemSpawnVolume>(FoundVolumes[i]);
		if (SpawnVolume)
		{
			for (int32 j = 0; j < ItemToSpawn; ++j)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
			}
		}
	}

	GetWorldTimerManager().SetTimer
	(
		LevelTimerHandle
		, this
		, &ADefaultGameState::OnLevelTimeUp
		, LevelDuration
		, false
	);
}

void ADefaultGameState::OnLevelTimeUp()
{
	EndLevel();
	//OnGameOver();
}

void ADefaultGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	CurrentLevelIndex++;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(GameInstance);
		if (DefaultGameInstance)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("end level: %d"), DefaultGameInstance->CurrentLevel));
			DefaultGameInstance->CurrentLevel = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevelIndex)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void ADefaultGameState::UpdateHUD()
{
}
