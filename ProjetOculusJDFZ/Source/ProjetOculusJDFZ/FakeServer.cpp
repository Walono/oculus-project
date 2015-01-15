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

void FakeServer::addSoundToLibrary(std::string name, FVector pos, FVector viewDirection, FVector upDirection, int id)
{
	std::list<float> soundPosition;
	soundPosition.push_back(pos.X);
	soundPosition.push_back(pos.Y);
	soundPosition.push_back(pos.Z);

	std::vector<float> soundViewDirection;
	soundViewDirection.push_back(viewDirection.X);
	soundViewDirection.push_back(viewDirection.Y);
	soundViewDirection.push_back(viewDirection.Z);

	std::vector<float> soundUpDirection;
	soundUpDirection.push_back(upDirection.X);
	soundUpDirection.push_back(upDirection.Y);
	soundUpDirection.push_back(upDirection.Z);

	library->add_sound_source(name, soundPosition, soundViewDirection, soundUpDirection, id);
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
	addFaceToLibrary(FVector(-200.f, -200.f, 0.f), floorcoord, 1, 1);

	//outside wall
	TArray<FVector> outsideSouthCoord;
	outsideSouthCoord.Add(FVector(0.f, 0.f, 0.f));
	outsideSouthCoord.Add(FVector(0.f, 0.f, unitHigh));
	outsideSouthCoord.Add(FVector(0.f, 16 * unitWidth, unitHigh));
	outsideSouthCoord.Add(FVector(0.f, 16 * unitWidth, 0.f));
	addFaceToLibrary(FVector(0.f, 0.f, 0.f), outsideSouthCoord, 2, 2);

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

	//inner wall
	TArray<FVector>entranceSouthCoord;
	entranceSouthCoord.Add(FVector(0.f, 0.f, 0.f));
	entranceSouthCoord.Add(FVector(0.f, 0.f, unitHigh));
	entranceSouthCoord.Add(FVector(0.f, 15 * unitWidth, unitHigh));
	entranceSouthCoord.Add(FVector(0.f, 15 * unitWidth, 0.f));
	addFaceToLibrary(FVector(unitLength, 0.f, 0.f), entranceSouthCoord, 0, 8);

	TArray<FVector>entranceNorthCoord;
	entranceNorthCoord.Add(FVector(0.f, 0.f, 0.f));
	entranceNorthCoord.Add(FVector(0.f, 0.f, unitHigh));
	entranceNorthCoord.Add(FVector(0.f, 14 * unitWidth, unitHigh));
	entranceNorthCoord.Add(FVector(0.f, 14 * unitWidth, 0.f));
	addFaceToLibrary(FVector(2* unitLength, 0.f, 0.f), entranceNorthCoord, 0, 9);

	TArray<FVector>entranceNeedleCoord;
	entranceNeedleCoord.Add(FVector(0.f, 0.f, 0.f));
	entranceNeedleCoord.Add(FVector(0.f, 0.f, unitHigh));
	entranceNeedleCoord.Add(FVector(unitLength, 0.f, unitHigh));
	entranceNeedleCoord.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(2 * unitLength, 14 * unitWidth, 0.f), entranceNeedleCoord, 0, 10);

	TArray<FVector>entranceFrontCoord;
	entranceFrontCoord.Add(FVector(0.f, 0.f, 0.f));
	entranceFrontCoord.Add(FVector(0.f, 0.f, unitHigh));
	entranceFrontCoord.Add(FVector(3 * unitLength, 0.f, unitHigh));
	entranceFrontCoord.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(unitLength, 15 * unitWidth, 0.f), entranceFrontCoord, 0, 11);

	TArray<FVector>entranceEndUCoord;
	entranceEndUCoord.Add(FVector(0.f, 0.f, 0.f));
	entranceEndUCoord.Add(FVector(0.f, 0.f, unitHigh));
	entranceEndUCoord.Add(FVector(0.f, 4 * unitLength, unitHigh));
	entranceEndUCoord.Add(FVector(0.f, 4 * unitLength, 0.f));
	addFaceToLibrary(FVector(4 * unitLength, 11 * unitWidth, 0.f), entranceEndUCoord, 0, 12);

	TArray<FVector>entranceEndNeedleCoord;
	entranceEndNeedleCoord.Add(FVector(0.f, 0.f, 0.f));
	entranceEndNeedleCoord.Add(FVector(0.f, 0.f, unitHigh));
	entranceEndNeedleCoord.Add(FVector(0.f, 4 * unitLength, unitHigh));
	entranceEndNeedleCoord.Add(FVector(0.f, 4 * unitLength, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 10 * unitWidth, 0.f), entranceEndNeedleCoord, 0, 13);

	TArray<FVector>bigFloorEastCoord;
	bigFloorEastCoord.Add(FVector(0.f, 0.f, 0.f));
	bigFloorEastCoord.Add(FVector(0.f, 0.f, unitHigh));
	bigFloorEastCoord.Add(FVector(15 * unitLength, 0.f, unitHigh));
	bigFloorEastCoord.Add(FVector(15 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(4 * unitLength, 11 * unitWidth, 0.f), bigFloorEastCoord, 0, 14);

	TArray<FVector>bigFloorWestCoord;
	bigFloorWestCoord.Add(FVector(0.f, 0.f, 0.f));
	bigFloorWestCoord.Add(FVector(0.f, 0.f, unitHigh));
	bigFloorWestCoord.Add(FVector(16 * unitLength, 0.f, unitHigh));
	bigFloorWestCoord.Add(FVector(16 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 10 * unitWidth, 0.f), bigFloorWestCoord, 0, 15);

	TArray<FVector>doubleBigNeedleFirstSpikeCoord;
	doubleBigNeedleFirstSpikeCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleFirstSpikeCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleFirstSpikeCoord.Add(FVector(0.f, unitWidth, unitHigh));
	doubleBigNeedleFirstSpikeCoord.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(19 * unitLength, 11 * unitWidth, 0.f), doubleBigNeedleFirstSpikeCoord, 0, 16);

	TArray<FVector>doubleBigNeedleSecondSpikeCoord;
	doubleBigNeedleSecondSpikeCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleSecondSpikeCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleSecondSpikeCoord.Add(FVector(0.f, unitWidth, unitHigh));
	doubleBigNeedleSecondSpikeCoord.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(17 * unitLength, 13 * unitWidth, 0.f), doubleBigNeedleSecondSpikeCoord, 0, 17);

	TArray<FVector>doubleBigNeedleMiddleWestCoord;
	doubleBigNeedleMiddleWestCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleMiddleWestCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleMiddleWestCoord.Add(FVector(3 * unitLength, 0.f, unitHigh));
	doubleBigNeedleMiddleWestCoord.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(16 * unitLength, 12 * unitWidth, 0.f), doubleBigNeedleMiddleWestCoord, 0, 18);

	TArray<FVector>doubleBigNeedleMiddleEastCoord;
	doubleBigNeedleMiddleEastCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleMiddleEastCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleMiddleEastCoord.Add(FVector(3 * unitLength, 0.f, unitHigh));
	doubleBigNeedleMiddleEastCoord.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(17 * unitLength, 13 * unitWidth, 0.f), doubleBigNeedleMiddleEastCoord, 0, 19);

	TArray<FVector>doubleBigNeedleSecondEndCoord;
	doubleBigNeedleSecondEndCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleSecondEndCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleSecondEndCoord.Add(FVector(3 * unitLength, 0.f, unitHigh));
	doubleBigNeedleSecondEndCoord.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(17 * unitLength, 14 * unitWidth, 0.f), doubleBigNeedleSecondEndCoord, 0, 20);

	TArray<FVector>doubleBigNeedleWrongEndCoord;
	doubleBigNeedleWrongEndCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleWrongEndCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleWrongEndCoord.Add(FVector(0.f, unitWidth, unitHigh));
	doubleBigNeedleWrongEndCoord.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(20 * unitLength, 14 * unitWidth, 0.f), doubleBigNeedleWrongEndCoord, 0, 21);

	TArray<FVector>doubleBigNeedleBigWallCoord;
	doubleBigNeedleBigWallCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleBigWallCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleBigWallCoord.Add(FVector(0.f, 6 * unitWidth, unitHigh));
	doubleBigNeedleBigWallCoord.Add(FVector(0.f, 6 * unitWidth, 0.f));
	addFaceToLibrary(FVector(20 * unitLength, 7 * unitWidth, 0.f), doubleBigNeedleBigWallCoord, 0, 22);

	TArray<FVector>doubleBigNeedleSouthWallCoord;
	doubleBigNeedleSouthWallCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleSouthWallCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleSouthWallCoord.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	doubleBigNeedleSouthWallCoord.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(16 * unitLength, 12 * unitWidth, 0.f), doubleBigNeedleSouthWallCoord, 0, 23);

	TArray<FVector>doubleBigNeedleEasthWallCoord;
	doubleBigNeedleEasthWallCoord.Add(FVector(0.f, 0.f, 0.f));
	doubleBigNeedleEasthWallCoord.Add(FVector(0.f, 0.f, unitHigh));
	doubleBigNeedleEasthWallCoord.Add(FVector(6 * unitLength, 0.f, unitHigh));
	doubleBigNeedleEasthWallCoord.Add(FVector(6 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(14 * unitLength, 15 * unitWidth, 0.f), doubleBigNeedleEasthWallCoord, 0, 24);

	TArray<FVector>middleNorthNeedleSpikeCoord;
	middleNorthNeedleSpikeCoord.Add(FVector(0.f, 0.f, 0.f));
	middleNorthNeedleSpikeCoord.Add(FVector(0.f, 0.f, unitHigh));
	middleNorthNeedleSpikeCoord.Add(FVector(unitLength, 0.f, unitHigh));
	middleNorthNeedleSpikeCoord.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(15 * unitLength, 14 * unitWidth, 0.f), middleNorthNeedleSpikeCoord, 0, 25);

	TArray<FVector>middleNorthNeedleSouthWallCoord;
	middleNorthNeedleSouthWallCoord.Add(FVector(0.f, 0.f, 0.f));
	middleNorthNeedleSouthWallCoord.Add(FVector(0.f, 0.f, unitHigh));
	middleNorthNeedleSouthWallCoord.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	middleNorthNeedleSouthWallCoord.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(15 * unitLength, 12 * unitWidth, 0.f), middleNorthNeedleSouthWallCoord, 0, 26);

	TArray<FVector>ThreeRedCircleNorth;
	ThreeRedCircleNorth.Add(FVector(0.f, 0.f, 0.f));
	ThreeRedCircleNorth.Add(FVector(0.f, 0.f, unitHigh));
	ThreeRedCircleNorth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	ThreeRedCircleNorth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(14 * unitLength, 13 * unitWidth, 0.f), ThreeRedCircleNorth, 0, 27);

	TArray<FVector>ThreeRedCircleWest;
	ThreeRedCircleWest.Add(FVector(0.f, 0.f, 0.f));
	ThreeRedCircleWest.Add(FVector(0.f, 0.f, unitHigh));
	ThreeRedCircleWest.Add(FVector(8 * unitLength, 0.f, unitHigh));
	ThreeRedCircleWest.Add(FVector(8 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(6 * unitLength, 13 * unitWidth, 0.f), ThreeRedCircleWest, 0, 28);

	TArray<FVector>ThreeRedCircleSouth;
	ThreeRedCircleSouth.Add(FVector(0.f, 0.f, 0.f));
	ThreeRedCircleSouth.Add(FVector(0.f, 0.f, unitHigh));
	ThreeRedCircleSouth.Add(FVector(0.f, unitWidth, unitHigh));
	ThreeRedCircleSouth.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(13 * unitLength, 14 * unitWidth, 0.f), ThreeRedCircleSouth, 0, 29);

	TArray<FVector>FrontThreeRedCircleWest;
	FrontThreeRedCircleWest.Add(FVector(0.f, 0.f, 0.f));
	FrontThreeRedCircleWest.Add(FVector(0.f, 0.f, unitHigh));
	FrontThreeRedCircleWest.Add(FVector(10 * unitLength, 0.f, unitHigh));
	FrontThreeRedCircleWest.Add(FVector(10 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 12 * unitWidth, 0.f), FrontThreeRedCircleWest, 0, 30);

	TArray<FVector>middleEastWrongWayWestWall;
	middleEastWrongWayWestWall.Add(FVector(0.f, 0.f, 0.f));
	middleEastWrongWayWestWall.Add(FVector(0.f, 0.f, unitHigh));
	middleEastWrongWayWestWall.Add(FVector(7 * unitLength, 0.f, unitHigh));
	middleEastWrongWayWestWall.Add(FVector(7 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(6 * unitLength, 14 * unitWidth, 0.f), middleEastWrongWayWestWall, 0, 31);

	TArray<FVector>middleEastWrongWayEastWall;
	middleEastWrongWayEastWall.Add(FVector(0.f, 0.f, 0.f));
	middleEastWrongWayEastWall.Add(FVector(0.f, 0.f, unitHigh));
	middleEastWrongWayEastWall.Add(FVector(8 * unitLength, 0.f, unitHigh));
	middleEastWrongWayEastWall.Add(FVector(8 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 15 * unitWidth, 0.f), middleEastWrongWayEastWall, 0, 32);

	TArray<FVector>middleEastWrongWaySouthWall;
	middleEastWrongWaySouthWall.Add(FVector(0.f, 0.f, 0.f));
	middleEastWrongWaySouthWall.Add(FVector(0.f, 0.f, unitHigh));
	middleEastWrongWaySouthWall.Add(FVector(0.f, 3 * unitWidth, unitHigh));
	middleEastWrongWaySouthWall.Add(FVector(0.f, 3 * unitWidth, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 12 * unitWidth, 0.f), middleEastWrongWaySouthWall, 0, 33);

	TArray<FVector>middleEastWrongWayNeedleSpike;
	middleEastWrongWayNeedleSpike.Add(FVector(0.f, 0.f, 0.f));
	middleEastWrongWayNeedleSpike.Add(FVector(0.f, 0.f, unitHigh));
	middleEastWrongWayNeedleSpike.Add(FVector(0.f, unitWidth, unitHigh));
	middleEastWrongWayNeedleSpike.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(6 * unitLength, 13 * unitWidth, 0.f), middleEastWrongWayNeedleSpike, 0, 34);

	TArray<FVector>bigFloorLeftSouth;
	bigFloorLeftSouth.Add(FVector(0.f, 0.f, 0.f));
	bigFloorLeftSouth.Add(FVector(0.f, 0.f, unitHigh));
	bigFloorLeftSouth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	bigFloorLeftSouth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(19 * unitLength, 8 * unitWidth, 0.f), bigFloorLeftSouth, 0, 35);

	TArray<FVector>bigFloorLeftNeedleSpike;
	bigFloorLeftNeedleSpike.Add(FVector(0.f, 0.f, 0.f));
	bigFloorLeftNeedleSpike.Add(FVector(0.f, 0.f, unitHigh));
	bigFloorLeftNeedleSpike.Add(FVector(unitLength, 0.f, unitHigh));
	bigFloorLeftNeedleSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(18 * unitLength, 8 * unitWidth, 0.f), bigFloorLeftNeedleSpike, 0, 36);

	TArray<FVector>bigFloorLeftNeedleSouth;
	bigFloorLeftNeedleSouth.Add(FVector(0.f, 0.f, 0.f));
	bigFloorLeftNeedleSouth.Add(FVector(0.f, 0.f, unitHigh));
	bigFloorLeftNeedleSouth.Add(FVector(0.f, unitWidth, unitHigh));
	bigFloorLeftNeedleSouth.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(18 * unitLength, 8 * unitWidth, 0.f), bigFloorLeftNeedleSouth, 0, 37);

	TArray<FVector>bigFloorWestOposit;
	bigFloorWestOposit.Add(FVector(0.f, 0.f, 0.f));
	bigFloorWestOposit.Add(FVector(0.f, 0.f, unitHigh));
	bigFloorWestOposit.Add(FVector(13 * unitLength, 0.f, unitHigh));
	bigFloorWestOposit.Add(FVector(13 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 9 * unitWidth, 0.f), bigFloorWestOposit, 0, 38);

	TArray<FVector>midFloorSouth;
	midFloorSouth.Add(FVector(0.f, 0.f, 0.f));
	midFloorSouth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorSouth.Add(FVector(0.f, unitWidth, unitHigh));
	midFloorSouth.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 8 * unitWidth, 0.f), midFloorSouth, 0, 39);

	TArray<FVector>midFloorSouthWest;
	midFloorSouthWest.Add(FVector(0.f, 0.f, 0.f));
	midFloorSouthWest.Add(FVector(0.f, 0.f, unitHigh));
	midFloorSouthWest.Add(FVector(6 * unitLength, 0.f, unitHigh));
	midFloorSouthWest.Add(FVector(6 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 8 * unitWidth, 0.f), midFloorSouthWest, 0, 40);

	TArray<FVector>midFloorMiddle;
	midFloorMiddle.Add(FVector(0.f, 0.f, 0.f));
	midFloorMiddle.Add(FVector(0.f, 0.f, unitHigh));
	midFloorMiddle.Add(FVector(unitLength, 0.f, unitHigh));
	midFloorMiddle.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(12 * unitLength, 8 * unitWidth, 0.f), midFloorMiddle, 0, 41);

	TArray<FVector>midFloorTopBot;
	midFloorTopBot.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopBot.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopBot.Add(FVector(unitLength, 0.f, unitHigh));
	midFloorTopBot.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(14 * unitLength, 8 * unitWidth, 0.f), midFloorTopBot, 0, 42);

	TArray<FVector>midFloorTopTop;
	midFloorTopTop.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopTop.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopTop.Add(FVector(unitLength, 0.f, unitHigh));
	midFloorTopTop.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(16 * unitLength, 8 * unitWidth, 0.f), midFloorTopTop, 0, 43);

	TArray<FVector>midFloorTopTopWest;
	midFloorTopTopWest.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopTopWest.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopTopWest.Add(FVector(3 * unitLength, 0.f, unitHigh));
	midFloorTopTopWest.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(17 * unitLength, 7 * unitWidth, 0.f), midFloorTopTopWest, 0, 44);

	TArray<FVector>midFloorTopBotWest;
	midFloorTopBotWest.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopBotWest.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopBotWest.Add(FVector(unitLength, 0.f, unitHigh));
	midFloorTopBotWest.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(15 * unitLength, 7 * unitWidth, 0.f), midFloorTopBotWest, 0, 45);

	TArray<FVector>midFloorTopTopSouth;
	midFloorTopTopSouth.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopTopSouth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopTopSouth.Add(FVector(0.f, unitWidth, unitHigh));
	midFloorTopTopSouth.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(16 * unitLength, 7 * unitWidth, 0.f), midFloorTopTopSouth, 0, 46);

	TArray<FVector>midFloorTopTopNorth;
	midFloorTopTopNorth.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopTopNorth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopTopNorth.Add(FVector(0.f, unitWidth, unitHigh));
	midFloorTopTopNorth.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(17 * unitLength, 7 * unitWidth, 0.f), midFloorTopTopNorth, 0, 47);

	TArray<FVector>midFloorTopBotNorth;
	midFloorTopBotNorth.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopBotNorth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopBotNorth.Add(FVector(0.f, unitWidth, unitHigh));
	midFloorTopBotNorth.Add(FVector(0.f, unitWidth, 0.f));
	addFaceToLibrary(FVector(15 * unitLength, 7 * unitWidth, 0.f), midFloorTopBotNorth, 0, 48);

	TArray<FVector>midFloorTopBotSouth;
	midFloorTopBotSouth.Add(FVector(0.f, 0.f, 0.f));
	midFloorTopBotSouth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorTopBotSouth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	midFloorTopBotSouth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(14 * unitLength, 6 * unitWidth, 0.f), midFloorTopBotSouth, 0, 49);

	TArray<FVector>midFloorMiddleNorth;
	midFloorMiddleNorth.Add(FVector(0.f, 0.f, 0.f));
	midFloorMiddleNorth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorMiddleNorth.Add(FVector(0.f, 3 * unitWidth, unitHigh));
	midFloorMiddleNorth.Add(FVector(0.f, 3 * unitWidth, 0.f));
	addFaceToLibrary(FVector(13 * unitLength, 5 * unitWidth, 0.f), midFloorMiddleNorth, 0, 50);

	TArray<FVector>midFloorMiddleSouth;
	midFloorMiddleSouth.Add(FVector(0.f, 0.f, 0.f));
	midFloorMiddleSouth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorMiddleSouth.Add(FVector(0.f, 4 * unitWidth, unitHigh));
	midFloorMiddleSouth.Add(FVector(0.f, 4 * unitWidth, 0.f));
	addFaceToLibrary(FVector(12 * unitLength, 4 * unitWidth, 0.f), midFloorMiddleSouth, 0, 51);

	TArray<FVector>midFloorMiddleFrontSouth;
	midFloorMiddleFrontSouth.Add(FVector(0.f, 0.f, 0.f));
	midFloorMiddleFrontSouth.Add(FVector(0.f, 0.f, unitHigh));
	midFloorMiddleFrontSouth.Add(FVector(0.f, 6 * unitWidth, unitHigh));
	midFloorMiddleFrontSouth.Add(FVector(0.f, 6 * unitWidth, 0.f));
	addFaceToLibrary(FVector(11 * unitLength, 2 * unitWidth, 0.f), midFloorMiddleFrontSouth, 0, 52);

	TArray<FVector>midFloorMiddleFrontSouthOposit;
	midFloorMiddleFrontSouthOposit.Add(FVector(0.f, 0.f, 0.f));
	midFloorMiddleFrontSouthOposit.Add(FVector(0.f, 0.f, unitHigh));
	midFloorMiddleFrontSouthOposit.Add(FVector(0.f, 5 * unitWidth, unitHigh));
	midFloorMiddleFrontSouthOposit.Add(FVector(0.f, 5 * unitWidth, 0.f));
	addFaceToLibrary(FVector(10 * unitLength, 2 * unitWidth, 0.f), midFloorMiddleFrontSouthOposit, 0, 53);

	TArray<FVector>midSouthWrongWayNorth;
	midSouthWrongWayNorth.Add(FVector(0.f, 0.f, 0.f));
	midSouthWrongWayNorth.Add(FVector(0.f, 0.f, unitHigh));
	midSouthWrongWayNorth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	midSouthWrongWayNorth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(4 * unitLength, 7 * unitWidth, 0.f), midSouthWrongWayNorth, 0, 54);

	TArray<FVector>midSouthWrongWaySouth;
	midSouthWrongWaySouth.Add(FVector(0.f, 0.f, 0.f));
	midSouthWrongWaySouth.Add(FVector(0.f, 0.f, unitHigh));
	midSouthWrongWaySouth.Add(FVector(0.f, 3 * unitWidth, unitHigh));
	midSouthWrongWaySouth.Add(FVector(0.f, 3 * unitWidth, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 6 * unitWidth, 0.f), midSouthWrongWaySouth, 0, 55);

	TArray<FVector>midSouthWrongWayEast;
	midSouthWrongWayEast.Add(FVector(0.f, 0.f, 0.f));
	midSouthWrongWayEast.Add(FVector(0.f, 0.f, unitHigh));
	midSouthWrongWayEast.Add(FVector(unitLength, 0.f, unitHigh));
	midSouthWrongWayEast.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 9 * unitWidth, 0.f), midSouthWrongWayEast, 0, 56);

	TArray<FVector>beforMidSouthWrongWayWest;
	beforMidSouthWrongWayWest.Add(FVector(0.f, 0.f, 0.f));
	beforMidSouthWrongWayWest.Add(FVector(0.f, 0.f, unitHigh));
	beforMidSouthWrongWayWest.Add(FVector(6 * unitLength, 0.f, unitHigh));
	beforMidSouthWrongWayWest.Add(FVector(6 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 6 * unitWidth, 0.f), beforMidSouthWrongWayWest, 0, 57);
	
	TArray<FVector>beforMidSouthWrongWayEast;
	beforMidSouthWrongWayEast.Add(FVector(0.f, 0.f, 0.f));
	beforMidSouthWrongWayEast.Add(FVector(0.f, 0.f, unitHigh));
	beforMidSouthWrongWayEast.Add(FVector(6 * unitLength, 0.f, unitHigh));
	beforMidSouthWrongWayEast.Add(FVector(6 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(4 * unitLength, 7 * unitWidth, 0.f), beforMidSouthWrongWayEast, 0, 58);

	TArray<FVector>fiveNeedleFirstSpike;
	fiveNeedleFirstSpike.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFirstSpike.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFirstSpike.Add(FVector(unitLength, 0.f, unitHigh));
	fiveNeedleFirstSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(12 * unitLength, 3 * unitWidth, 0.f), fiveNeedleFirstSpike, 0, 59);

	TArray<FVector>fiveNeedleFirstSpikeOposit;
	fiveNeedleFirstSpikeOposit.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFirstSpikeOposit.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFirstSpikeOposit.Add(FVector(2 * unitLength, 0.f, unitHigh));
	fiveNeedleFirstSpikeOposit.Add(FVector(2 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(12 * unitLength, 4 * unitWidth, 0.f), fiveNeedleFirstSpikeOposit, 0, 60);

	TArray<FVector>fiveNeedleSecondSpike;
	fiveNeedleSecondSpike.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleSecondSpike.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleSecondSpike.Add(FVector(unitLength, 0.f, unitHigh));
	fiveNeedleSecondSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(10 * unitLength, 2 * unitWidth, 0.f), fiveNeedleSecondSpike, 0, 61);

	TArray<FVector>fiveNeedleThirdSpike;
	fiveNeedleThirdSpike.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleThirdSpike.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleThirdSpike.Add(FVector(unitLength, 0.f, unitHigh));
	fiveNeedleThirdSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(8 * unitLength, 2 * unitWidth, 0.f), fiveNeedleThirdSpike, 0, 62);

	TArray<FVector>fiveNeedleFourthSpike;
	fiveNeedleFourthSpike.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFourthSpike.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFourthSpike.Add(FVector(unitLength, 0.f, unitHigh));
	fiveNeedleFourthSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(6 * unitLength, 2 * unitWidth, 0.f), fiveNeedleFourthSpike, 0, 63);

	TArray<FVector>fiveNeedleFivethSpike;
	fiveNeedleFivethSpike.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFivethSpike.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFivethSpike.Add(FVector(unitLength, 0.f, unitHigh));
	fiveNeedleFivethSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(4 * unitLength, 3 * unitWidth, 0.f), fiveNeedleFivethSpike, 0, 64);

	TArray<FVector>fiveNeedleFivethSpikeWest;
	fiveNeedleFivethSpikeWest.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFivethSpikeWest.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFivethSpikeWest.Add(FVector(unitLength, 0.f, unitHigh));
	fiveNeedleFivethSpikeWest.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 1 * unitWidth, 0.f), fiveNeedleFivethSpikeWest, 0, 65);

	TArray<FVector>fiveNeedleFirstthSpikeWest;
	fiveNeedleFirstthSpikeWest.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFirstthSpikeWest.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFirstthSpikeWest.Add(FVector(7 * unitLength, 0.f, unitHigh));
	fiveNeedleFirstthSpikeWest.Add(FVector(7 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 1 * unitWidth, 0.f), fiveNeedleFirstthSpikeWest, 0, 66);

	TArray<FVector>fiveNeedleFivethSpikeOposit;
	fiveNeedleFivethSpikeOposit.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFivethSpikeOposit.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFivethSpikeOposit.Add(FVector(3 * unitLength, 0.f, unitHigh));
	fiveNeedleFivethSpikeOposit.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 5 * unitWidth, 0.f), fiveNeedleFivethSpikeOposit, 0, 67);

	TArray<FVector>fiveNeedleThirdSpikeEast;
	fiveNeedleThirdSpikeEast.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleThirdSpikeEast.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleThirdSpikeEast.Add(FVector(unitLength, 0.f, unitHigh));
	fiveNeedleThirdSpikeEast.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(7 * unitLength, 5 * unitWidth, 0.f), fiveNeedleThirdSpikeEast, 0, 68);

	TArray<FVector>fiveNeedleFivethSouth;
	fiveNeedleFivethSouth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFivethSouth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFivethSouth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	fiveNeedleFivethSouth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(4 * unitLength, 1 * unitWidth, 0.f), fiveNeedleFivethSouth, 0, 69);

	TArray<FVector>fiveNeedleFivethSouthOposit;
	fiveNeedleFivethSouthOposit.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFivethSouthOposit.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFivethSouthOposit.Add(FVector(0.f, 4 * unitWidth, unitHigh));
	fiveNeedleFivethSouthOposit.Add(FVector(0.f, 4 * unitWidth, 0.f));
	addFaceToLibrary(FVector(3 * unitLength, 1 * unitWidth, 0.f), fiveNeedleFivethSouthOposit, 0, 70);

	TArray<FVector>fiveNeedleFourthSouth;
	fiveNeedleFourthSouth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFourthSouth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFourthSouth.Add(FVector(0.f, 3 * unitWidth, unitHigh));
	fiveNeedleFourthSouth.Add(FVector(0.f, 3 * unitWidth, 0.f));
	addFaceToLibrary(FVector(6 * unitLength, 2 * unitWidth, 0.f), fiveNeedleFourthSouth, 0, 71);

	TArray<FVector>fiveNeedleFourthNorth;
	fiveNeedleFourthNorth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFourthNorth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFourthNorth.Add(FVector(0.f, 3 * unitWidth, unitHigh));
	fiveNeedleFourthNorth.Add(FVector(0.f, 3 * unitWidth, 0.f));
	addFaceToLibrary(FVector(7 * unitLength, 2 * unitWidth, 0.f), fiveNeedleFourthNorth, 0, 72);

	TArray<FVector>fiveNeedleThirdSouth;
	fiveNeedleThirdSouth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleThirdSouth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleThirdSouth.Add(FVector(0.f, 3 * unitWidth, unitHigh));
	fiveNeedleThirdSouth.Add(FVector(0.f, 3 * unitWidth, 0.f));
	addFaceToLibrary(FVector(8 * unitLength, 2 * unitWidth, 0.f), fiveNeedleThirdSouth, 0, 73);

	TArray<FVector>fiveNeedleThirdNorth;
	fiveNeedleThirdNorth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleThirdNorth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleThirdNorth.Add(FVector(0.f, 4 * unitWidth, unitHigh));
	fiveNeedleThirdNorth.Add(FVector(0.f, 4 * unitWidth, 0.f));
	addFaceToLibrary(FVector(9 * unitLength, 2 * unitWidth, 0.f), fiveNeedleThirdNorth, 0, 74);

	TArray<FVector>fiveNeedleFirstSouth;
	fiveNeedleFirstSouth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFirstSouth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFirstSouth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	fiveNeedleFirstSouth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(12 * unitLength, 1 * unitWidth, 0.f), fiveNeedleFirstSouth, 0, 75);

	TArray<FVector>fiveNeedleFirstNorth;
	fiveNeedleFirstNorth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFirstNorth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFirstNorth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	fiveNeedleFirstNorth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(13 * unitLength, 1 * unitWidth, 0.f), fiveNeedleFirstNorth, 0, 76);

	TArray<FVector>fiveNeedleFirstNorthOposit;
	fiveNeedleFirstNorthOposit.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFirstNorthOposit.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFirstNorthOposit.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	fiveNeedleFirstNorthOposit.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(14 * unitLength, 2 * unitWidth, 0.f), fiveNeedleFirstNorthOposit, 0, 77);

	TArray<FVector>lastLWest;
	lastLWest.Add(FVector(0.f, 0.f, 0.f));
	lastLWest.Add(FVector(0.f, 0.f, unitHigh));
	lastLWest.Add(FVector(9 * unitLength, 0.f, unitHigh));
	lastLWest.Add(FVector(9 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(13 * unitLength, 1 * unitWidth, 0.f), lastLWest, 0, 78);

	TArray<FVector>lastLEast;
	lastLEast.Add(FVector(0.f, 0.f, 0.f));
	lastLEast.Add(FVector(0.f, 0.f, unitHigh));
	lastLEast.Add(FVector(7 * unitLength, 0.f, unitHigh));
	lastLEast.Add(FVector(7 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(14 * unitLength, 2 * unitWidth, 0.f), lastLEast, 0, 79);

	TArray<FVector>lastLNorth;
	lastLNorth.Add(FVector(0.f, 0.f, 0.f));
	lastLNorth.Add(FVector(0.f, 0.f, unitHigh));
	lastLNorth.Add(FVector(0.f, 15 * unitWidth, unitHigh));
	lastLNorth.Add(FVector(0.f, 15 * unitWidth, 0.f));
	addFaceToLibrary(FVector(22 * unitLength, 1 * unitWidth, 0.f), lastLNorth, 0, 80);

	TArray<FVector>lastLSouth;
	lastLSouth.Add(FVector(0.f, 0.f, 0.f));
	lastLSouth.Add(FVector(0.f, 0.f, unitHigh));
	lastLSouth.Add(FVector(0.f, 14 * unitWidth, unitHigh));
	lastLSouth.Add(FVector(0.f, 14 * unitWidth, 0.f));
	addFaceToLibrary(FVector(21 * unitLength, 2 * unitWidth, 0.f), lastLSouth, 0, 81);

	TArray<FVector>fiveNeedleFivethNorth;
	fiveNeedleFivethNorth.Add(FVector(0.f, 0.f, 0.f));
	fiveNeedleFivethNorth.Add(FVector(0.f, 0.f, unitHigh));
	fiveNeedleFivethNorth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	fiveNeedleFivethNorth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(5 * unitLength, 1 * unitWidth, 0.f), fiveNeedleFivethNorth, 0, 82);

	TArray<FVector>twoNeedleNorthWestEndWest;
	twoNeedleNorthWestEndWest.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestEndWest.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestEndWest.Add(FVector(unitLength, 0.f, unitHigh));
	twoNeedleNorthWestEndWest.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(19 * unitLength, 3 * unitWidth, 0.f), twoNeedleNorthWestEndWest, 0, 83);

	TArray<FVector>twoNeedleNorthWestEndWestOposit;
	twoNeedleNorthWestEndWestOposit.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestEndWestOposit.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestEndWestOposit.Add(FVector(3 * unitLength, 0.f, unitHigh));
	twoNeedleNorthWestEndWestOposit.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(17 * unitLength, 6 * unitWidth, 0.f), twoNeedleNorthWestEndWestOposit, 0, 84);

	TArray<FVector>twoNeedleNorthWestFirstNeedleSpike;
	twoNeedleNorthWestFirstNeedleSpike.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestFirstNeedleSpike.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestFirstNeedleSpike.Add(FVector(unitLength, 0.f, unitHigh));
	twoNeedleNorthWestFirstNeedleSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(18 * unitLength, 5 * unitWidth, 0.f), twoNeedleNorthWestFirstNeedleSpike, 0, 85);

	TArray<FVector>twoNeedleNorthWestSecondNeedleSpike;
	twoNeedleNorthWestSecondNeedleSpike.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestSecondNeedleSpike.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestSecondNeedleSpike.Add(FVector(unitLength, 0.f, unitHigh));
	twoNeedleNorthWestSecondNeedleSpike.Add(FVector(unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(16 * unitLength, 4 * unitWidth, 0.f), twoNeedleNorthWestSecondNeedleSpike, 0, 86);

	TArray<FVector>twoNeedleNorthWestSecondNeedleSpikeOposit;
	twoNeedleNorthWestSecondNeedleSpikeOposit.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestSecondNeedleSpikeOposit.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestSecondNeedleSpikeOposit.Add(FVector(3 * unitLength, 0.f, unitHigh));
	twoNeedleNorthWestSecondNeedleSpikeOposit.Add(FVector(3 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(15 * unitLength, 3 * unitWidth, 0.f), twoNeedleNorthWestSecondNeedleSpikeOposit, 0, 87);

	TArray<FVector>twoNeedleNorthWestEntranceWest;
	twoNeedleNorthWestEntranceWest.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestEntranceWest.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestEntranceWest.Add(FVector(2 * unitLength, 0.f, unitHigh));
	twoNeedleNorthWestEntranceWest.Add(FVector(2 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(13 * unitLength, 5 * unitWidth, 0.f), twoNeedleNorthWestEntranceWest, 0, 88);

	TArray<FVector>twoNeedleNorthWestEntranceWestOposit;
	twoNeedleNorthWestEntranceWestOposit.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestEntranceWestOposit.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestEntranceWestOposit.Add(FVector(2 * unitLength, 0.f, unitHigh));
	twoNeedleNorthWestEntranceWestOposit.Add(FVector(2 * unitLength, 0.f, 0.f));
	addFaceToLibrary(FVector(14 * unitLength, 6 * unitWidth, 0.f), twoNeedleNorthWestEntranceWestOposit, 0, 89);

	TArray<FVector>twoNeedleNorthWestSecondNeedleSouth;
	twoNeedleNorthWestSecondNeedleSouth.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestSecondNeedleSouth.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestSecondNeedleSouth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	twoNeedleNorthWestSecondNeedleSouth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(16 * unitLength, 4 * unitWidth, 0.f), twoNeedleNorthWestSecondNeedleSouth, 0, 90);

	TArray<FVector>twoNeedleNorthWestSecondNeedleNorth;
	twoNeedleNorthWestSecondNeedleNorth.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestSecondNeedleNorth.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestSecondNeedleNorth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	twoNeedleNorthWestSecondNeedleNorth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(17 * unitLength, 4 * unitWidth, 0.f), twoNeedleNorthWestSecondNeedleNorth, 0, 91);

	TArray<FVector>twoNeedleNorthWestFirstNeedleSouth;
	twoNeedleNorthWestFirstNeedleSouth.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestFirstNeedleSouth.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestFirstNeedleSouth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	twoNeedleNorthWestFirstNeedleSouth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(18 * unitLength, 3 * unitWidth, 0.f), twoNeedleNorthWestFirstNeedleSouth, 0, 92);

	TArray<FVector>twoNeedleNorthWestFirstNeedleNorth;
	twoNeedleNorthWestFirstNeedleNorth.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestFirstNeedleNorth.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestFirstNeedleNorth.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	twoNeedleNorthWestFirstNeedleNorth.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(19 * unitLength, 3 * unitWidth, 0.f), twoNeedleNorthWestFirstNeedleNorth, 0, 93);

	TArray<FVector>twoNeedleNorthWestFirstNeedleNorthOposit;
	twoNeedleNorthWestFirstNeedleNorthOposit.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestFirstNeedleNorthOposit.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestFirstNeedleNorthOposit.Add(FVector(0.f, 3 * unitWidth, unitHigh));
	twoNeedleNorthWestFirstNeedleNorthOposit.Add(FVector(0.f, 3 * unitWidth, 0.f));
	addFaceToLibrary(FVector(20 * unitLength, 3 * unitWidth, 0.f), twoNeedleNorthWestFirstNeedleNorthOposit, 0, 94);

	TArray<FVector>twoNeedleNorthWestSecondNeedleSouthOposit;
	twoNeedleNorthWestSecondNeedleSouthOposit.Add(FVector(0.f, 0.f, 0.f));
	twoNeedleNorthWestSecondNeedleSouthOposit.Add(FVector(0.f, 0.f, unitHigh));
	twoNeedleNorthWestSecondNeedleSouthOposit.Add(FVector(0.f, 2 * unitWidth, unitHigh));
	twoNeedleNorthWestSecondNeedleSouthOposit.Add(FVector(0.f, 2 * unitWidth, 0.f));
	addFaceToLibrary(FVector(15 * unitLength, 3 * unitWidth, 0.f), twoNeedleNorthWestSecondNeedleSouthOposit, 0, 95);

	//add sound

	addSoundToLibrary("Sound1", FVector(1 * unitLength + 150.f, 14 * unitWidth + 250.f, 100.f), FVector(0.f, -1.f, 0.f), FVector(0.f, 0.f, 1.f), 1);
	addSoundToLibrary("Sound1", FVector(19 * unitLength + 250.f, 14 * unitWidth + 150.f, 100.f), FVector(-2.f, -1.f, 0.f), FVector(0.f, 0.f, 1.f), 2);
	addSoundToLibrary("Sound1", FVector(18 * unitLength + 50.f, 7 * unitWidth + 150.f, 100.f), FVector(0.f, 2.f, 0.f), FVector(0.f, 0.f, 1.f), 3);
}