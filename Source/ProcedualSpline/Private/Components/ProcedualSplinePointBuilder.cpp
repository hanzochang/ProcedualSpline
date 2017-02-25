// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplinePointBuilder.h"

void UProcedualSplinePointBuilder::AssignPointsToSpline(
	USplineComponent *Spline,
	FSpawnedSplineUnit &SpawnedSplineUnit,
	FVector &StartPoint,
	int32 &PointsIndex
)
{
	FVector PrevDirection = Spline->GetDirectionAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);
	FRotator PrevRotation  = Spline->GetRotationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);

	TArray<FVector> SplinePoints = SpawnedSplineUnit.DeriveSplinePointsAddTo(StartPoint, PrevDirection, PrevRotation);

	//PointsIndex = 0;
	for (FVector SplinePoint : SplinePoints) {
		PointsIndex += 1;
		//Spline->AddSplinePoint(SplinePoint, ESplineCoordinateSpace::Type::Local);
		Spline->AddSplinePointAtIndex(SplinePoint, PointsIndex, ESplineCoordinateSpace::Type::Local);
		SpawnedSplineUnit.PushAssignedSplineUnitPoints(Spline, PointsIndex);
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString::FromInt(PointsIndex)); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Blue, FString::FromInt(Spline->GetNumberOfSplinePoints())); }
	}
	Spline->RemoveSplinePoint(PointsIndex);

}

void DestroyPointsFromSpline(
	USplineComponent *Spline,
	FSpawnedSplineUnit &SpawnedSplineUnit
)
{
  // RemoveSplinePoint
}
