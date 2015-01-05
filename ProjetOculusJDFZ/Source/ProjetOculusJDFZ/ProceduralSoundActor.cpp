// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ProceduralSoundActor.h"


AProceduralSoundActor::AProceduralSoundActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	mesh = PCIP.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("ProceduralSound"));

	// Apply a simple material directly using the VertexColor as its BaseColor input
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/BaseColor.BaseColor'"));
	// TODO Apply a real material with textures, using UVs
	//	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/Materials/M_Concrete_Poured.M_Concrete_Poured'"));
	mesh->SetMaterial(0, Material.Object);

	//Create a audio for our mesh
	AudioComp = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Object sound"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Sound(TEXT("SoundWave'/Game/Audio/short_audio.short_audio'"));

	//The array of triangles who will build all faces
	TArray<FProceduralMeshTriangle> triangles;

	// Contains the points describing the polyline we are going to rotate
	TArray<FVector> points;

	points.Add(FVector(100, 0, 0));
	points.Add(FVector(75, 50, 0));
	points.Add(FVector(150, 200, 0));
	points.Add(FVector(100, 200, 0));
	points.Add(FVector(25, 50, 0));
	points.Add(FVector(0, 50, 0));

	

	GenerateLathe(points, 256, triangles);
	mesh->SetProceduralMeshTriangles(triangles);
	RootComponent = mesh;

	AudioComp->SetSound(Sound.Object);
	AudioComp->AttachParent = RootComponent;
	AudioComp->bOverrideAttenuation = true;
	AudioComp->AttenuationOverrides.AttenuationShape = EAttenuationShape::Cone;
	AudioComp->AttenuationOverrides.DistanceAlgorithm = ESoundDistanceModel::ATTENUATION_Linear;
	AudioComp->AttenuationOverrides.ConeOffset = 0.f;
	AudioComp->AttenuationOverrides.FalloffDistance = 1.f;
	AudioComp->AttenuationOverrides.AttenuationShapeExtents = FVector(1000.f, 45.f, 1.f);
	AudioComp->Play();
	
}


	void AProceduralSoundActor::GenerateLathe(const TArray<FVector>& InPoints, const int InSegments, TArray<FProceduralMeshTriangle>& OutTriangles)
{
		
			UE_LOG(LogClass, Log, TEXT("AProceduralLatheActor::Lathe POINTS %d"), InPoints.Num());

			TArray<FVector> verts;

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