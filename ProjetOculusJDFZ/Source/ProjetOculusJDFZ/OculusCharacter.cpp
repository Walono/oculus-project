// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "OculusCharacter.h"
#include "ProjetOculusJDFZGameMode.h"
#include "Kismet/GameplayStatics.h"


AOculusCharacter::
AOculusCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	buttonPressedDelay = 3.0f;
}

void AOculusCharacter::
SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, 
		&AOculusCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, 
		&AOculusCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, 
		&AOculusCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, 
		&AOculusCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, 
		&AOculusCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, 
		&AOculusCharacter::OnStopJump);
	InputComponent->BindAction("StartSpawning", IE_Pressed, this, 
		&AOculusCharacter::OnStartSpawning);
	InputComponent->BindAction("StartSpawning", IE_Released, this, 
		&AOculusCharacter::OnReleaseSpawning);
	InputComponent->BindAction("ResetPosition", IE_Pressed, this, 
		&AOculusCharacter::OnStartReset);
	InputComponent->BindAction("ResetPosition", IE_Released, this, 
		&AOculusCharacter::OnReleaseReset);
}

void AOculusCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (CharacterMovement->IsMovingOnGround() || 
			CharacterMovement->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = 
			FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AOculusCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = 
			FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AOculusCharacter::OnStartJump()
{
	bPressedJump = true;
}
void AOculusCharacter::OnStopJump()
{
	bPressedJump = false;
}

void AOculusCharacter::OnStartSpawning()
{
	//Set the simulation to Spawning state
	AProjetOculusJDFZGameMode* MyGameMode =
		Cast<AProjetOculusJDFZGameMode>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode->GetCurrentState() != 
		EOculusProjectPlayStats::ESpawningEnable){
		MyGameMode->SetCurrentState(EOculusProjectPlayStats::ESpawningEnable);
	}
	
}

void AOculusCharacter::OnReleaseSpawning()
{
	//do nothing
}

void AOculusCharacter::OnStartReset()
{
	//if not already pressed, start the timer for reset position
	if (isResetButtonPressed == false) {
		GetWorldTimerManager().SetTimer(this, 
			&AOculusCharacter::ResetCharacterPosition, 
			buttonPressedDelay, true);

		isResetButtonPressed = true;
	}
}

void AOculusCharacter::OnReleaseReset()
{
	//end the timer for reset position
	GetWorldTimerManager().ClearTimer(this, 
		&AOculusCharacter::ResetCharacterPosition);
	isResetButtonPressed = false;
}

void AOculusCharacter::setIsResetButtonPressed(bool isPressed)
{
	isResetButtonPressed = isPressed;
}

void AOculusCharacter::ResetCharacterPosition()
{

	Library* library = Library::getLibrary();
	std::list<float> initialPosition = library->getInitialPosition();
	FVector CharacterInitialPosition;
	//Extract position of the basic library type to a FVector
	if (initialPosition.size() >= 3){
		CharacterInitialPosition.X = initialPosition.front();
		std::list<float>::iterator itY = initialPosition.begin();
		std::advance(itY, 1);
		CharacterInitialPosition.Y = *itY;
		std::list<float>::iterator itZ = initialPosition.begin();
		std::advance(itZ, 2);
		//add 50.f to fall on your point, and give the editor 
		//the time to spawn your floor
		CharacterInitialPosition.Z = *itZ + 50.f;
	}
	//Teleport the character to the new position
	this->SetActorLocation(CharacterInitialPosition, false);
}