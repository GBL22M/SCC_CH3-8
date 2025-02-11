// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SCC_CH3_8_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
//functions
public:
	APlayerCharacterController();

protected:
	virtual void BeginPlay() override;


//variables
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
};
