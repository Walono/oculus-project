// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Library.h"
#include "SpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOCULUSJDFZ_API ASpawnVolume : public AActor
{
	GENERATED_UCLASS_BODY()

	/** BoxComponent to specify the spawning area within the level */
	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	TSubobjectPtr<UBoxComponent> WhereToSpawn;

	/** The delay of the delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelay;

	/** ovverdide the tick to spawn object on the right time */
	virtual void Tick(float DeltSeconds) override;

	/** change the dimension of the spawnVolum according to the level dim */
	UFUNCTION()
	void SetSpawnVolumeDimension(float NewX, float NewY, float NewZ);

	/** Enable/disable the spawning behaviours */
	UFUNCTION()
	void SetSpawningEnable(bool isEnable);

	/** Verify if a FName already existe or not */
	bool IsActorAlreadySpawned(FString FaceName);

private:
	int32 Counter;

	/** The container of all object to spawn */
	Library * library;

	/** Base location for the SpawnVolume. */
	FVector InitialSpawnVolumePos;

	/** Base dimension for the SpawnVolume */
	FVector InitialSpawnVolumeDim;

	/** Can be changed with SetSpawningEnable */
	bool bSpawningEnabled;

	/** Handles the spawning of a new Face */
	void SpawnFace();

	/** Handles the move of an existing Face */
	void MoveFace();

	/** Handles the delete of an existing Face */
	void DeleteFace();

	/** Handles the spawning of a Sound */
	void SpawnSound();

	/** Handles the move of an existing Sound */
	void MoveSound();

	/** Handles the delete of an existing Sound */
	void DeleteSound();

	/** The timer for when to spawn the Obect */
	float SpawnTime;


	
};
