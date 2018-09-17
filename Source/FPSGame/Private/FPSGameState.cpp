// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"




void AFPSGameState::MulitcastOnMissionComplete(APawn* IntigatorPawn, bool bMissionSuccess)
{
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		APawn* Pawn = It->Get();
		if (Pawn && Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}
}
