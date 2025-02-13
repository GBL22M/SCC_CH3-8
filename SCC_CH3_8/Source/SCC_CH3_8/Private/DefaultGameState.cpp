#include "DefaultGameState.h"
#include "Kismet/GameplayStatics.h"

#include "PlayerCharacterController.h"
#include "DefaultGameInstance.h"
#include "ItemSpawnVolume.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

ADefaultGameState::ADefaultGameState()
	:TotalScore(0)
	,LevelDuration(30.f)
	,CurrentLevelIndex(0)
	,MaxLevelIndex(3)
	,bPlayBefore(false)
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
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(GameInstance);
		if (DefaultGameInstance)
		{
			DefaultGameInstance->AddTotalScore(Amount);
		}
	}
	TotalScore += Amount;
}

void ADefaultGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(PlayerController))
		{
			PlayerCharacterController->ShowMainMenu(true);
			PlayerCharacterController->SetPause(true);
		}
	}
}

void ADefaultGameState::BeginPlay()
{
	Super::BeginPlay();

	UpdateHUD();
	StartLevel();

	//HUD Timer
	GetWorldTimerManager().SetTimer
	(
		HUDUpdateTimerHandle
		,this
		,&ADefaultGameState::UpdateHUD
		,0.1f
		,true
	);
}

void ADefaultGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(PlayerController))
		{
			PlayerCharacterController->ShowGameHUD();
		}
	}
	//game instance - level
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(GameInstance);
		if (DefaultGameInstance)
		{
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

	UpdateHUD();
}

void ADefaultGameState::OnLevelTimeUp()
{
	EndLevel();
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
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = PlayerCharacterController->GetHUDWidget())
			{
				//Timer Text
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %.1f"),RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						if (UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(GameInstance))
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), DefaultGameInstance->TotalScore)));
						}
					}
				}
				if (UTextBlock* LevelText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						if (UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(GameInstance))
						{
							LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), DefaultGameInstance->CurrentLevel + 1)));
						}
					}
				}
				if (UProgressBar* ProgressBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(TEXT("TimeBar"))))
				{			
					RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					float value = RemainingTime / LevelDuration;
					ProgressBar->SetPercent(value);
					
					if (!bPlayBefore && value > 0.001f && value < 0.3f)
					{
						PlayerCharacterController->PlayBarAnimation();
						bPlayBefore = true;
					}
				}				
			}
		}
	}
}
