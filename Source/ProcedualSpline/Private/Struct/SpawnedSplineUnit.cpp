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

void FSpawnedSplineUnit::DeriveNextSpawnPoint()
{
	FAssignedSplineUnitPoint LastAssignedSplineUnitPoint = AssignedSplineUnitPoints.Last();
	FVector FirstPoint = AssignedSplineUnitPoints[0].Location;
	NextSpawnPoint = SplineUnit.DeriveNextSplineUnitStartPoint(FirstPoint, LastAssignedSplineUnitPoint.Location, LastAssignedSplineUnitPoint.Rotation);
}
