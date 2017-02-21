// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "SplineUnit.h"
#include "AssignedSplineUnitPoint.h"
#include "SpawnedSplineUnitActor.h"
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

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    TArray<FSpawnedSplineUnitActor> SpawnedSplineUnitActors;

public:
	static FSpawnedSplineUnit GenerateSpawnedSplineUnit(FSplineUnit &InSplineUnit);

public:
	void PushAssignedSplineUnitPoints(USplineComponent *Spline, int32 PointNumber);

	void PushSpawnedSplineUnitActor(AActor* SpawnedActor);

	void DeriveNextSpawnPoint();

	void Destroy();

};
