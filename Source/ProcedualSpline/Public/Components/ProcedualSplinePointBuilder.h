// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "SplineUnit.h"
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
	void Init();
	
};