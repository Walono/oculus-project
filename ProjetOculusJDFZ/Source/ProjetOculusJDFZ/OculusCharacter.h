// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "OculusCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOCULUSJDFZ_API AOculusCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	//handles moving forward/backward
	UFUNCTION()
	void MoveForward(float Val);
	//handles strafing
	UFUNCTION()
	void MoveRight(float Val);

	//sets jump flag when key is pressed
	UFUNCTION()
	void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
	void OnStopJump();

	//set the state in gamemode to ESpawningEnable
	UFUNCTION()
	void OnStartSpawning();
	//do nothing
	UFUNCTION()
	void OnReleaseSpawning();

	//Start the reset timer
	UFUNCTION()
	void OnStartReset();
	//Verify if the reset timer reach the delay
	UFUNCTION()
	void OnReleaseReset();

	void setIsResetButtonPressed(bool isPressed);

	// called by the timer or the spawnVolume to reset the character position
	void ResetCharacterPosition();

private:

	//used to check how many time a button is pressed
	bool isResetButtonPressed;
	float buttonPressedDelay;


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
