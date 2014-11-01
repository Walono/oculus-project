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

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
