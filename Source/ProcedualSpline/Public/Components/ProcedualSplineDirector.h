// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "Components/SplineComponent.h"
#include "SplineUnit.h"
#include "ProcedualSplineEntity.h"
#include "ProcedualSplinePointBuilder.h"
#include "ProcedualSplineActorsBuilder.h"
#include "ProcedualSplineDirector.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDUALSPLINE_API UProcedualSplineDirector : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	USplineComponent *Spline;
	TArray<FSplineUnit> SplineUnits;
	TArray<FSpawnedSplineUnit> SpawnedSplineUnits;
	FProcedualSplineEntity Entity;
	UProcedualSplinePointBuilder *ProcedualSplinePointBuilder;
	UProcedualSplineActorsBuilder *ProcedualSplineActorsBuilder;

	AActor *Owner;

public:
	void Initialize(
		USplineComponent *Spline,
		TArray<FSplineUnit> &SplineUnits,
		TArray<FSpawnedSplineUnit> &SpawnedSplineUnits,
		FProcedualSplineEntity &Entity,
		UProcedualSplinePointBuilder *InProcedualSplinePointBuilder,
		UProcedualSplineActorsBuilder *InProcedualSplineActorsBuilder
	);

	void CreateInitialSpline(
		//TArray<FSplineUnit> &SplineUnits,
	);

	void CheckProcedualSplineEntity(FProcedualSplineEntity &Entity, float CurrentLength);

private:
	void RefreshEntityParameters();

};