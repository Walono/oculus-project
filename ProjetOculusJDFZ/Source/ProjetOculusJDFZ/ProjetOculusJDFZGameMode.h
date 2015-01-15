// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "OculusCharacter.h"
#include "SpawnVolume.h"
#include "ProjetOculusJDFZGameMode.generated.h"

//Enmum to store the current stats of simulation
enum class EOculusProjectPlayStats : short
{
	EInitialization,
	ESpawningEnable,
	EUnknow
};

/**
 * 
 */
UCLASS()
class PROJETOCULUSJDFZ_API AProjetOculusJDFZGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()


	virtual void BeginPlay() override;

	EOculusProjectPlayStats GetCurrentState() const;

	void SetCurrentState(EOculusProjectPlayStats NewState);

private:

	TArray<ASpawnVolume*> SpawnVolumeActors;

	EOculusProjectPlayStats CurrentState;

	void HandleNewState(EOculusProjectPlayStats NewState);

	Library* library;
	
};

FORCEINLINE EOculusProjectPlayStats 
AProjetOculusJDFZGameMode::GetCurrentState() const
{
	return CurrentState;
};
