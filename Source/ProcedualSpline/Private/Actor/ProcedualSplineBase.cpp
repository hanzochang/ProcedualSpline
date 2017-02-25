// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineBase.h"


// Sets default values
AProcedualSplineBase::AProcedualSplineBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<UStaticMeshComponent>(FName("SM")));

    Spline = CreateDefaultSubobject<USplineComponent>(FName("Spline"));
	Spline->SetupAttachment(StaticMesh);

    ProcedualSplineDirector = CreateDefaultSubobject<UProcedualSplineDirector>(FName("SplineDirector"));
    ProcedualSplinePointBuilder = CreateDefaultSubobject<UProcedualSplinePointBuilder>(FName("SplinePointBuilder"));
    ProcedualSplineActorsBuilder = CreateDefaultSubobject<UProcedualSplineActorsBuilder>(FName("SplineActorsBuilder"));
	ProcedualSplineEntity = FProcedualSplineEntity(2);

	SplineUnits = SplineUnitGenerator->GenerateSplineUnits("splinetest2.json");
}

// Called when the game starts or when spawned
void AProcedualSplineBase::BeginPlay()
{
	Super::BeginPlay();
	ProcedualSplineDirector->Initialize(Spline, &SplineUnits, &ProcedualSplineEntity, ProcedualSplinePointBuilder, ProcedualSplineActorsBuilder);
	ProcedualSplineDirector->CreateInitialSpline(SplineUnits, SpawnedSplineUnits);
}

FVector AProcedualSplineBase ::GetCurrentLocationAlongSpline(float distance)
{
	return Spline->GetWorldLocationAtDistanceAlongSpline(distance);
}

FVector AProcedualSplineBase::GetCurrentDirectionAlongSpline(float distance)
{
	return Spline->GetWorldDirectionAtDistanceAlongSpline(distance);
}

FRotator AProcedualSplineBase::GetCurrentRotationAlongSpline(float distance)
{
	return Spline->GetWorldRotationAtDistanceAlongSpline(distance);
}