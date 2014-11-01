// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "OculusCharacter.h"
#include "ProjetOculusJDFZGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOCULUSJDFZ_API AProjetOculusJDFZGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

		virtual void BeginPlay() override;
	
	
};
