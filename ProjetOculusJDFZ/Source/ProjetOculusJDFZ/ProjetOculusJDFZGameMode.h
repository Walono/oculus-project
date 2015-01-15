// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "OculusCharacter.h"
#include "SpawnVolume.h"
#include "ProjetOculusJDFZGameMode.generated.h"

//Enmum of simulation's stats
enum class EOculusProjectPlayStats : short
{
	EInitialization,
	ESpawningEnable,
	EUnknow
};

/**
*	Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
*	ProjetOculusJDFZGameMode
*	Purpose: Rules the world, set the initial variable and handle the state and state changement
*
*  @author Julie Djeffal & Fabien Zellweger
*/
UCLASS()
class PROJETOCULUSJDFZ_API AProjetOculusJDFZGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	/** method called befir the start of the simulation */
	virtual void BeginPlay() override;

	EOculusProjectPlayStats GetCurrentState() const;

	void SetCurrentState(EOculusProjectPlayStats NewState);

private:
	/** Contain the spawnVolume, and more if needed */
	TArray<ASpawnVolume*> SpawnVolumeActors;

	EOculusProjectPlayStats CurrentState;
	/** change state and manage what's needed befor change it, called by SetCurrentState() only */
	void HandleNewState(EOculusProjectPlayStats NewState);

	Library* library;
	
};

FORCEINLINE EOculusProjectPlayStats AProjetOculusJDFZGameMode::GetCurrentState() const
{
	return CurrentState;
};
