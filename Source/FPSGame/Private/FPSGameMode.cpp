// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewPointClass)
		{

			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, ReturnedActors);

			AActor* NewViewTarget = nullptr;

			if (ReturnedActors.Num())
			{
				NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();
					if (PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
	
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No Spectating View Point Class Set"));
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();

	if (GS)
	{
		GS->MulitcastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}

