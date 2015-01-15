// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Library.h"
#include "SpawnVolume.generated.h"

/**
*	Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
*	SpawnVolume
*	Purpose: Make the link between the library and the visualization. Look into the library if there is something to do, and
*		and acte in concequence.
*		This Actor is curently placed in the editor. No code doing this right now.
*
*  @author Julie Djeffal & Fabien Zellweger
*/
UCLASS()
class PROJETOCULUSJDFZ_API ASpawnVolume : public AActor
{
	GENERATED_UCLASS_BODY()

	/** BoxComponent to specify the spawning area within the level */
	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	TSubobjectPtr<UBoxComponent> WhereToSpawn;

	/** How many tick between two spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelay;

	/** ovverdide the tick to spawn object on the right time, it tick every frame */
	virtual void Tick(float DeltSeconds) override;

	/** Enable/disable the spawning behaviours, called in GameMode when changing state */
	UFUNCTION()
	void SetSpawningEnable(bool isEnable);

	/** Verify if a FName already existe or not in the World's Actor list */
	bool IsActorAlreadySpawned(FString FaceName);

private:

	/** The container of all object to spawn */
	Library * library;

	/** Base location for the SpawnVolume. */
	FVector InitialSpawnVolumePos;

	/** Base dimension for the SpawnVolume */
	FVector InitialSpawnVolumeDim;

	/** Can be changed with SetSpawningEnable() */
	bool bSpawningEnabled;

	/** Verify if a face is spawned, get the position from library, 
		give it parameters and spawn a new Face, then update the library*/
	void SpawnFace();

	/** Find the Actor to move with it name and move it*/
	void MoveFace();

	/** Find the Actor to delete with it name and destroy it */
	void DeleteFace();

	/** Verify if a sound is spawned, get the position and the viewDirection from library,
	give it parameters and spawn a new Face, then update the library*/
	void SpawnSound();

	/** Find the Actor to move with it name and move it*/
	void MoveSound();

	/** Find the Actor to delete with it name and destroy it */
	void DeleteSound();

	/** Handles the enable/disable sound of an existing Sound */
	void IOSound();

	/** The timer for when to spawn the Obect, update every tick */
	float SpawnTime;


	
};
