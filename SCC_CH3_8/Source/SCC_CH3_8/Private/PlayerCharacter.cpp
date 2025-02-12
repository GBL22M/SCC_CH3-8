#include "PlayerCharacter.h"

#include "PlayerCharacterController.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


APlayerCharacter::APlayerCharacter()
	:bIsReverseMove(false)
	,ReverseMoveDelayTime(2.f)
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);	
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SkeletalMeshAsset(TEXT("/Game/Resources/Characters/Meshes/SKM_Manny.SKM_Manny"));
	if (SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCharacterMovement()->JumpZVelocity = 500.f;

	Tags.Add("Player");
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInputComponent->BindAction
				(
					PlayerController->MoveAction
					,ETriggerEvent::Triggered
					,this
					,&APlayerCharacter::Move
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInputComponent->BindAction
				(
					PlayerController->LookAction
					, ETriggerEvent::Triggered
					, this
					, &APlayerCharacter::Look
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInputComponent->BindAction
				(
					PlayerController->JumpAction
					, ETriggerEvent::Triggered
					, this
					, &APlayerCharacter::StartJump
				);

				EnhancedInputComponent->BindAction
				(
					PlayerController->JumpAction
					, ETriggerEvent::Completed
					, this
					, &APlayerCharacter::StopJump
				);
			}
		}
	}
}

void APlayerCharacter::ReverseMove()
{
	bIsReverseMove = true;

	GetWorldTimerManager().SetTimer
	(
		ReverseMoveTimerHandle
		,this
		,&APlayerCharacter::RestoreMove
		,ReverseMoveDelayTime
		,false
	);
}

void APlayerCharacter::RestoreMove()
{
	bIsReverseMove = false;
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	if (!Controller)
		return;
	FVector2D MoveInput = value.Get<FVector2D>();

	if (bIsReverseMove)
	{
		MoveInput.X *= -1;
		MoveInput.Y *= -1;
	}
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void APlayerCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

void APlayerCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}


