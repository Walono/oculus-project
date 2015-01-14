// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Library.h"
#include "ProceduralFaceActor.generated.h"

/**
*	Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
*	ProceduralFaceActor
*	Purpose: create a face or a set of face we can spawn in the world
*
*  @author Julie Djeffal & Fabien Zellweger
*/
UCLASS()
class PROJETOCULUSJDFZ_API AProceduralFaceActor : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	/** The visual and physical entity of the Actor*/
	UPROPERTY(VisibleAnywhere, Category = Materials)
	TSubobjectPtr<UProceduralMeshComponent> mesh;

	
private:

	Library * library;
	/** Take a face, and cut it to generate the triangle for the triangle mesh
	*	@param InPoints: all the Vertex of a face
	*	@param OutTriangles: The array which contains all the triangles of the mesh of the Actor,
	*		it will be send to the generator at the end of the constructor
	*/
	void GenerateFace(const TArray<FVector>& InPoints, TArray<FProceduralMeshTriangle>& OutTriangles);
	
};
