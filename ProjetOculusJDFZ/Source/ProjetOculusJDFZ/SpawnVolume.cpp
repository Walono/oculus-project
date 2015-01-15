// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProceduralFaceActor.h"
#include "ProceduralSoundActor.h"
#include "Library.h"
#include "OculusCharacter.h"
#include "SpawnVolume.h"


ASpawnVolume::ASpawnVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//TODO: create and spawn this actor in the GameMode during the initialize state or beginPlay()

	//Set the initial position and size of our  spawnVolum
	InitialSpawnVolumeDim = FVector(10000.f, 10000.f, 10000.f);
	InitialSpawnVolumePos = FVector(0.f, 0.f, 1000.f);

	//Create a simple StaticMeshComponent to represent the level
	WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));
	WhereToSpawn->SetBoxExtent(InitialSpawnVolumeDim);
	WhereToSpawn->SetWorldLocation(InitialSpawnVolumePos);
	WhereToSpawn->AttachTo(RootComponent);

	SpawnDelay = 500000.f;

	//Make the SpawnVolume tickable.
	PrimaryActorTick.bCanEverTick = true;

	library = Library::getLibrary();
}

void ASpawnVolume::Tick(float DeltaSeconds)
{
	// Do we need to reset the position of the character
	if (library->getResetActivity()) {
		AOculusCharacter* MyCharacter = Cast<AOculusCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		MyCharacter->ResetCharacterPosition();
		library->setResetActivity(false);
	}

	//Can this class spawn element? 
	if (bSpawningEnabled)
	{
		//increment the time befor spawnng
		SpawnTime += DeltaSeconds;

		if (SpawnTime > SpawnDelay)
		{
			//Is there a face to spawn?
			if (library->isFacesToSpawnEmpty() == false) {
				SpawnFace();

				//Restart the timer
				SpawnTime -= SpawnDelay;
			}
			//Is thete a sound to spawn?
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

	//Is there a sound to enable/disable?
	if (library->isSoundToEnableEmpty() == false) {
		IOSound();
	}
}

void ASpawnVolume::SpawnFace()
{
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

			//Spawn the sound, and update the library
			AProceduralSoundActor* const SpawnedFace = World->SpawnActor<AProceduralSoundActor>(SpawnLocation, SpawnRotation, SpawnParams);
			library->getNextSoundToSpawn()->setSoundSpawned(true);
			library->deleteSoundSpawned();
		}
	}
}

void ASpawnVolume::MoveFace()
{
	Face* movedFace = library->getNextFaceToMove();	

	//Extracte the translation value and put it in a FVector
	FVector newTranslation;
	std::list<float> faceTranslationList = movedFace->getTranslationVector();
	if (faceTranslationList.size() >= 3) {
		newTranslation.X = faceTranslationList.front();
		std::list<float>::iterator itY = faceTranslationList.begin();
		std::advance(itY, 1);
		newTranslation.Y = *itY;
		std::list<float>::iterator itZ = faceTranslationList.begin();
		std::advance(itZ, 2);
		newTranslation.Z = *itZ;
	}	

	//Extracte the rotationValue and put it in a FRotator
	FRotator newRotation;
	std::list<float> faceRotationList = movedFace->getRotation();
	if (faceRotationList.size() >= 3) {
		newRotation.Pitch = faceRotationList.front();
		std::list<float>::iterator itY = faceRotationList.begin();
		std::advance(itY, 1);
		newRotation.Yaw = *itY;
		std::list<float>::iterator itZ = faceRotationList.begin();
		std::advance(itZ, 2);
		newRotation.Roll = *itZ;
	}

	//Find the actor from the face
	FString searchedFace = FString(TEXT("Face")) + FString::SanitizeFloat(movedFace->getFaceId());
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)	{
		if (ActorItr->GetName() == searchedFace) {
			//Teleport the actor to the new location
			ActorItr->SetActorLocation(newTranslation, false);
			ActorItr->SetActorRotation(newRotation);
		}
	}
	library->deleteFaceMoved();
}

void ASpawnVolume::MoveSound()
{
	Sound* movedSound = library->getNextSoundToMove();

	//Extracte the translation value and put it in a FVector
	FVector newTranslation;
	std::list<float> soundPositionList = movedSound->getPosition();
	if (soundPositionList.size() >= 3) {
		newTranslation.X = soundPositionList.front();
		std::list<float>::iterator itY = soundPositionList.begin();
		std::advance(itY, 1);
		newTranslation.Y = *itY;
		std::list<float>::iterator itZ = soundPositionList.begin();
		std::advance(itZ, 2);
		newTranslation.Z = *itZ;
	}
	//Get and update the viewDirection
	//Extracte the viewDirection to have the rotation
	std::vector<float> soundViewDirection = movedSound->getViewDirection();
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
	FRotator newRotation = FRotator(rotationFirtstValue, rotationSecondValue, rotationThirdValue);

	//Find the actor from the sound and modify it
	FString searchedSound = FString(TEXT("Sound")) + FString::SanitizeFloat(movedSound->getSourceId());
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName() == searchedSound) {
			//Teleport the actor to the new location
			ActorItr->SetActorLocation(newTranslation, false);
			ActorItr->SetActorRotation(newRotation);
		}
	}
	library->deleteSoundMoved();
}

void ASpawnVolume::DeleteFace()
{
	// Find the Actor with it name in all actor and destroy it
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
	// Find the Actor with it name in all actor and destroy it
	int soundId = library->getNextSoundIdToDelete();
	FString searchedSound = FString(TEXT("Sound")) + FString::SanitizeFloat((float)soundId);
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->GetName() == searchedSound) {
			ActorItr->Destroy();
			break;
		}
	}
	library->deleteFaceDeleted();
}

void ASpawnVolume::IOSound()
{
	Sound* soundToEnable = library->getNextSoundIdToEnable();
	FString searchedSound = FString(TEXT("Sound")) + FString::SanitizeFloat((float)soundToEnable->getSourceId());

	//find the current proceduralSoundActor with it name and play/stop it
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProceduralSoundActor::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		AProceduralSoundActor* ProceduralSoundActor = Cast<AProceduralSoundActor>(Actor);
		if (ProceduralSoundActor)
		{
			ProceduralSoundActor->IOActorSound(soundToEnable->getSoundActivity());
		}
	}
}

void ASpawnVolume::SetSpawningEnable(bool isEnable)
{
	bSpawningEnabled = isEnable;
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