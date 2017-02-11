// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "ProcedualSplineEntity.h"
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
	void Initialize(FProcedualSplineEntity &Entity,
		            UProcedualSplinePointBuilder *ProcedualSplinePointBuilder);
	
};