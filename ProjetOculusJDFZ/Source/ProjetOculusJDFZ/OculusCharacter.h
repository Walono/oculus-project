// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "OculusCharacter.generated.h"

/**
*	Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
*	OculusCharacter
*	Purpose: The class that allows the interpretation of user actions with the game pad, mouse, 
*		keyboard, and the oculus. Provided also the severity and way of moving
*
*  @author Julie Djeffal & Fabien Zellweger
*/
UCLASS()
class PROJETOCULUSJDFZ_API AOculusCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** handles moving forward/backward
	*	@param Val: determined by the engine, by exemple if you use a stick, if you're at max,
	*	or juste on middle of the stick
	*/
	UFUNCTION()
	void MoveForward(float Val);
	/** handles moving on sides
	*	@param Val: determined by the engine, by exemple if you use a stick, if you're at max,
	*	or juste on middle of the stick
	*/
	UFUNCTION()
	void MoveRight(float Val);

	/** jump already defin in mother class, it just set flags */
	UFUNCTION()
	void OnStartJump();
	/** jump already defin in mother class, it just clear flags when key is released*/
	UFUNCTION()
	void OnStopJump();

	/** set the state in gamemode to ESpawningEnable */
	UFUNCTION()
	void OnStartSpawning();
	/** do nothing */
	UFUNCTION()
	void OnReleaseSpawning();

	/** Start the reset timer */
	UFUNCTION()
	void OnStartReset();
	/** end the reset timer if it didn't reach its time */
	UFUNCTION()
	void OnReleaseReset();
	/** set the controller
	*	@param isPressed will set isResetButtonPressed*/
	void setIsResetButtonPressed(bool isPressed);

	/** called by the timer or the spawnVolume to reset the character position */
	void ResetCharacterPosition();

private:

	/** used to check how many time the reset button is pressed */
	bool isResetButtonPressed;
	/** define a delay for the timer */
	float buttonPressedDelay;


protected:
	/** contains all input set in the editor and the associated function 
	*	@param InputComponent an input used by the user*/
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
