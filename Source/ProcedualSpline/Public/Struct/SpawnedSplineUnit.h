// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "SplineUnit.h"
#include "AssignedSplineUnitPoint.h"
#include "SpawnedSplineUnit.generated.h"

USTRUCT(BlueprintType)
struct FSpawnedSplineUnit
{
	GENERATED_BODY()

public:
	FSplineUnit SplineUnit;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	FVector NextSpawnPoint;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    TArray<FAssignedSplineUnitPoint> AssignedSplineUnitPoints;

public:
	static FSpawnedSplineUnit GenerateSpawnedSplineUnit(FSplineUnit &InSplineUnit);

public:
	void PushAssignedSplineUnitPoints(USplineComponent *Spline, int32 PointNumber);
	void FSpawnedSplineUnit::DeriveNextSpawnPoint();

};
