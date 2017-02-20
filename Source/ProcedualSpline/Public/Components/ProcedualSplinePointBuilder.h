// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "SplineUnit.h"
#include "SpawnedSplineUnit.h"
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
	USplineComponent* Spline;
	
public:
	//void Init(USplineComponent *Spline, TArray<FSplineUnit> &SplineUnits);
	void Initialize(FProcedualSplineEntity &Entity,
		USplineComponent *SplineComponent,
		TArray<FSplineUnit> &SplineUnits);

	//void AssignPointsToSpline(FProcedualSplineEntity &Entity, TArray<FSplineUnit> &SplineUnits);
	void AssignPointsToSpline(FProcedualSplineEntity &Entity, FSpawnedSplineUnit &SpawnedSplineUnit, FVector &StartPoint);

};