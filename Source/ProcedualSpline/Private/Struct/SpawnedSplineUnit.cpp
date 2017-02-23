// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "SpawnedSplineUnit.h"

FSpawnedSplineUnit FSpawnedSplineUnit::GenerateSpawnedSplineUnit(FSplineUnit &InSplineUnit)
{
	FSpawnedSplineUnit SpawnedSplineUnit;
	SpawnedSplineUnit.SplineUnit = InSplineUnit;

	return SpawnedSplineUnit;

}

void FSpawnedSplineUnit::PushAssignedSplineUnitPoints(USplineComponent *Spline, int32 PointNumber)
{
    AssignedSplineUnitPoints.Push(FAssignedSplineUnitPoint::GenerateAssignedSplineUnitPoint(Spline, PointNumber));
}

void FSpawnedSplineUnit::PushSpawnedSplineUnitActor(AActor* SpawnedActor)
{
    SpawnedSplineUnitActors.Push(FSpawnedSplineUnitActor::Generate(SpawnedActor));

}

void FSpawnedSplineUnit::DeriveNextSpawnPoint(FSpawnedSplineUnit &SpawnedSplineUnit)
{
	FVector FirstPoint = AssignedSplineUnitPoints[0].Location;
	if (SpawnedSplineUnit.AssignedSplineUnitPoints.Num() > 0)
	{ 
		FAssignedSplineUnitPoint PrevAssignedSplineUnitPoint = SpawnedSplineUnit.AssignedSplineUnitPoints.Last();
		FVector PrevLocation = PrevAssignedSplineUnitPoint.Location;
		FRotator PrevRotation = PrevAssignedSplineUnitPoint.Rotation;
		NextSpawnPoint = SplineUnit.DeriveNextSplineUnitStartPoint(FirstPoint, PrevLocation, PrevRotation);
	}
	else {
		FVector PrevLocation = FVector{ 0,0,0 };
		FRotator PrevRotation = FRotator{ 0,0,0 };
		NextSpawnPoint = SplineUnit.DeriveNextSplineUnitStartPoint(FirstPoint, PrevLocation, PrevRotation);
	}
}

void FSpawnedSplineUnit::Destroy()
{
	
	for (FSpawnedSplineUnitActor SpawnedSplineUnitActor : SpawnedSplineUnitActors)
	{
		SpawnedSplineUnitActor.Destroy();
	}

}
