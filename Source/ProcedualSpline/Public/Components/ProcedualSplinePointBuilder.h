// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "SplineUnit.h"
#include "ProcedualSplineEntity.h"
#include "Components/SplineComponent.h"
#include "ProcedualSplinePointBuilder.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDUALSPLINE_API UProcedualSplinePointBuilder : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:
	//void Init(USplineComponent *Spline, TArray<FSplineUnit> &SplineUnits);
	void Initialize(FProcedualSplineEntity &Entity,
		USplineComponent *Spline,
		TArray<FSplineUnit> &SplineUnits);

	void AssignSplinePointsFromSplineUnit(USplineComponent *Spline,
		TArray<FVector> &SplinePoints,
		TArray<FSplineUnit> &SplineUnits);

private:

	void AssignSplinePoints(USplineComponent *Spline,
		TArray<FVector> &SplinePoints,
		TArray<FSplineUnit> &SplineUnits,
		int32 counter,
		FVector &StartPoint
	);

	float GetCurrentSplineUnitLength(
		USplineComponent *Spline,
		int32 PointStartNumber,
		int32 PointEndNumber
	);

	float GetGeneratedSplineLength(
		FProcedualSplineEntity &Entity,
		USplineComponent *Spline,
		int32 EdgeSplineUnitStartSplineNum
	);

	void SetDisplayableSplineUnitLength(FProcedualSplineEntity &Entity);

};