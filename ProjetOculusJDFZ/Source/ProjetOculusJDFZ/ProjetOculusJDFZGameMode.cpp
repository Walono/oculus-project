// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProjetOculusJDFZGameMode.h"
#include "Engine.h"


AProjetOculusJDFZGameMode::AProjetOculusJDFZGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DefaultPawnClass = AOculusCharacter::StaticClass();
}

void AProjetOculusJDFZGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}


