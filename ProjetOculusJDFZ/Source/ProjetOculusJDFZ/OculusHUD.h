// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "OculusHUD.generated.h"

/**
*	Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
*	OculusHUD
*	Purpose: create a heads-up display to give the user some information on screen
*
*  @author Julie Djeffal & Fabien Zellweger
*/
UCLASS()
class PROJETOCULUSJDFZ_API AOculusHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/** Variable for storing the font, the "graphics" of what we will write */
	UPROPERTY()
	UFont* HUDFont;
	
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;


};
