// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineDirector.h"

void UProcedualSplineDirector::Initialize(
	USplineComponent *InSpline,
	TArray<FSplineUnit> *InSplineUnits,
	FProcedualSplineEntity *InEntity,
	UProcedualSplinePointBuilder *InProcedualSplinePointBuilder,
	UProcedualSplineActorsBuilder *InProcedualSplineActorsBuilder
)
{
	Spline = InSpline;
	SplineUnits = InSplineUnits;
	Entity = InEntity;
	ProcedualSplinePointBuilder = InProcedualSplinePointBuilder;
	ProcedualSplineActorsBuilder = InProcedualSplineActorsBuilder;

    Owner = GetOwner();
}

void UProcedualSplineDirector::CreateInitialSpline(
	FProcedualSplineEntity &Entity,
	TArray<FSplineUnit> &SplineUnits,
	TArray<FSpawnedSplineUnit> &SpawnedSplineUnits
)
{
	// ó·äOèàóùÇèëÇ≠ÅBBuilderÇ™Ç»Ç©Ç¡ÇΩèÍçá 
	int32 counter = 0;
	int32 TopmostSplineNumber = 0;
	FSpawnedSplineUnit PreviousSpawnedSplineUnit;
	FVector StartPoint = FVector{ 0,0,0 }; //Ç±ÇÍÇÕSplineStructÇÃÇŸÇ§Ç…Ç¢ÇÍÇÈ

	for (int32 i = 0; i < Entity.DisplayableSplineUnitSum(); i++)
	{
		TopmostSplineNumber = Spline->GetNumberOfSplinePoints();
		counter = i % SplineUnits.Num();

		FSplineUnit SplineUnit = SplineUnits[counter];
		FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint);
		ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);

		SpawnedSplineUnit.DeriveNextSpawnPoint(PreviousSpawnedSplineUnit);
		StartPoint = SpawnedSplineUnit.NextSpawnPoint;
		SpawnedSplineUnits.Push(SpawnedSplineUnit);

		PreviousSpawnedSplineUnit = SpawnedSplineUnit;
	}

	//for (FSpawnedSplineUnit SpawnedSplineUnit : SpawnedSplineUnits)
	//{
	//	SpawnedSplineUnit.Destroy();
	//}
}