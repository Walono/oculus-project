// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProjetOculusJDFZGameMode.h"
#include "Engine.h"
#include "OculusHUD.h"
#include "FakeServer.h"



AProjetOculusJDFZGameMode::
AProjetOculusJDFZGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Set the default pawn class, respectivly our character
	DefaultPawnClass = AOculusCharacter::StaticClass();

	//Set the default HUD class
	HUDClass = AOculusHUD::StaticClass();

	library = Library::getLibrary();
}

void AProjetOculusJDFZGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartMatch();

	//Wrtie a wellcome message the 5 first seconds
	if (GEngine)
	{
<<<<<<< HEAD
		GEngine->AddOnScreenDebugMessage(-1, 5.f,
			FColor::Yellow, TEXT("HELLO WORLD"));
=======
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Wellcome to the simulation"));
>>>>>>> 6dc8f40f518fdfcc7f32e55f232c2529f34794ae
	}

	//find all spawn volume actor and store them
	TArray<AActor*> FoundActors;
<<<<<<< HEAD

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), 
		ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
=======
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)	{
>>>>>>> 6dc8f40f518fdfcc7f32e55f232c2529f34794ae
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.Add(SpawnVolumeActor);
		}
	}
	//We currently don't need torstart the position
	library->setResetActivity(false);

	std::list<float> initPos;
	initPos.push_back(0.f);
	initPos.push_back(0.f);
	initPos.push_back(50.f);
	library->set_initial_position(initPos);

	FakeServer fakeServer = FakeServer::FakeServer();
	fakeServer.startSendingData();

	SetCurrentState(EOculusProjectPlayStats::EInitialization);
}

void AProjetOculusJDFZGameMode::
SetCurrentState(EOculusProjectPlayStats NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void AProjetOculusJDFZGameMode::HandleNewState(EOculusProjectPlayStats NewState)
{
<<<<<<< HEAD
	//Get the current character and it's controller. 
	//As we have only one of both, it is the character and controller 0.
	APlayerController* PlayerController = 
		UGameplayStatics::GetPlayerController(this, 0);
	AOculusCharacter* MyCharacter = 
		Cast<AOculusCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));	
=======
	//Get the current character and its controller. As we have only one of both, it is the character and controller 0.
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AOculusCharacter* MyCharacter = Cast<AOculusCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

>>>>>>> 6dc8f40f518fdfcc7f32e55f232c2529f34794ae
	switch (NewState)
	{
	case EOculusProjectPlayStats::EInitialization:
		//disable the possibility to move befor entering the spawning state		
		PlayerController->SetIgnoreMoveInput(true);
		MyCharacter->setIsResetButtonPressed(false);
		//at initializazion state, nothing spawn
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningEnable(false);
		}
		break;
	case EOculusProjectPlayStats::ESpawningEnable:
	{
		//Player can now move normaly
		PlayerController->SetIgnoreMoveInput(false);
		//at spawning state, spawnVolume can spawn element
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningEnable(true);
		}
		
		
		//Extracte the initial position
		std::list<float> newInitialPosition = library->getInitialPosition();
		FVector CharacterInitialPosition;
		if (newInitialPosition.size() >= 3){
			CharacterInitialPosition.X = newInitialPosition.front();
			std::list<float>::iterator itY = newInitialPosition.begin();
			std::advance(itY, 1);
			CharacterInitialPosition.Y = *itY;
			std::list<float>::iterator itZ = newInitialPosition.begin();
			std::advance(itZ, 2);
			//add 50.f to fall on your point, 
			//and give the editor the time to spawn your floor
			CharacterInitialPosition.Z = *itZ + 50.f;
		}
		//Teleport the character to the new position
		MyCharacter->SetActorLocation(CharacterInitialPosition, false);
		break;
	}

	case EOculusProjectPlayStats::EUnknow:
	default:
		//do nothing
		break;
	}
}


