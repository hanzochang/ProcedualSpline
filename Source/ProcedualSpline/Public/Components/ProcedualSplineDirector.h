// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "ProcedualSplinePointBuilder.h"
#include "ProcedualSplineDirector.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDUALSPLINE_API UProcedualSplineDirector : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UProcedualSplinePointBuilder *ProcedualSplinePointBuilder;

public:
	void Initialize(UProcedualSplinePointBuilder *ProcedualSplinePointBuilder);
	
};