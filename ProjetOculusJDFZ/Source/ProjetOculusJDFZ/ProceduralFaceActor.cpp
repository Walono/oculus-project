// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProceduralFaceActor.h"


AProceduralFaceActor::AProceduralFaceActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	mesh = PCIP.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("ProceduralCube"));

	// Apply a simple material directly using the VertexColor as its BaseColor input
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/BaseColor.BaseColor'"));
	// TODO Apply a real material with textures, using UVs
	//	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/M_Concrete_Poured.M_Concrete_Poured'"));
	mesh->SetMaterial(0, Material.Object);

	// Contains factice presentation points of our face
	TArray<FVector> points;
	float startPoint = 0;
	points.Add(FVector(startPoint, -startPoint, (startPoint / 2)));
	points.Add(FVector(startPoint, -startPoint + 60.f, (startPoint / 2)));
	points.Add(FVector(startPoint + 80.f, -startPoint + 120.f, (startPoint / 2) + 60.f));
	points.Add(FVector(startPoint + 160.f, -startPoint + 60.f, (startPoint / 2) + 120.f));
	points.Add(FVector(startPoint + 160.f, -startPoint, (startPoint / 2) + 120.f));
	points.Add(FVector(startPoint + 80.f, -startPoint - 60.f, (startPoint / 2) + 60.f));
	//TODO need to find a way to obtain this magic number

	// Generate a face
	TArray<FProceduralMeshTriangle> triangles;
	GenerateFace(points, triangles);
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

	static const FColor Green(96, 169, 23);
	for (i = 0; i < nbrPoints; ++i){
		FProceduralMeshTriangle triangle;
		triangle.Vertex0.Color = Green;
		triangle.Vertex1.Color = Green;
		triangle.Vertex2.Color = Green;
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
		triangle.Vertex0.Color = Green;
		triangle.Vertex1.Color = Green;
		triangle.Vertex2.Color = Green;
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



