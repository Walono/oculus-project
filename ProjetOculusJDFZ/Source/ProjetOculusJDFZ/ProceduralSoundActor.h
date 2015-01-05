// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralSoundActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJETOCULUSJDFZ_API AProceduralSoundActor : public AActor
{
	GENERATED_UCLASS_BODY()

	// Allow viewing/changing the Material ot the procedural Mesh in editor (if placed in a level at construction)
	UPROPERTY(VisibleAnywhere, Category = Materials)
	TSubobjectPtr<UProceduralMeshComponent> mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AudioComponent)
	TSubobjectPtr <UAudioComponent> AudioComp;

	void GenerateLathe(const TArray<FVector>& InPoints, const int InSegments, TArray<FProceduralMeshTriangle>& OutTriangles);
};