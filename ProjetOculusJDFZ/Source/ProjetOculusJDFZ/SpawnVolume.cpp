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

	std::list<float> posOne;
	posOne.push_back(0.f);
	posOne.push_back(0.f);
	posOne.push_back(0.f);

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

	//add a sound source
	std::list<float> posTwo;
	posTwo.push_back(800.f);
	posTwo.push_back(0.f);
	posTwo.push_back(300.f);
	std::vector<float> viewDirectionOne;
	viewDirectionOne.push_back(-20.f);
	viewDirectionOne.push_back(0.f);
	viewDirectionOne.push_back(0.f);
	std::vector<float> upDirectionOne;
	viewDirectionOne.push_back(0.f);
	viewDirectionOne.push_back(0.f);
	viewDirectionOne.push_back(0.f);

	library->add_sound_source("SourceOne", posTwo, viewDirectionOne, upDirectionOne, 1);
		
}

void ASpawnVolume::Tick(float DeltaSeconds)
{
	//Is there a face to spawn?
	if (bSpawningEnabled)
	{
		//increment the time befor spawnng
		SpawnTime += DeltaSeconds;

		if (SpawnTime > SpawnDelay)
		{
			//Skip if there is no face to spawn
			if (library->isFacesToSpawnEmpty() == false) {
				SpawnFace();

				//Restart the timer
				SpawnTime -= SpawnDelay;
			}

			//Skip if there is no sound to spawn
			if (library->isSoundToSpawnEmpty() == false) {
				SpawnSound();
			}
		}


	}

	//Is there a face to move?
	if (library->isFacesToMoveEmpty() == false) {
		MoveFace();
	}

	//Is there a face to delete?
	if (library->isFacesToDeleteEmpty() == false) {
		DeleteFace();
	}

	//Is there a sound to move?
	if (library->isSoundToMoveEmpty() == false) {
		MoveSound();
	}

	//Is there a sound to delete?
	if (library->isSoundToDeleteEmpty() == false) {
		DeleteSound();
	}
}

void ASpawnVolume::SpawnFace()
{
	Counter += 1;
		//Check the world is valid
		UWorld* const World = GetWorld();
		if (World)
		{

			//Get the current face to spawn
			Face* newFace = library->getNextFaceToSpawn();

			//Verify this face doesn't already exist
			FString searchedFace = FString(TEXT("Face")) + FString::SanitizeFloat(newFace->getFaceId());

			if (IsActorAlreadySpawned(searchedFace) == false) {
					//Extract the position of the face to spawn
					std::list<float> facePositionList = newFace->getPosition();
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

					//Set the spawn parameters
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = Instigator;
					SpawnParams.Name = FName(*searchedFace);

					//Spawn the face, and update the library
					AProceduralFaceActor* const SpawnedFace = World->SpawnActor<AProceduralFaceActor>(SpawnLocation, FRotator(0.f, 0.f, 0.f), SpawnParams);
					library->getNextFaceToSpawn()->setFaceSpawned(true);
					library->deleteFaceSpawned();

					//Test hard coded part
					if (Counter == 6) {
						std::list<float> posTwo;
						posTwo.push_back(-300.f);
						posTwo.push_back(0.f);
						posTwo.push_back(3000.f);
						library->move_face(posTwo, 1);
						library->remove_face(2);
					}
				}
		}
}

void ASpawnVolume::SpawnSound()
{
	//Check the world is valid
	UWorld* const World = GetWorld();
	if (World)
	{
		//Get the current sound to spawn
		Sound* newSound = library->getNextSoundToSpawn();

		//Verify this sound doesn't already exist
		FString searchedSound = FString(TEXT("Sound")) + FString::SanitizeFloat(newSound->getSourceId());
		if (IsActorAlreadySpawned(searchedSound) == false) {
			//Extract the position of the sound to spawn
			std::list<float> soundPositionList = newSound->getPosition();
			FVector SpawnLocation;
			if (soundPositionList.size() >= 3){
				SpawnLocation.X = soundPositionList.front();
				std::list<float>::iterator itY = soundPositionList.begin();
				std::advance(itY, 1);
				SpawnLocation.Y = *itY;
				std::list<float>::iterator itZ = soundPositionList.begin();
				std::advance(itZ, 2);
				SpawnLocation.Z = *itZ;
			}

			//Extracte the viewDirection to have the rotation
			std::vector<float> soundViewDirection = newSound->getViewDirection();
			FVector viewDirection;
			if (soundViewDirection.size() >= 3){
				viewDirection.X = soundViewDirection.front();
				std::vector<float>::iterator itY = soundViewDirection.begin();
				std::advance(itY, 1);
				viewDirection.Y = *itY;
				std::vector<float>::iterator itZ = soundViewDirection.begin();
				std::advance(itZ, 2);
				viewDirection.Z = *itZ;
			}
			//rotation around Y axis (look up or down), 0 = straight, + up and - down
			float rotationFirtstValue = viewDirection.Z;
			//rotation around Z axis of the object
			float rotationSecondValue;
			if (viewDirection.X != 0.f) {
				if (viewDirection.X > 0) {
					rotationSecondValue = FMath::Atan(viewDirection.Y / viewDirection.X);
				}
				else {
					rotationSecondValue = FMath::Atan(viewDirection.Y / viewDirection.X) + 180.f;
				}				
			}
			else {
				if (viewDirection.Y > 0){
					rotationSecondValue = 90.f;
				}
				else {
					rotationSecondValue = 270.f;
				}
			}			
			//rotation around X axis of the object
			float rotationThirdValue = 0.f;
			FRotator SpawnRotation = FRotator(rotationFirtstValue, rotationSecondValue, rotationThirdValue);

			//Set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			SpawnParams.Name = FName(*searchedSound);

			//Spawn the face, and update the library
			AProceduralSoundActor* const SpawnedFace = World->SpawnActor<AProceduralSoundActor>(SpawnLocation, SpawnRotation, SpawnParams);
			library->getNextSoundToSpawn()->setSoundSpawned(true);
			library->deleteSoundSpawned();
		}
	}
}

void ASpawnVolume::MoveFace()
{
	Face* movedFace = library->getNextFaceToMove();
	FVector newPosition;
	std::list<float> facePositionList = movedFace->getPosition();
	if (facePositionList.size() >= 3) {
		newPosition.X = facePositionList.front();
		std::list<float>::iterator itY = facePositionList.begin();
		std::advance(itY, 1);
		newPosition.Y = *itY;
		std::list<float>::iterator itZ = facePositionList.begin();
		std::advance(itZ, 2);
		newPosition.Z = *itZ;
	}	
	//Find the actor from the face
	FString searchedFace = FString(TEXT("Face")) + FString::SanitizeFloat(movedFace->getFaceId());
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)	{
		if (ActorItr->GetName() == searchedFace) {
			//Teleport the actor to the new location
			ActorItr->SetActorLocation(newPosition, false);
		}
	}
	library->deleteFaceMoved();
}

void ASpawnVolume::MoveSound()
{
	Sound* movedSound = library->getNextSoundToMove();
	FVector newPosition;
	std::list<float> soundPositionList = movedSound->getPosition();
	if (soundPositionList.size() >= 3) {
		newPosition.X = soundPositionList.front();
		std::list<float>::iterator itY = soundPositionList.begin();
		std::advance(itY, 1);
		newPosition.Y = *itY;
		std::list<float>::iterator itZ = soundPositionList.begin();
		std::advance(itZ, 2);
		newPosition.Z = *itZ;
	}
	//Find the actor from the face
	FString searchedSound = FString(TEXT("Sound")) + FString::SanitizeFloat(movedSound->getSourceId());
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName() == searchedSound) {
			//Teleport the actor to the new location
			ActorItr->SetActorLocation(newPosition, false);
		}
	}
	library->deleteSoundMoved();
}

void ASpawnVolume::DeleteFace()
{
	int faceId = library->getNextFaceIdToDelete();
	FString searchedFace = FString(TEXT("Face")) + FString::SanitizeFloat((float)faceId);
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName() == searchedFace) {
			ActorItr->Destroy();
			break;
		}
	}
	library->deleteFaceDeleted();
}

void ASpawnVolume::DeleteSound()
{
	int soundId = library->getNextSoundIdToDelete();
	FString searchedSound = FString(TEXT("Sound")) + FString::SanitizeFloat((float)soundId);
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName() == searchedSound) {
			ActorItr->Destroy;
			break;
		}
	}
	library->deleteFaceDeleted();
}

void ASpawnVolume::SetSpawningEnable(bool isEnable)
{
	bSpawningEnabled = isEnable;
}

void ASpawnVolume::SetSpawnVolumeDimension(float NewX, float NewY, float NewZ)
{
	InitialSpawnVolumeDim = FVector(NewX, NewY, NewZ);
}

bool ASpawnVolume::IsActorAlreadySpawned(FString FaceName){
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName() == FaceName) {
			return true;
		}
	}
	return false;
}