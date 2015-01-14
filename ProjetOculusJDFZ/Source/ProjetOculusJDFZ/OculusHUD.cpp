// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "OculusHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "OculusCharacter.h"
#include "ProjetOculusJDFZGameMode.h"
#include "Kismet/GameplayStatics.h"


AOculusHUD::AOculusHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Use the RobotoDistanceField font from the engine
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;
}

void AOculusHUD::DrawHUD()
{
	//Get the screen dimensions
	FVector2D ScreenDimension = FVector2D(Canvas->SizeX, Canvas->SizeY);

	//Call to the parent versions of DrawHUD
	Super::DrawHUD();

	//Only write the introduction message on the GameMode's inizialize state
	AProjetOculusJDFZGameMode* MyGameMode = Cast<AProjetOculusJDFZGameMode>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode->GetCurrentState() == EOculusProjectPlayStats::EInitialization)
	{
		FString InstructionString = TEXT("Hello, press X button/front left button/Enter to start the simulation");
		//create a variable for storing the size of printing our instruction
		FVector2D instructionSize;
		GetTextSize(InstructionString, instructionSize.X, instructionSize.Y, HUDFont);
		DrawText(InstructionString, FColor::Yellow, (ScreenDimension.X - instructionSize.X) / 2.0f, (ScreenDimension.Y - instructionSize.Y) / 2.0f, HUDFont);
	}
}


