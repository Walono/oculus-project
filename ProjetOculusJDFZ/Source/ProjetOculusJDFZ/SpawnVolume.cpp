// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProceduralFaceActor.h"
#include "ProceduralSoundActor.h"
#include "Library.h"
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
	SpawnDelay = 1.f;


	//Make the SpawnVolume tickable.
	PrimaryActorTick.bCanEverTick = true;

	//TODO Use a key after to set it true/false
	SetSpawningEnable(true);
	Counter = 0;

	library = Library::getLibrary();
	//Face::Face(std::list<float> position, std::list<std::list<float>> coordinates,
	//	int texture, int faceId)
	std::list<float> posOne;
	posOne.push_back(0.f);
	posOne.push_back(0.f);
	posOne.push_back(0.f);

	std::list<std::list<float>> coordiOne;
	std::list<float> coordOne00;
	coordOne00.push_back(0.f);
	coordOne00.push_back(0.f);
	coordOne00.push_back(0.f);
	coordiOne.push_back(coordOne00);

	std::list<float> coordOne01;
	coordOne01.push_back(0.f);
	coordOne01.push_back(400.f);
	coordOne01.push_back(0.f);
	coordiOne.push_back(coordOne01);

	std::list<float> coordOne02;
	coordOne02.push_back(0.f);
	coordOne02.push_back(400.f);
	coordOne02.push_back(200.f);
	coordiOne.push_back(coordOne02);

	/////////////////////////////

	std::list<std::list<float>> coordiTwo;
	std::list<float> coordOne10;
	coordOne10.push_back(0.f);
	coordOne10.push_back(0.f);
	coordOne10.push_back(0.f);
	coordiTwo.push_back(coordOne10);

	std::list<float> coordOne11;
	coordOne11.push_back(0.f);
	coordOne11.push_back(400.f);
	coordOne11.push_back(0.f);
	coordiTwo.push_back(coordOne11);

	std::list<float> coordOne12;
	coordOne12.push_back(0.f);
	coordOne12.push_back(400.f);
	coordOne12.push_back(200.f);
	coordiTwo.push_back(coordOne12);

	std::list<float> coordOne13;
	coordOne13.push_back(0.f);
	coordOne13.push_back(200.f);
	coordOne13.push_back(6000.f);
	coordiTwo.push_back(coordOne13);

	std::list<float> coordOne14;
	coordOne14.push_back(0.f);
	coordOne14.push_back(0.f);
	coordOne14.push_back(200.f);
	coordiTwo.push_back(coordOne14);

	library->add_face(posOne, coordiOne, 0, 1);
	library->add_face(posOne, coordiTwo, 0, 2);
	library->add_face(posOne, coordiOne, 0, 3);
	library->add_face(posOne, coordiOne, 0, 4);
	library->add_face(posOne, coordiTwo, 0, 5);
	library->add_face(posOne, coordiOne, 0, 6);

}

void ASpawnVolume::SpawnObject()
{
	Counter += 1;
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

			if (Counter % 100 != 0) {
				AProceduralFaceActor* const SpawnedFace = World->SpawnActor<AProceduralFaceActor>(SpawnLocation, SpawnRotation, SpawnParams);
				//SpawnedFace->PostInitializeComponents();
				library->deleteFaceSpawned();
			}
			else {
				AProceduralSoundActor* const SpawnedSound = World->SpawnActor<AProceduralSoundActor>(SpawnLocation, SpawnRotation, SpawnParams);
			}
			

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
		//Do nothing if there is no face to spawn
		if (library->isFacesToSpawnEmpty() == false){

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
}

void ASpawnVolume::SetSpawningEnable(bool isEnable)
{
	bSpawningEnabled = isEnable;
}

void ASpawnVolume::SetSpawnVolumeDimension(float NewX, float NewY, float NewZ)
{
	InitialSpawnVolumeDim = FVector(NewX, NewY, NewZ);
}