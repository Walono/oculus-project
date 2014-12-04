// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "SpawnVolume.h"


ASpawnVolume::ASpawnVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Set the initial pos of the spawn volume.
	InitialSpawnVolumePos = FVector(0, 0, 0);

	//Set the initial dim of the spawn volume.
	InitialSpawnVolumeDim = FVector(4600, 4600, 2500);

	//Create a simple StaticMeshComponent to represent the level
	WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));
	WhereToSpawn->SetWorldScale3D(InitialSpawnVolumeDim);
	WhereToSpawn->Bounds.Origin = InitialSpawnVolumePos;
	WhereToSpawn->AttachTo(RootComponent);

	//Set the spawn delay
	SpawnDelay = 10.f;

	//Make the SpawnVolume tickable.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnVolume::SpawnObject()
{
	//Check we have something to spawn
	if (WhatToSpawn != NULL)
	{
		//Check the world is valid
		UWorld* const World = GetWorld();
		if (World)
		{
			//TODO make it spawn
			//TODO define WhatToSpawn
		}
	}
}


FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector RandomLocation;
	float MinX;
	float MinY;
	float MinZ;
	float MaxX; 
	float MaxY;
	float MaxZ;

	FVector BoxExtent;

	//Get the SpawnVolume's box extent
	BoxExtent = WhereToSpawn->Bounds.BoxExtent;

	//Calculate the limite where to spawn
	MinX = InitialSpawnVolumePos.X - BoxExtent.X / 2.f;
	MinY = InitialSpawnVolumePos.Y - BoxExtent.Y / 2.f;
	MinZ = InitialSpawnVolumePos.Z - BoxExtent.Z / 2.f;

	MaxX = InitialSpawnVolumePos.X + BoxExtent.X / 2.f;
	MaxY = InitialSpawnVolumePos.Y + BoxExtent.Y / 2.f;
	MaxZ = InitialSpawnVolumePos.Z + BoxExtent.Z / 2.f;

	//The random spawn location will fall between the min and max
	RandomLocation.X = FMath::FRandRange(MinX, MaxX);
	RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);

	return RandomLocation;
}

void ASpawnVolume::Tick(float DeltaSeconds)
{
	//Do nothing if spawning aren't enable
	if (!bSpawningEnabled)
	{
		return
	}

	//increment the time befor spawnng
	SpawnTime += DeltaSeconds;

	if (SpawnTime > SpawnDelay)
	{
		SpawnObject();

		//Restart the timer
		SpawnTime = 0;
	}
}

void ASpawnVolume::SetSpawningEnable(bool isEnable)
{
	bSpawningEnabled = isEnable;
}

void ASpawnVolume::SetSpawnVolumeDimension(float NewX, float NewY, float NewZ)
{
	InitialSpawnVolumeDim = FVector(NewX, NewY, NewZ);
}