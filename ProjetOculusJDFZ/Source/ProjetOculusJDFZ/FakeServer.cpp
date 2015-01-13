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
	addFaceToLibrary(FVector(-200.f, -200.f, 0.f), floorcoord, 0, 1);

	//outside face
	TArray<FVector> outsideSouthCoord;
	outsideSouthCoord.Add(FVector(0.f, 0.f, 0.f));
	outsideSouthCoord.Add(FVector(0.f, 0.f, unitHigh));
	outsideSouthCoord.Add(FVector(0.f, 16 * unitWidth, unitHigh));
	outsideSouthCoord.Add(FVector(0.f, 16 * unitWidth, 0.f));
	addFaceToLibrary(FVector(0.f, 0.f, 0.f), outsideSouthCoord, 0, 2);

	TArray<FVector> outsideEastCoord;
	outsideEastCoord.Add(FVector(0.f, 0.f, 0.f));
	outsideEastCoord.Add(FVector(0.f, 0.f, unitHigh));
	outsideEastCoord.Add(FVector(21 * unitLength, 0.f, unitHigh));
	outsideEastCoord.Add(FVector(21 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(0.f, 16 * unitWidth, 0.f), outsideEastCoord, 0, 3);

	TArray<FVector> littleOutsideEastCoord;
	littleOutsideEastCoord.Add(FVector(0.f, 0.f, 0.f));
	littleOutsideEastCoord.Add(FVector(0.f, 0.f, unitHigh));
	littleOutsideEastCoord.Add(FVector(unitLength, 0.f, unitHigh));
	littleOutsideEastCoord.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(22 * unitLength, 16 * unitWidth, 0.f), littleOutsideEastCoord, 0, 4);

	TArray<FVector>outsideNorthCoord;
	outsideNorthCoord.Add(FVector(0.f, 0.f, 0.f));
	outsideNorthCoord.Add(FVector(0.f, 0.f, unitHigh));
	outsideNorthCoord.Add(FVector(0.f, 16 * unitWidth, unitHigh));
	outsideNorthCoord.Add(FVector(0.f, 16 * unitWidth, 0.f));
	addFaceToLibrary(FVector(23 * unitLength, 0.f, 0.f), outsideNorthCoord, 0, 5);

	TArray<FVector>littleOutsidWestCoord;
	littleOutsidWestCoord.Add(FVector(0.f, 0.f, 0.f));
	littleOutsidWestCoord.Add(FVector(0.f, 0.f, unitHigh));
	littleOutsidWestCoord.Add(FVector(unitLength, 0.f, unitHigh));
	littleOutsidWestCoord.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(0.f, 0.f, 0.f), littleOutsidWestCoord, 0, 6);

	TArray<FVector>outsidWestCoord;
	outsidWestCoord.Add(FVector(0.f, 0.f, 0.f));
	outsidWestCoord.Add(FVector(0.f, 0.f, unitHigh));
	outsidWestCoord.Add(FVector(21 * unitLength, 0.f, unitHigh));
	outsidWestCoord.Add(FVector(21 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(2 * unitLength, 0.f, 0.f), outsidWestCoord, 0, 7);


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