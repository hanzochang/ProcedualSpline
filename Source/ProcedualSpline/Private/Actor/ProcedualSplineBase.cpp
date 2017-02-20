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
	ProcedualSplineEntity = FProcedualSplineEntity(40);
	SplineUnits = SplineUnitGenerator->GenerateSplineUnits("splinetest2.json");

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

	// ここはDirectorが実行する

	int32 counter = 0;
	int32 TopmostSplineNumber = 0;
	TArray<FVector> AssignedSplinePoints;
	TArray<FSpawnedSplineUnit> SpawnedSplineUnits;

	FVector StartPoint = FVector{ 0,0,0 }; //これはガン、SplineStructのほうにいれる

	for (int32 i = 0; i < ProcedualSplineEntity.DisplayableSplineUnitSum(); i++)
	{
		TopmostSplineNumber = Spline->GetNumberOfSplinePoints();
		counter = i % SplineUnits.Num();

		FSplineUnit SplineUnit = SplineUnits[counter];
		FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		ProcedualSplinePointBuilder->AssignPointsToSpline(ProcedualSplineEntity, SpawnedSplineUnit, StartPoint);

		// 明日はこの処理内で、SpawnedSplineUnitにActorをしまう
		ProcedualSplineActorsBuilder->SpawnActors(SpawnedSplineUnit);

		StartPoint = SpawnedSplineUnit.NextSpawnPoint;
		SpawnedSplineUnits.Push(SpawnedSplineUnit);
	}

	//for (auto i = 0; i < Spline->GetNumberOfSplinePoints(); i++) {
	//	ProcedualSplineActorsBuilder->SetDebugGridsEachSplinePoints(WhatToSpawn, i);
	//}

}