// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineBase.h"


// Sets default values
AProcedualSplineBase::AProcedualSplineBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<UStaticMeshComponent>(FName("SM")));
    Spline = CreateDefaultSubobject<USplineComponent>(FName("Spline"));
	Spline->SetupAttachment(StaticMesh);

    ProcedualSplineDirector = CreateDefaultSubobject<UProcedualSplineDirector>(FName("SplineDirector"));
    ProcedualSplinePointBuilder = CreateDefaultSubobject<UProcedualSplinePointBuilder>(FName("SplinePointBuilder"));

	Init();
}

void AProcedualSplineBase::Init()
{
	SplineUnits = SplineUnitGenerator->GenerateSplineUnits("splinetest.json");
	ProcedualSplineDirector->Initialize(ProcedualSplinePointBuilder);
}

// Called when the game starts or when spawned
void AProcedualSplineBase::BeginPlay()
{
	Super::BeginPlay();
	
}