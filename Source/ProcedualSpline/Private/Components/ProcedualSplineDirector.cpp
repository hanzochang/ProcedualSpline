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
	TArray<FSplineUnit> &SplineUnits,
	TArray<FSpawnedSplineUnit> &SpawnedSplineUnits
)
{
	// ó·äOèàóùÇèëÇ≠ÅBBuilderÇ™Ç»Ç©Ç¡ÇΩèÍçá 
	int32 counter = 0;
	int32 TopmostSplineNumber = 0;
	FSpawnedSplineUnit PreviousSpawnedSplineUnit;
	float CurrentLength = 0;
	FVector StartPoint = FVector{ 0,0,0 }; //Ç±ÇÍÇÕSplineStructÇÃÇŸÇ§Ç…Ç¢ÇÍÇÈ

	for (int32 i = 0; i < Entity->DisplayableSplineUnitSum(); i++)
	{
		TopmostSplineNumber = Spline->GetNumberOfSplinePoints();
		CurrentLength = Spline->GetSplineLength();
		counter = i % SplineUnits.Num();
		
		FSplineUnit SplineUnit = SplineUnits[counter];
		FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint);
		ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);

		SpawnedSplineUnit.DeriveNextSpawnPoint(PreviousSpawnedSplineUnit);
		SpawnedSplineUnit.Length = Spline->GetSplineLength() - CurrentLength;
		StartPoint = SpawnedSplineUnit.NextSpawnPoint;

		SpawnedSplineUnits.Push(SpawnedSplineUnit);
		PreviousSpawnedSplineUnit = SpawnedSplineUnit;
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(SpawnedSplineUnit.Length)); }
	}

	RefreshEntityParameters(SpawnedSplineUnits);

	//for (FSpawnedSplineUnit SpawnedSplineUnit : SpawnedSplineUnits)
	//{
	//	SpawnedSplineUnit.Destroy();
	//}
}

void UProcedualSplineDirector::CheckProcedualSplineEntity(FProcedualSplineEntity &Entity, float CurrentLength)
{

}

void UProcedualSplineDirector::RefreshEntityParameters(TArray<FSpawnedSplineUnit> &SpawnedSplineUnits)
{
	float SplineLength = 0;
	for (int32 i = 0; i < SpawnedSplineUnits.Num(); i++)
	{
		float number = i + 1;

		if (number == Entity->DisplayableSplineUnitBuffer)
		{
			Entity->RearRefreshSplineLength = SplineLength + SpawnedSplineUnits[i].Length / 2;
		}
		else if (number == (Entity->DisplayableSplineUnitBuffer + 1 + 1))
		{
			Entity->TopRefreshSplineLength = SplineLength + SpawnedSplineUnits[i].Length / 2;
		}

		SplineLength += SpawnedSplineUnits[i].Length;
	}

	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(SplineLength)); }
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::SanitizeFloat(Entity->RearRefreshSplineLength)); }
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::SanitizeFloat(Entity->TopRefreshSplineLength)); }

}
