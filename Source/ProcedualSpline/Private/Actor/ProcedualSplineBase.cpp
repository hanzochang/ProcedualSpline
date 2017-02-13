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
	SplineUnits = SplineUnitGenerator->GenerateSplineUnits("splinetest.json");

	static ConstructorHelpers::FObjectFinder<UBlueprint> DebugGridClassFinder( TEXT( "Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'" ) );
	if (DebugGridClassFinder.Succeeded())
	{
		WhatToSpawn = (UClass*)DebugGridClassFinder.Object->GeneratedClass;
	}

	Init();
}

void AProcedualSplineBase::Init()
{
}

// Called when the game starts or when spawned
void AProcedualSplineBase::BeginPlay()
{
	Super::BeginPlay();
	//ProcedualSplineDirector->Initialize(ProcedualSplineEntity, ProcedualSplinePointBuilder);
	ProcedualSplinePointBuilder->Initialize(ProcedualSplineEntity, Spline, SplineUnits);
	ProcedualSplineActorsBuilder->Initialize(Spline);

	for (auto i = 0; i < Spline->GetNumberOfSplinePoints(); i++) {
		ProcedualSplineActorsBuilder->SetDebugGridsEachSplinePoints(WhatToSpawn, i);
	}

}