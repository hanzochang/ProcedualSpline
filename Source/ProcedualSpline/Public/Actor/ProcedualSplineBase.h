// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SplineUnit.h"
#include "SplineUnitGenerator.h"
#include "ProcedualSplineDirector.h"
#include "ProcedualSplineInstanceBuilder.h"
#include "ProcedualSplinePointBuilder.h"
#include "Components/SplineComponent.h"
#include "ProcedualSplineBase.generated.h"

UCLASS(Blueprintable)
class PROCEDUALSPLINE_API AProcedualSplineBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProcedualSplineBase();

	virtual void BeginPlay() override;

	void Init();

	UPROPERTY(VisibleAnyWhere)
	USplineComponent* Spline;

	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnyWhere)
	TArray<FSplineUnit> SplineUnits;

	UPROPERTY(VisibleAnyWhere)
	USplineUnitGenerator* SplineUnitGenerator;

	UPROPERTY(VisibleAnyWhere)
	UProcedualSplineDirector* ProcedualSplineDirector = NewObject<UProcedualSplineDirector>();
	//UProcedualSplineDirector* ProcedualSplineDirector;

	UPROPERTY(VisibleAnyWhere)
	UProcedualSplineInstanceBuilder* ProcedualSplineInstanceBuilder = NewObject<UProcedualSplineInstanceBuilder>();
	//UProcedualSplineInstanceBuilder* ProcedualSplineInstanceBuilder;

	UPROPERTY(VisibleAnyWhere)
	UProcedualSplinePointBuilder* ProcedualSplinePointBuilder = NewObject<UProcedualSplinePointBuilder>();
	//UProcedualSplinePointBuilder* ProcedualSplinePointBuilder;
};