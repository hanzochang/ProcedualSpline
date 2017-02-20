// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SplineUnit.h"
#include "SpawnedSplineUnit.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SplineComponent.h"
#include "ProcedualSplineActorsBuilder.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDUALSPLINE_API UProcedualSplineActorsBuilder : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, Category = General)
    //TSubclassOf<class AActor> WhatToSpawn;

	AActor* Owner;
	USplineComponent* Spline;

public:
	void Initialize(USplineComponent* OwnerSpline);
	void SpawnActors(FSpawnedSplineUnit &SpawnedSplineUnit);
};