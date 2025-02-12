#include "PlayerCharacterController.h"

#include "DefaultGameState.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"

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
}

UUserWidget* APlayerCharacterController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void APlayerCharacterController::ShowGameHUD()
{
}

void APlayerCharacterController::ShowMainMenu(bool bIsStart)
{
}

void APlayerCharacterController::StartGame()
{
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

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}

	ADefaultGameState* DefaultGameState = GetWorld() ? GetWorld()->GetGameState<ADefaultGameState>() : nullptr;
	if (DefaultGameState)
	{
		DefaultGameState->UpdateHUD();
	}
}
