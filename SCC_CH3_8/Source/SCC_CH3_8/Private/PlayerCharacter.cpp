#include "PlayerCharacter.h"

#include "PlayerCharacterController.h"

#include "Camera/CameraComponent.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
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

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> OverHeadWidgetClass(TEXT("/Game/UI/WBP_Item.WBP_Item_C"));
	if (OverHeadWidgetClass.Succeeded())
	{
		OverheadWidget->SetWidgetClass(OverHeadWidgetClass.Class);
	}
	OverheadWidget->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	OverheadWidget->SetRelativeLocation(FVector(0.f, 0.f, 180.f));
	OverheadWidget->SetDrawSize(FVector2D(100.f, 100.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SkeletalMeshAsset(TEXT("/Game/Resources/Characters/Meshes/SKM_Manny.SKM_Manny"));
	if (SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>AnimInstanceClass(TEXT("/Game/Animation/ABP_PlayerCharacter.ABP_PlayerCharacter_C"));
	if (AnimInstanceClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
	}


	//value setting
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
	UpdateOverheadWidget();

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

	if (!OverheadWidget)
		return;

	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance)
		return;

	if (UImage* Image = Cast<UImage>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadWidget"))))
	{
		Image->SetOpacity(0.f);
	}
}

void APlayerCharacter::UpdateOverheadWidget()
{
	if (!OverheadWidget)
		return;

	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance) 
		return;

	if (UImage* Image = Cast<UImage>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadWidget"))))
	{
		Image->SetOpacity(1.f);
	}		
	/*if (UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP"))))
	{
		HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Health, MaxHealth)));
	}*/
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


