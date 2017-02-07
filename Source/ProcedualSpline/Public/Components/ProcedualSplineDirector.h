// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SplineUnit.h"
#include "ProcedualSplineInstanceBuilder.h"
#include "ProcedualSplinePointBuilder.h"
#include "Components/SplineComponent.h"
#include "ProcedualSplineDirector.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDUALSPLINE_API UProcedualSplineDirector : public UActorComponent
{
	GENERATED_BODY()

public:	
	UProcedualSplineDirector();

	void Init(USplineComponent *Spline, TArray<FSplineUnit> &SplineUnits,
		UProcedualSplineInstanceBuilder *ProcedualSplineInstanceBuilder,
		UProcedualSplinePointBuilder *ProcedualSplinePointBuilder);
};
