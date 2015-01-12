// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProjetOculusJDFZGameMode.h"
#include "Engine.h"
#include "OculusHUD.h"



AProjetOculusJDFZGameMode::AProjetOculusJDFZGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Set the default pawn class, respectivly our character
	DefaultPawnClass = AOculusCharacter::StaticClass();

	//Set the default HUD class
	HUDClass = AOculusHUD::StaticClass();
}

void AProjetOculusJDFZGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}

	//find all spawn volume actor
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.Add(SpawnVolumeActor);
		}
	}

	SetCurrentState(EOculusProjectPlayStats::EInitialization);
}

void AProjetOculusJDFZGameMode::SetCurrentState(EOculusProjectPlayStats NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void AProjetOculusJDFZGameMode::HandleNewState(EOculusProjectPlayStats NewState)
{

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	switch (NewState)
	{
	case EOculusProjectPlayStats::EInitialization:
		//disable the possibility to move befor entering the spawning state		
		PlayerController->SetIgnoreMoveInput(true);
		//at initializazion state, nothing spawn
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningEnable(false);
		}
		break;
	case EOculusProjectPlayStats::ESpawningEnable:
		//Player can now move normaly
		PlayerController->SetIgnoreMoveInput(false);
		//at spawning state, spawnVolume can spawn element
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningEnable(true);
		}
		break;
	case EOculusProjectPlayStats::EUnknow:
	default:
		//do nothing
		break;
	}
}


