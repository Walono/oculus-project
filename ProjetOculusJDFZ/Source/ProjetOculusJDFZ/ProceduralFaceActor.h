// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Library.h"
#include "ProceduralFaceActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOCULUSJDFZ_API AProceduralFaceActor : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	// Allow viewing/changing the Material ot the procedural Mesh in editor (if placed in a level at construction)
	UPROPERTY(VisibleAnywhere, Category = Materials)
	TSubobjectPtr<UProceduralMeshComponent> mesh;

	
private:

	Library * library;

	void GenerateFace(const TArray<FVector>& InPoints, TArray<FProceduralMeshTriangle>& OutTriangles);
	
};
