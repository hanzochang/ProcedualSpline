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

	float DeletedSplineLengthsDiff;

	bool Refreshable;

public:
	void Initialize(
		USplineComponent *InSpline,
		TArray<FSplineUnit> &InSplineUnits,
		TArray<FSpawnedSplineUnit> &InSpawnedSplineUnits,
		float &InDeletedSplineLengthsDiff,
		FProcedualSplineEntity &InEntity,
		UProcedualSplinePointBuilder *InProcedualSplinePointBuilder,
		UProcedualSplineActorsBuilder *InProcedualSplineActorsBuilder
	);

	void CreateInitialSpline();

	void CheckProcedualSplineEntity(float CurrentLength);

private:
	void GenerateNextSpawnedSplineUnit();

	void RefreshEntityParameters();

	void DeleteFirstSpawnedSplineUnit();

	void UProcedualSplineDirector::UpdateSpline();

};