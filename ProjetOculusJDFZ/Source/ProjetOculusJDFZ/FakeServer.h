// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Library.h"



/**
 * 
 */
class PROJETOCULUSJDFZ_API FakeServer
{
public:
	FakeServer();
	~FakeServer();

	void startSendingData();

private:
	Library* library;

	void addFaceToLibrary(FVector pos, TArray<FVector> face, int texture, int id);

	void addSoundToLibrary(std::string name, FVector pos, FVector viewDirection, FVector upDirection, int id);
};
