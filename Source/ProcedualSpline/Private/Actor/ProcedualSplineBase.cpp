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

	DeletedSplineLengthsDiff = 0;

	SplineUnits = SplineUnitGenerator->GenerateSplineUnits("splinetest2.json");
}

// Called when the game starts or when spawned
void AProcedualSplineBase::BeginPlay()
{
	Super::BeginPlay();
	ProcedualSplineDirector->Initialize(
		Spline,
		SplineUnits,
		SpawnedSplineUnits,
		DeletedSplineLengthsDiff,
		ProcedualSplineEntity,
		ProcedualSplinePointBuilder,
		ProcedualSplineActorsBuilder
	);

	ProcedualSplineDirector->CreateInitialSpline();
}

void AProcedualSplineBase::WatchSplineLifeCycle(float CurrentLength)
{
	ProcedualSplineDirector->CheckProcedualSplineEntity(CurrentLength);
}

FVector AProcedualSplineBase ::GetCurrentLocationAlongSpline(float distance)
{
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::SanitizeFloat(ProcedualSplineDirector->DeletedSplineLengthsDiff)); }
	return Spline->GetWorldLocationAtDistanceAlongSpline(distance - ProcedualSplineDirector->DeletedSplineLengthsDiff);
}

FVector AProcedualSplineBase::GetCurrentDirectionAlongSpline(float distance)
{
	return Spline->GetWorldDirectionAtDistanceAlongSpline(distance - ProcedualSplineDirector->DeletedSplineLengthsDiff);
}

FRotator AProcedualSplineBase::GetCurrentRotationAlongSpline(float distance)
{
	return Spline->GetWorldRotationAtDistanceAlongSpline(distance - ProcedualSplineDirector->DeletedSplineLengthsDiff);
}