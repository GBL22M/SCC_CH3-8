#include "DefaultGameMode.h"

#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"
#include "DefaultGameState.h"

ADefaultGameMode::ADefaultGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = APlayerCharacterController::StaticClass();
	GameStateClass = ADefaultGameState::StaticClass();
}