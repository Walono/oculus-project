// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProceduralFaceActor.h"


AProceduralFaceActor::AProceduralFaceActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	mesh = PCIP.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("ProceduralFace"));

	// Apply a simple material directly using the VertexColor as its BaseColor input
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/BaseColor.BaseColor'"));
	// TODO Apply a real material with textures, using UVs
	//	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/M_Concrete_Poured.M_Concrete_Poured'"));
	mesh->SetMaterial(0, Material.Object);

	//The array of triangles who will build all faces
	TArray<FProceduralMeshTriangle> triangles;
	float startPoint = 0.f;
	float vectorLength = 300.f;

	// Define and generate face 0
	TArray<FVector> face0;
	face0.Add(FVector(startPoint, startPoint, startPoint));
	face0.Add(FVector(startPoint, startPoint + vectorLength, startPoint));
	face0.Add(FVector(startPoint, startPoint + vectorLength, startPoint + vectorLength));
	face0.Add(FVector(startPoint, startPoint, startPoint + vectorLength));
	GenerateFace(face0, triangles);

	// Define and generate face 1
	TArray<FVector> face1;
	face1.Add(FVector(startPoint, startPoint, startPoint));
	face1.Add(FVector(startPoint - vectorLength, startPoint, startPoint));
	face1.Add(FVector(startPoint - vectorLength, startPoint + vectorLength, startPoint));
	face1.Add(FVector(startPoint, startPoint + vectorLength, startPoint));
	GenerateFace(face1, triangles);

	// Define and generate face 2
	TArray<FVector> face2;
	face2.Add(FVector(startPoint, startPoint, startPoint));
	face2.Add(FVector(startPoint - vectorLength, startPoint, startPoint));
	face2.Add(FVector(startPoint - vectorLength, startPoint, startPoint + vectorLength));
	face2.Add(FVector(startPoint, startPoint, startPoint + vectorLength));
	GenerateFace(face2, triangles);

	// Define and generate face 3
	TArray<FVector> face3;
	face3.Add(FVector(startPoint - vectorLength, startPoint, startPoint));
	face3.Add(FVector(startPoint - vectorLength, startPoint + vectorLength, startPoint));
	face3.Add(FVector(startPoint - vectorLength, startPoint + vectorLength, startPoint + vectorLength));
	face3.Add(FVector(startPoint - vectorLength, startPoint, startPoint + vectorLength));
	GenerateFace(face3, triangles);

	// Define and generate face 4
	TArray<FVector> face4;
	face4.Add(FVector(startPoint, startPoint + vectorLength, startPoint));
	face4.Add(FVector(startPoint - vectorLength, startPoint + vectorLength, startPoint));
	face4.Add(FVector(startPoint - vectorLength, startPoint + vectorLength, startPoint + vectorLength));
	face4.Add(FVector(startPoint, startPoint + vectorLength, startPoint + vectorLength));
	GenerateFace(face4, triangles);

	// Define and generate face 5
	TArray<FVector> face5;
	face5.Add(FVector(startPoint, startPoint, startPoint + vectorLength));
	face5.Add(FVector(startPoint, startPoint + vectorLength, startPoint + vectorLength));
	face5.Add(FVector(startPoint - vectorLength, startPoint + vectorLength, startPoint + vectorLength));
	face5.Add(FVector(startPoint - vectorLength, startPoint, startPoint + vectorLength));
	GenerateFace(face5, triangles);

	//Create the object
	mesh->SetProceduralMeshTriangles(triangles);
	RootComponent = mesh;
}

void AProceduralFaceActor::GenerateFace(const TArray<FVector>& InPoints, TArray<FProceduralMeshTriangle>& OutTriangles){

	//Creat the midle point
	float middleXPos = 0;
	float middleYPos = 0;
	float middleZPos = 0;
	int nbrPoints;
	int i ;
	for (i = 0; i < InPoints.Num(); ++i) {
		middleXPos += InPoints[i][0];
		middleYPos += InPoints[i][1];
		middleZPos += InPoints[i][2];
	}
	nbrPoints = i;
	middleXPos = middleXPos / nbrPoints;
	middleYPos = middleYPos / nbrPoints;
	middleZPos = middleZPos / nbrPoints;

	static const FColor RandomColor(FMath::FRandRange(0, 255), FMath::FRandRange(0, 255), FMath::FRandRange(0, 255));
	for (i = 0; i < nbrPoints; ++i){
		FProceduralMeshTriangle triangle;
		triangle.Vertex0.Color = RandomColor;
		triangle.Vertex1.Color = RandomColor;
		triangle.Vertex2.Color = RandomColor;
		triangle.Vertex0.Position.Set(InPoints[i][0], InPoints[i][1], InPoints[i][2]);
		if (i == nbrPoints - 1) {
			triangle.Vertex1.Position.Set(InPoints[0][0], InPoints[0][1], InPoints[0][2]);
		}
		else {
			triangle.Vertex1.Position.Set(InPoints[i + 1][0], InPoints[i + 1][1], InPoints[i + 1][2]);
		}
		triangle.Vertex2.Position.Set(middleXPos, middleYPos, middleZPos);

		OutTriangles.Add(triangle);
	}

	for (i = nbrPoints - 1; i >= 0; --i){
		FProceduralMeshTriangle triangle;
		triangle.Vertex0.Color = RandomColor;
		triangle.Vertex1.Color = RandomColor;
		triangle.Vertex2.Color = RandomColor;
		triangle.Vertex0.Position.Set(InPoints[i][0], InPoints[i][1], InPoints[i][2]);
		if (i == 0) {
			triangle.Vertex1.Position.Set(InPoints[nbrPoints - 1][0], InPoints[nbrPoints - 1][1], InPoints[nbrPoints - 1][2]);
		}
		else {
			triangle.Vertex1.Position.Set(InPoints[i - 1][0], InPoints[i - 1][1], InPoints[i - 1][2]);
		}
		triangle.Vertex2.Position.Set(middleXPos, middleYPos, middleZPos);

		OutTriangles.Add(triangle);
	}
}



