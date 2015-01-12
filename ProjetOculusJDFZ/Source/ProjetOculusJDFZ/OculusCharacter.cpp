// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "OculusCharacter.h"
#include "ProjetOculusJDFZGameMode.h"
#include "Kismet/GameplayStatics.h"


AOculusCharacter::AOculusCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AOculusCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AOculusCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AOculusCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AOculusCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AOculusCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AOculusCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AOculusCharacter::OnStopJump);
	InputComponent->BindAction("StartSpawning", IE_Pressed, this, &AOculusCharacter::OnStartSpawning);
	InputComponent->BindAction("StartSpawning", IE_Released, this, &AOculusCharacter::OnReleaseSpawning);
}

void AOculusCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AOculusCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
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
//Set the simulation to Spawning state
void AOculusCharacter::OnStartSpawning()
{
	AProjetOculusJDFZGameMode* MyGameMode = Cast<AProjetOculusJDFZGameMode>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode->GetCurrentState() != EOculusProjectPlayStats::ESpawningEnable){
		MyGameMode->SetCurrentState(EOculusProjectPlayStats::ESpawningEnable);
	}
	
}

void AOculusCharacter::OnReleaseSpawning()
{
	//do nothing
}