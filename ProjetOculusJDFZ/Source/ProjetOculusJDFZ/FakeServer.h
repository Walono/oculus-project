// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Library.h"



/**
 * Bachelor Project: Development and Implementation of an Oculus Rift Frontend
 *		for Audio-Visual VR Applications
 *  FakeServer
 *  Purpose: Class that simule what the server could send to the library,
 *		useful for the demo because there isn't any server now.
 *
 *  @author Julie Djeffal & Fabien Zellweger
*/

class PROJETOCULUSJDFZ_API FakeServer
{
public:
	/**	Constructor called in the gamemode with BeginPlay(). */
	FakeServer();
	~FakeServer();

	/** Called in the GameMode, simule a flux of data send by the server. */
	void startSendingData();

private:

	Library* library;
	/**	Convert the Unreal type to the general type used in the Interface and
		send the face to the Library. */
	void addFaceToLibrary(FVector pos, TArray<FVector> face, int texture,
		int id);
	/** Convert the Unreal type to the general type used in the Interface and
		send the sound to the Library. */
	void addSoundToLibrary(std::string name, FVector pos, FVector viewDirection,
		FVector upDirection, int id);
};
