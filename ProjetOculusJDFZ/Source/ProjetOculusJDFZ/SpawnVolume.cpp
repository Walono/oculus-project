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
	SpawnDelay = 500000.f;


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

	std::list<float> posTwo;
	posTwo.push_back(-300.f);
	posTwo.push_back(0.f);
	posTwo.push_back(100.f);

	//Base floor
	std::list<std::list<float>> coordiOne;
	std::list<float> coordOne00;
	coordOne00.push_back(300.f);
	coordOne00.push_back(-500.f);
	coordOne00.push_back(100.f);
	coordiOne.push_back(coordOne00);

	std::list<float> coordOne01;
	coordOne01.push_back(300.f);
	coordOne01.push_back(500.f);
	coordOne01.push_back(100.f);
	coordiOne.push_back(coordOne01);

	std::list<float> coordOne02;
	coordOne02.push_back(1300.f);
	coordOne02.push_back(500.f);
	coordOne02.push_back(100.f);
	coordiOne.push_back(coordOne02);

	std::list<float> coordOne03;
	coordOne03.push_back(1300.f);
	coordOne03.push_back(-500.f);
	coordOne03.push_back(100.f);
	coordiOne.push_back(coordOne03);

	//Left wall
	std::list<std::list<float>> coordiTwo;
	std::list<float> coordiTwo0;
	coordiTwo0.push_back(300.f);
	coordiTwo0.push_back(-500.f);
	coordiTwo0.push_back(100.f);
	coordiTwo.push_back(coordiTwo0);

	std::list<float> coordiTwo1;
	coordiTwo1.push_back(300.f);
	coordiTwo1.push_back(-500.f);
	coordiTwo1.push_back(800.f);
	coordiTwo.push_back(coordiTwo1);

	std::list<float> coordiTwo2;
	coordiTwo2.push_back(1300.f);
	coordiTwo2.push_back(-500.f);
	coordiTwo2.push_back(800.f);
	coordiTwo.push_back(coordiTwo2);

	std::list<float> coordiTwo3;
	coordiTwo3.push_back(1300.f);
	coordiTwo3.push_back(-500.f);
	coordiTwo3.push_back(100.f);
	coordiTwo.push_back(coordiTwo3);

	//Back wall
	std::list<std::list<float>> coordiTree;
	std::list<float> coordiTree0;
	coordiTree0.push_back(1300.f);
	coordiTree0.push_back(-500.f);
	coordiTree0.push_back(100.f);
	coordiTree.push_back(coordiTree0);

	std::list<float> coordiTree1;
	coordiTree1.push_back(1300.f);
	coordiTree1.push_back(-500.f);
	coordiTree1.push_back(800.f);
	coordiTree.push_back(coordiTree1);

	std::list<float> coordiTree2;
	coordiTree2.push_back(1300.f);
	coordiTree2.push_back(500.f);
	coordiTree2.push_back(800.f);
	coordiTree.push_back(coordiTree2);
	
	std::list<float> coordiTree3;
	coordiTree3.push_back(1300.f);
	coordiTree3.push_back(500.f);
	coordiTree3.push_back(100.f);
	coordiTree.push_back(coordiTree3);

	//Right wall
	std::list<std::list<float>> coordiFour;
	std::list<float> coordiFour0;
	coordiFour0.push_back(1300.f);
	coordiFour0.push_back(500.f);
	coordiFour0.push_back(100.f);
	coordiFour.push_back(coordiFour0);

	std::list<float> coordiFour1;
	coordiFour1.push_back(1300.f);
	coordiFour1.push_back(500.f);
	coordiFour1.push_back(800.f);
	coordiFour.push_back(coordiFour1);

	std::list<float> coordiFour2;
	coordiFour2.push_back(300.f);
	coordiFour2.push_back(500.f);
	coordiFour2.push_back(800.f);
	coordiFour.push_back(coordiFour2);

	std::list<float> coordiFour3;
	coordiFour3.push_back(300.f);
	coordiFour3.push_back(500.f);
	coordiFour3.push_back(100.f);
	coordiFour.push_back(coordiFour3);

	//Front wall right from door
	std::list<std::list<float>> coordiFive;
	std::list<float> coordiFive0;
	coordiFive0.push_back(300.f);
	coordiFive0.push_back(500.f);
	coordiFive0.push_back(100.f);
	coordiFive.push_back(coordiFive0);

	std::list<float> coordiFive1;
	coordiFive1.push_back(300.f);
	coordiFive1.push_back(500.f);
	coordiFive1.push_back(800.f);
	coordiFive.push_back(coordiFive1);

	std::list<float> coordiFive2;
	coordiFive2.push_back(300.f);
	coordiFive2.push_back(100.f);
	coordiFive2.push_back(800.f);
	coordiFive.push_back(coordiFive2);

	std::list<float> coordiFive3;
	coordiFive3.push_back(300.f);
	coordiFive3.push_back(100.f);
	coordiFive3.push_back(100.f);
	coordiFive.push_back(coordiFive3);

	//Front wall left from door
	std::list<std::list<float>> coordiSix;
	std::list<float> coordiSix0;
	coordiSix0.push_back(300.f);
	coordiSix0.push_back(-100.f);
	coordiSix0.push_back(100.f);
	coordiSix.push_back(coordiSix0);

	std::list<float> coordiSix1;
	coordiSix1.push_back(300.f);
	coordiSix1.push_back(-100.f);
	coordiSix1.push_back(800.f);
	coordiSix.push_back(coordiSix1);

	std::list<float> coordiSix2;
	coordiSix2.push_back(300.f);
	coordiSix2.push_back(-500.f);
	coordiSix2.push_back(800.f);
	coordiSix.push_back(coordiSix2);

	std::list<float> coordiSix3;
	coordiSix3.push_back(300.f);
	coordiSix3.push_back(-500.f);
	coordiSix3.push_back(100.f);
	coordiSix.push_back(coordiSix3);

	//Front wall up from door
	std::list<std::list<float>> coordiSeven;
	std::list<float> coordiSeven0;
	coordiSeven0.push_back(300.f);
	coordiSeven0.push_back(-100.f);
	coordiSeven0.push_back(350.f);
	coordiSeven.push_back(coordiSeven0);

	std::list<float> coordiSeven1;
	coordiSeven1.push_back(300.f);
	coordiSeven1.push_back(-100.f);
	coordiSeven1.push_back(800.f);
	coordiSeven.push_back(coordiSeven1);

	std::list<float> coordiSeven2;
	coordiSeven2.push_back(300.f);
	coordiSeven2.push_back(100.f);
	coordiSeven2.push_back(800.f);
	coordiSeven.push_back(coordiSeven2);

	std::list<float> coordiSeven3;
	coordiSeven3.push_back(300.f);
	coordiSeven3.push_back(100.f);
	coordiSeven3.push_back(350.f);
	coordiSeven.push_back(coordiSeven3);

	//Roof
	std::list<std::list<float>> coordiHeight;
	std::list<float> coordiHeight0;
	coordiHeight0.push_back(300.f);
	coordiHeight0.push_back(-500.f);
	coordiHeight0.push_back(800.f);
	coordiHeight.push_back(coordiHeight0);

	std::list<float> coordiHeight1;
	coordiHeight1.push_back(300.f);
	coordiHeight1.push_back(500.f);
	coordiHeight1.push_back(800.f);
	coordiHeight.push_back(coordiHeight1);

	std::list<float> coordiHeight2;
	coordiHeight2.push_back(1300.f);
	coordiHeight2.push_back(500.f);
	coordiHeight2.push_back(800.f);
	coordiHeight.push_back(coordiHeight2);

	std::list<float> coordiHeight3;
	coordiHeight3.push_back(1300.f);
	coordiHeight3.push_back(-500.f);
	coordiHeight3.push_back(800.f);
	coordiHeight.push_back(coordiHeight3);


	library->add_face(posOne, coordiOne, 0, 1);
	library->add_face(posOne, coordiTwo, 0, 2);
	library->add_face(posOne, coordiTree, 0, 3);
	library->add_face(posOne, coordiFour, 0, 4);
	library->add_face(posOne, coordiFive, 0, 5);
	library->add_face(posOne, coordiSix, 0, 6);
	library->add_face(posOne, coordiSeven, 0, 7);
	library->add_face(posOne, coordiHeight, 0, 8);
	library->move_face(posTwo, 1);

}

void ASpawnVolume::SpawnFace()
{
	Counter += 1;
		//Check the world is valid
		UWorld* const World = GetWorld();
		if (World)
		{

			//Set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//Get the current coordinat from our object.
			Face newFace = library->getNextFaceToSpawn();
			std::list<float> facePositionList = newFace.getPosition();
			FVector SpawnLocation;
			if (facePositionList.size() >= 3){
				SpawnLocation.X = facePositionList.front();
				std::list<float>::iterator itY = facePositionList.begin();
				std::advance(itY, 1);
				SpawnLocation.Y = *itY;
				std::list<float>::iterator itZ = facePositionList.begin();
				std::advance(itZ, 2);
				SpawnLocation.Z = *itZ;
			}
			
			FRotator SpawnRotation = FRotator(0.f,0.f,0.f);

			AProceduralFaceActor* const SpawnedFace = World->SpawnActor<AProceduralFaceActor>(SpawnLocation, SpawnRotation, SpawnParams);
			newFace.setProceduralFaceActor(SpawnedFace);
			library->deleteFaceSpawned();
		}
}

void ASpawnVolume::MoveFace()
{
	Face movedFace = library->getNextFaceToMove();
	FVector newPosition;
	std::list<float> facePositionList = movedFace.getPosition();
	if (facePositionList.size() >= 3){
		newPosition.X = facePositionList.front();
		std::list<float>::iterator itY = facePositionList.begin();
		std::advance(itY, 1);
		newPosition.Y = *itY;
		std::list<float>::iterator itZ = facePositionList.begin();
		std::advance(itZ, 2);
		newPosition.Z = *itZ;
	}	
	movedFace.getProceduralFaceActor()->SetActorLocation(newPosition, true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Mouve!!!!!"));
}

void ASpawnVolume::Tick(float DeltaSeconds)
{
	//Do nothing if spawning aren't enable
	if (bSpawningEnabled)
	{
		//Skip if there is no face to spawn
		if (library->isFacesToSpawnEmpty() == false) {

			//increment the time befor spawnng
			SpawnTime += DeltaSeconds;

			if (SpawnTime > SpawnDelay)
			{
				SpawnFace();
	
				//Restart the timer
				SpawnTime -= SpawnDelay;
			}
		}
	}
	//Test if
	if (Counter > 4) {
		
		//Skip if there is no face to move
		if (library->isFacesToMoveEmpty() == false) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mouve???"));
			MoveFace();
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