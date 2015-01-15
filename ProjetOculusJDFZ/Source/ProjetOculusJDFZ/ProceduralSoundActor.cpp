// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProceduralSoundActor.h"


AProceduralSoundActor::AProceduralSoundActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	mesh = PCIP.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("ProceduralSound"));

	// Apply a simple material directly using the VertexColor as its BaseColor input
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/BaseColor.BaseColor'"));
	// TODO find a way to realy display it
	mesh->SetMaterial(0, Material.Object);

	// The array of triangles who will build all faces
	TArray<FProceduralMeshTriangle> triangles;

	// Hard coded polyline for a speacker
	TArray<FVector> points;
	points.Add(FVector(25, 0, 0));
	points.Add(FVector(19, 13, 0));
	points.Add(FVector(38, 50, 0));
	points.Add(FVector(25, 50, 0));
	points.Add(FVector(7, 13, 0));
	points.Add(FVector(0, 13, 0));	

	// Build the triangle Array, send it to the generator and attach it to the Actor
	GenerateLathe(points, 256, triangles);
	mesh->SetProceduralMeshTriangles(triangles);
	RootComponent = mesh;

	// Create a audio for our mesh and give it a sound
	AudioComp = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Object sound"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Sound(TEXT("SoundWave'/Game/Audio/blu.blu'"));
	AudioComp->SetSound(Sound.Object);
	AudioComp->AttachParent = RootComponent;
	// Give the sound a cone attenuation
	AudioComp->bOverrideAttenuation = true;
	AudioComp->AttenuationOverrides.AttenuationShape = EAttenuationShape::Cone;
	AudioComp->AttenuationOverrides.DistanceAlgorithm = ESoundDistanceModel::ATTENUATION_Linear;
	AudioComp->AttenuationOverrides.ConeOffset = 450.f;
	AudioComp->AttenuationOverrides.FalloffDistance = 4000.f;
	/* The dimensions to use for the attenuation shape. Interpretation of the values differ per shape.
	Sphere  - X is Sphere Radius. Y and Z are unused
	Capsule - X is Capsule Half Height, Y is Capsule Radius, Z is unused
	Box     - X, Y, and Z are the Box's dimensions
	Cone    - X is Cone Radius, Y is Cone Angle, Z is Cone Falloff Angle
	*/
	AudioComp->AttenuationOverrides.AttenuationShapeExtents = FVector(1500.f, 15.f, 45.f);
	AudioComp->Play();
	
}


void AProceduralSoundActor::GenerateLathe(const TArray<FVector>& InPoints, const int InSegments, TArray<FProceduralMeshTriangle>& OutTriangles)
{
	// precompute some trig
	float angle = FMath::DegreesToRadians(360.0f / InSegments);
	float sinA = FMath::Sin(angle);
	float cosA = FMath::Cos(angle);

	/*
	This implementation is rotation around the X Axis, other formulas below

	Z Axis Rotation
	x' = x*cos q - y*sin q
	y' = x*sin q + y*cos q
	z' = z

	X Axis Rotation
	y' = y*cos q - z*sin q
	z' = y*sin q + z*cos q
	x' = x

	Y Axis Rotation
	z' = z*cos q - x*sin q
	x' = z*sin q + x*cos q
	y' = y
	*/

	// Working point array, in which we keep the rotated line we draw with
	TArray<FVector> wp;
	for (int i = 0; i < InPoints.Num(); i++)
	{
		wp.Add(InPoints[i]);
	}

	// Add a first and last point on the axis to complete the OutTriangles
	FVector p0(wp[0].X, 0, 0);
	FVector pLast(wp[wp.Num() - 1].X, 0, 0);

	FProceduralMeshTriangle tri;
	// for each segment draw the OutTriangles clockwise for normals pointing out or counterclockwise for the opposite (this here does CW)
	for (int segment = 0; segment<InSegments; segment++)
	{

		for (int i = 0; i<InPoints.Num() - 1; i++)
		{
			FVector p1 = wp[i];
			FVector p2 = wp[i + 1];
			FVector p1r(p1.X, p1.Y*cosA - p1.Z*sinA, p1.Y*sinA + p1.Z*cosA);
			FVector p2r(p2.X, p2.Y*cosA - p2.Z*sinA, p2.Y*sinA + p2.Z*cosA);

			static const FColor Red(255, 0, 0);
			tri.Vertex0.Color = Red;
			tri.Vertex1.Color = Red;
			tri.Vertex2.Color = Red;

			if (i == 0)
			{
				tri.Vertex0.Position = p1;
				tri.Vertex1.Position = p0;
				tri.Vertex2.Position = p1r;
				OutTriangles.Add(tri);
			}

			tri.Vertex0.Position = p1;
			tri.Vertex1.Position = p1r;
			tri.Vertex2.Position = p2;
			OutTriangles.Add(tri);

			tri.Vertex0.Position = p2;
			tri.Vertex1.Position = p1r;
			tri.Vertex2.Position = p2r;
			OutTriangles.Add(tri);

			if (i == InPoints.Num() - 2)
			{
				tri.Vertex0.Position = p2;
				tri.Vertex1.Position = p2r;
				tri.Vertex2.Position = pLast;
				OutTriangles.Add(tri);
				wp[i + 1] = p2r;
			}

			wp[i] = p1r;
		}
	}
}

void AProceduralSoundActor::IOActorSound(bool isActive)
{
	if (isActive) {
		AudioComp->Play();
	}
	else {
		AudioComp->Stop();
	}
}