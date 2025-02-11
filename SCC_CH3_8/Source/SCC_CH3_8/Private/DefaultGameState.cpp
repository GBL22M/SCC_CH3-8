// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameState.h"

ADefaultGameState::ADefaultGameState()
	:TotalScore(0)
{
}

int32 ADefaultGameState::GetScore() const
{
	return TotalScore;
}

void ADefaultGameState::AddScore(int32 Amount)
{
	TotalScore += Amount;
}
