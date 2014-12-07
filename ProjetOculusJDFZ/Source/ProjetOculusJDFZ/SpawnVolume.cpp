// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProceduralFaceActor.h"
#include "SpawnVolume.h"


ASpawnVolume::ASpawnVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//TODO: Find a way to self generate the spawnVolum without the editor

	//Set the initial position and size of our  spawnVolum
	InitialSpawnVolumeDim = FVector(10000.f, 10000.f, 10000.f);
	InitialSpawnVolumePos = FVector(0.f, 0.f, 1000.f);

	//Create a simple StaticMeshComponent to represent the level
	WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));
	WhereToSpawn->SetBoxExtent(InitialSpawnVolumeDim);
	WhereToSpawn->SetWorldLocation(InitialSpawnVolumePos);
	WhereToSpawn->AttachTo(RootComponent);

	//Set the spawn delay
	SpawnDelay = 0.1f;


	//Make the SpawnVolume tickable.
	PrimaryActorTick.bCanEverTick = true;

	//TODO Use a key after to set it true/false
	SetSpawningEnable(true);
}

void ASpawnVolume::SpawnObject()
{

		//Check the world is valid
		UWorld* const World = GetWorld();
		if (World)
		{
			//TODO: Switch between diferent object to generate

			//Set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//Get a random location to spawn at
			FVector SpawnLocation = GetRandomPointInVolum();

			//Get a random rotation for the spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.f;
			SpawnRotation.Pitch = FMath::FRand() * 360.f;
			SpawnRotation.Roll = FMath::FRand() * 360.f;

			AProceduralFaceActor* const SpawnedFace = World->SpawnActor<AProceduralFaceActor>(SpawnLocation, SpawnRotation, SpawnParams);

		}
}


FVector ASpawnVolume::GetRandomPointInVolum()
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
	BoxExtent = InitialSpawnVolumeDim;

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
	if (bSpawningEnabled)
	{
		//increment the time befor spawnng
		SpawnTime += DeltaSeconds;

		if (SpawnTime > SpawnDelay)
		{
			SpawnObject();

			//Restart the timer
			SpawnTime -= SpawnDelay;
		}
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