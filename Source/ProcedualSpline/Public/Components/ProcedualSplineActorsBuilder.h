// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	void Initialize();
	void LoadDebugGrid();
	void SetDebugGridsEachSplinePoints(TSubclassOf<class AActor> WhatToSpawn, int PointNum);
	
};
