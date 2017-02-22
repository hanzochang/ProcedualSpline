// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SplineUnit.h"
#include "SpawnedSplineUnit.h"
#include "SplineUnitGenerator.h"
#include "ProcedualSplineEntity.h"
#include "ProcedualSplineDirector.h"
#include "ProcedualSplinePointBuilder.h"
#include "ProcedualSplineActorsBuilder.h"
#include "Components/SplineComponent.h"
#include "ProcedualSplineBase.generated.h"

UCLASS(Blueprintable)
class PROCEDUALSPLINE_API AProcedualSplineBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcedualSplineBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere)
	USplineComponent* Spline;

	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* StaticMesh;

	TArray<FSplineUnit> SplineUnits;
	FProcedualSplineEntity ProcedualSplineEntity;
	TArray<FSpawnedSplineUnit> SpawnedSplineUnits;

	USplineUnitGenerator* SplineUnitGenerator;

	UProcedualSplineDirector* ProcedualSplineDirector;
	UProcedualSplinePointBuilder* ProcedualSplinePointBuilder;
	UProcedualSplineActorsBuilder* ProcedualSplineActorsBuilder;
};