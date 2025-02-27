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
	UFUNCTION(BlueprintPure, Category = "HUD")
	UUserWidget* GetHUDWidget() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowMainMenu(bool bIsReStart);
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void StartGame();
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PlayBarAnimation();
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PlayScoreTextAnimation();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UUserWidget> HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Menu")
	TObjectPtr<UUserWidget> MenuWidgetInstance;
};
