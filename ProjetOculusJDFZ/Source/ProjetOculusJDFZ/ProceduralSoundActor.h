// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralSoundActor.generated.h"

/**
*	Bachelor Project: Development and Implementation of 
*    an Oculus Rift Frontend for Audio-Visual VR Applications
*	ProceduralSoundActor
*	Purpose: create a speacker that produce sound
*
*  @author Julie Djeffal & Fabien Zellweger
*/
UCLASS()
class PROJETOCULUSJDFZ_API AProceduralSoundActor : public AActor
{
	GENERATED_UCLASS_BODY()

public:
<<<<<<< HEAD
	// Allow viewing/changing the Material ot the procedural 
	// Mesh in editor (if placed in a level at construction)
=======
	/** The visual and physical entity of the Actor*/
>>>>>>> 6dc8f40f518fdfcc7f32e55f232c2529f34794ae
	UPROPERTY(VisibleAnywhere, Category = Materials)
	TSubobjectPtr<UProceduralMeshComponent> mesh;
	/** The sound component we can manipulate with attenuation,... */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AudioComponent)
	TSubobjectPtr <UAudioComponent> AudioComp;
	/** start or stop the sound
	@param: isActive: play or stop it
	*/
	UFUNCTION()
	void IOActorSound(bool isActive);

private: 

	/** Produce a revolution mesh
	*	@param InPoints: The point of a polyline we will rotate to have
	*          the revolution object
	*	@param InSegments: How many iteration for the rotation. Higher 
	*          it is less you see the face
	*	@param OutTriangles: The array which contains all 
	*          the triangles of the mesh of the Actor,
	*		it will be send to the generator at the end of the constructor
	*/
	void GenerateLathe(const TArray<FVector>& InPoints, const int InSegments, 
	TArray<FProceduralMeshTriangle>& OutTriangles);
};