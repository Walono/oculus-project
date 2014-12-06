// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
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

	/** Find a random point in the level */
	UFUNCTION(BlueprintPure, Category = Spawning)
	FVector GetRandomPointInVolum();

	/** ovverdide the tick to spawn object on the right time */
	virtual void Tick(float DeltSeconds) override;

	//TODO: add a addObjectToList(Object o) methode to add an abject in the list

	/** change the dimension of the spawnVolum according to the level dim */
	UFUNCTION()
		void SetSpawnVolumeDimension(float NewX, float NewY, float NewZ);

	/** Enable/disable the spawning behaviours */
	UFUNCTION()
	void SetSpawningEnable(bool isEnable);

private:

	/** Base location for the SpawnVolume. */
	FVector InitialSpawnVolumePos;

	/** Base dimension for the SpawnVolume */
	FVector InitialSpawnVolumeDim;

	/** Can be changed with SetSpawningEnable */
	bool bSpawningEnabled;

	//TODO: add a list of spawnable obect we can fil.

	/** Handles the spawning of a new Obect */
	void SpawnObject();

	/** The timer for when to spawn the Obect */
	float SpawnTime;
	
};
