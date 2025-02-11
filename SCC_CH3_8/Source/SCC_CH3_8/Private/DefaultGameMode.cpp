#include "DefaultGameMode.h"

#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"

ADefaultGameMode::ADefaultGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = APlayerCharacterController::StaticClass();
}