#include "PlayerCharacterController.h"

#include "DefaultGameState.h"
#include "DefaultGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacterController::APlayerCharacterController()
	:InputMappingContext(nullptr)
	, MoveAction(nullptr)
	, LookAction(nullptr)
	, JumpAction(nullptr)
	, HUDWidgetClass(nullptr)
	, HUDWidgetInstance(nullptr)
	, MenuWidgetClass(nullptr)
	, MenuWidgetInstance(nullptr)
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default(TEXT("/Game/Inputs/IMC_Default.IMC_Default"));
	if (IMC_Default.Succeeded())
	{
		InputMappingContext = IMC_Default.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Move(TEXT("/Game/Inputs/IA_Move.IA_Move"));
	if (IA_Move.Succeeded())
	{
		MoveAction = IA_Move.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Look(TEXT("/Game/Inputs/IA_Look.IA_Look"));
	if (IA_Look.Succeeded())
	{
		LookAction = IA_Look.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Jump(TEXT("/Game/Inputs/IA_Jump.IA_Jump"));
	if (IA_Jump.Succeeded())
	{
		JumpAction = IA_Jump.Object;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget>HUDWidget(TEXT("/Game/UI/WBP_HUD.WBP_HUD_C"));
	if (HUDWidget.Succeeded())
	{
		HUDWidgetClass = HUDWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget>MenuWidget(TEXT("/Game/UI/WBP_MainMenu.WBP_MainMenu_C"));
	if (MenuWidget.Succeeded())
	{
		MenuWidgetClass = MenuWidget.Class;
	}
}

UUserWidget* APlayerCharacterController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void APlayerCharacterController::ShowGameHUD()
{
	//HUD 있으면 없애기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	//MainMenu 있으면 없애기
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}

	//HUD UI 생성
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
			
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());

			ADefaultGameState* DefaultGameState = GetWorld() ? GetWorld()->GetGameState<ADefaultGameState>() : nullptr;
			if (DefaultGameState)
			{
				DefaultGameState->UpdateHUD();
			}
		}
	}
}

void APlayerCharacterController::ShowMainMenu(bool bIsReStart)
{
	//MainMenu 켤때 HUD 있으면 없애기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	//MainMenu 켤때 MainMenu 있으면 없애기
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}

	//Menu UI 생성
	if (MenuWidgetClass)
	{
		MenuWidgetInstance = CreateWidget<UUserWidget>(this, MenuWidgetClass);
		if (MenuWidgetInstance)
		{
			MenuWidgetInstance->AddToViewport();

			//게임 조작 불가능하게 처리
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsReStart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
	}
}

void APlayerCharacterController::StartGame()
{
	if (UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		DefaultGameInstance->CurrentLevel = 0;
		DefaultGameInstance->TotalScore = 0;
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level1"));
	SetPause(false);
}

void APlayerCharacterController::PlayBarAnimation()
{
	UFunction* PlayBarAnim = HUDWidgetInstance->FindFunction(FName("ProgressBarAnimation"));
	if (PlayBarAnim)
	{
		HUDWidgetInstance->ProcessEvent(PlayBarAnim, nullptr);
	}
}


void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	
	//Game Start
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}
