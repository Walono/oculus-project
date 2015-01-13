// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "Library.h"
#include "FakeServer.h"

FakeServer::FakeServer()
{
	library = Library::getLibrary();
}

FakeServer::~FakeServer()
{
}

void FakeServer::startSendingData()
{
	//The basic unit for our maze
	float unitHigh = 500.0f;
	float unitWidth = 300.0f;
	float unitLength = 300.0f;

	//set init pos
	std::list<float> initPos;
	initPos.push_back(unitWidth + 150.f);
	initPos.push_back(unitLength);
	initPos.push_back(0.f);
	library->set_initial_position(initPos);

	//Base floor
	TArray<FVector> floorcoord;
	floorcoord.Add(FVector(0.f, 0.f, 0.f));
	floorcoord.Add(FVector((23 * unitLength) + 400.f, 0.f, 0.f));
	floorcoord.Add(FVector((23 * unitLength) + 400.f, (16 * unitWidth) + 400.f, 0.f));
	floorcoord.Add(FVector(0.f, (16 * unitWidth) + 400.f, 0.f));

	addFaceToLibrary(FVector pos, TArray<FVector> face, int texture, int id)
}

void FakeServer::addFaceToLibrary(FVector pos, TArray<FVector> face, int texture, int id)
{
	std::list<float> facePosition;
	facePosition.push_back(pos.X);
	facePosition.push_back(pos.Y);
	facePosition.push_back(pos.Z);

	std::list<std::list<float>> faceCoordinates;
	for (int i = 0; i < face.Num(); ++i) {
		std::list<float> coordinate;
		coordinate.push_back(face[i].X);
		coordinate.push_back(face[i].Y);
		coordinate.push_back(face[i].Z);
		faceCoordinates.push_back(coordinate);
	}

	library->add_face(facePosition, faceCoordinates, texture, id);
}