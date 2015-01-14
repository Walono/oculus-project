// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include <iostream> 
#include "ProceduralFaceActor.h"


AProceduralFaceActor::AProceduralFaceActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	mesh = PCIP.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("ProceduralFace"));

	// Apply a simple material directly using the VertexColor as its BaseColor input
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/BrickTumbled_Mat.BrickTumbled_Mat'"));
	// TODO Apply a real material with textures, using UVs
	//	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/M_Concrete_Poured.M_Concrete_Poured'"));
	
	mesh->SetMaterial(0, Material.Object);
	

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("creating a face"));
	
	library = Library::getLibrary();
	// Verify if there is a new face to spawn
	
	if (library->isFacesToSpawnEmpty() == false) {

		Face* newFace = library->getNextFaceToSpawn();
		std::list<std::list<float>> coordinate = newFace->getCoordinates();
		std::list<std::list<float>>::const_iterator
			lit(coordinate.begin()),
			lend(coordinate.end());
		TArray<FVector> newPoints;
		for (; lit != lend; ++lit) {

			std::list<float> point = *lit;
			float x = point.front();
			point.pop_front();
			float y = point.front();
			point.pop_front();
			float z = point.front();

			newPoints.Add(FVector(x, y, z));
		}
		TArray<FProceduralMeshTriangle> newTriangles;
		GenerateFace(newPoints, newTriangles);
		mesh->SetProceduralMeshTriangles(newTriangles);
		RootComponent = mesh;
	}
	
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

	
	//static const FColor color(255,255,255);

	//generate the triangle of the mesh for one side of the face
	for (i = 0; i < nbrPoints; ++i){
		FProceduralMeshTriangle triangle;
		//triangle.Vertex0.Color = color;
		//triangle.Vertex1.Color = color;
		//triangle.Vertex2.Color = color;
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
	//The same procedure is call on the other side to generate the mesh visible on both side
	for (i = nbrPoints - 1; i >= 0; --i){
		FProceduralMeshTriangle triangle;
		//triangle.Vertex0.Color = color;
		//triangle.Vertex1.Color = color;
		//triangle.Vertex2.Color = color;
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

