// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "OculusHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOCULUSJDFZ_API AOculusHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/** Variable for storing the font */
	UPROPERTY()
	UFont* HUDFont;
	
	/** Promary draw call for the HUD */
	virtual void DrawHUD() override;


};
