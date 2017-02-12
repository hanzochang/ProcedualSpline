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
    ProcedualSplineActorsBuilder = CreateDefaultSubobject<UProcedualSplineActorsBuilder>(FName("SplineActorsBuilder"));
	ProcedualSplineEntity = FProcedualSplineEntity(2);

	SplineUnits = SplineUnitGenerator->GenerateSplineUnits("splinetest.json");

	LoadDebugGrid();

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

	// ‚±‚±‚ÌŠi”[‚Å—Ž‚¿‚Ä‚éL‚¢‚È
	ProcedualSplineActorsBuilder->Initialize();

	//static ConstructorHelpers::FObjectFinder<UBlueprint> DebugGridClassFinder( TEXT( "Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'" ) );

	//if (DebugGridClassFinder.Succeeded())
	//{
	//	WhatToSpawn = (UClass*)DebugGridClassFinder.Object->GeneratedClass;
	//}

	//for (auto i = 0 ; i < Spline->GetNumberOfSplinePoints(); i++) {
	//	SetDebugGridsEachSplinePoints(i);
	//}
	
}

//void AProcedualSplineBase::LoadDebugGrid()
//{
//	static ConstructorHelpers::FObjectFinder<UBlueprint> DebugGridClassFinder( TEXT( "Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'" ) );
//
//	if (DebugGridClassFinder.Succeeded())
//	{
//		WhatToSpawn = (UClass*)DebugGridClassFinder.Object->GeneratedClass;
//	}
//}
//
//void AProcedualSplineBase::SetDebugGridsEachSplinePoints(int PointNum)
//{
//	FVector Location = { 0.0, 0.0, 0.0 };
//	FRotator Rotation = { 0.0, 0.0, 0.0 };
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Owner = this;
//	AActor* const SpawningObject = GetWorld()->SpawnActor<AActor>(WhatToSpawn,
//		Spline->GetLocationAtSplinePoint(PointNum, ESplineCoordinateSpace::Type::Local), 
//		Spline->GetRotationAtSplinePoint(PointNum, ESplineCoordinateSpace::Type::Local),
//		SpawnParams);
//
//	SpawningObject->Destroy();
//}